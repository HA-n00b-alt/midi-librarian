#include "MidiManager.h"

MidiManager::MidiManager()
{
    // Initialize MIDI message queue
    midiMessageQueue.ensureStorageAllocated(MIDI_FIFO_SIZE);
    midiMessageQueue.resize(MIDI_FIFO_SIZE);
    
    // Listen for MIDI device changes
    juce::MidiOutput::getDevices(); // Trigger device list refresh
    juce::MidiOutput::addChangeListener(this);
}

MidiManager::~MidiManager()
{
    juce::MidiOutput::removeChangeListener(this);
    closePort();
}

juce::Result MidiManager::setOutputPort(const juce::String& portName)
{
    const juce::ScopedLock sl(deviceLock);
    
    if (portName.isEmpty())
    {
        closePort();
        sendChangeMessage();
        return juce::Result::ok();
    }
    
    if (portName == currentPortName && midiOutput != nullptr)
    {
        return juce::Result::ok(); // Already open
    }
    
    auto result = openPort(portName);
    if (result.wasOk())
    {
        sendChangeMessage();
    }
    return result;
}

void MidiManager::setMidiChannel(int channel)
{
    const juce::ScopedLock sl(deviceLock);
    // Channel is 1-16 from UI, convert to 0-15
    jassert(channel >= 1 && channel <= 16);
    midiChannel = juce::jlimit(0, 15, channel - 1);
}

juce::StringArray MidiManager::getAvailableOutputPorts() const
{
    return juce::MidiOutput::getDevices();
}

juce::Result MidiManager::sendProgramChange(int programNumber)
{
    // Validate program number (0-127)
    if (programNumber < 0 || programNumber > 127)
    {
        return juce::Result::fail("Program number must be 0-127");
    }
    
    // Check if port is open (thread-safe read)
    {
        const juce::ScopedLock sl(deviceLock);
        if (midiOutput == nullptr)
        {
            return juce::Result::fail("MIDI output port not open");
        }
    }
    
    // Queue message to FIFO (thread-safe)
    const juce::ScopedLock sl(midiQueueLock);
    
    int start1, size1, start2, size2;
    midiFifo.prepareToWrite(1, start1, size1, start2, size2);
    
    if (size1 + size2 == 0)
    {
        return juce::Result::fail("MIDI output queue full");
    }
    
    // Create Program Change message on the specified channel
    int channel;
    {
        const juce::ScopedLock deviceSl(deviceLock);
        channel = midiChannel + 1; // Convert 0-15 to 1-16
    }
    
    juce::MidiMessage message = juce::MidiMessage::programChange(channel, programNumber);
    
    if (size1 > 0)
    {
        midiMessageQueue.set(start1, message);
        midiFifo.finishedWrite(size1);
    }
    else if (size2 > 0)
    {
        midiMessageQueue.set(start2, message);
        midiFifo.finishedWrite(size2);
    }
    
    return juce::Result::ok();
}

juce::Result MidiManager::sendControlChange(int controller, int value)
{
    if (controller < 0 || controller > 127)
    {
        return juce::Result::fail("Controller number must be 0-127");
    }
    
    if (value < 0 || value > 127)
    {
        return juce::Result::fail("Control value must be 0-127");
    }
    
    {
        const juce::ScopedLock sl(deviceLock);
        if (midiOutput == nullptr)
        {
            return juce::Result::fail("MIDI output port not open");
        }
    }
    
    const juce::ScopedLock sl(midiQueueLock);
    
    int start1, size1, start2, size2;
    midiFifo.prepareToWrite(1, start1, size1, start2, size2);
    
    if (size1 + size2 == 0)
    {
        return juce::Result::fail("MIDI output queue full");
    }
    
    int channel;
    {
        const juce::ScopedLock deviceSl(deviceLock);
        channel = midiChannel + 1;
    }
    
    juce::MidiMessage message = juce::MidiMessage::controllerEvent(channel, controller, value);
    
    if (size1 > 0)
    {
        midiMessageQueue.set(start1, message);
        midiFifo.finishedWrite(size1);
    }
    else if (size2 > 0)
    {
        midiMessageQueue.set(start2, message);
        midiFifo.finishedWrite(size2);
    }
    
    return juce::Result::ok();
}

juce::Result MidiManager::sendBankSelect(int bankNumber, bool useMSB)
{
    if (bankNumber < 0 || bankNumber > 127)
    {
        return juce::Result::fail("Bank number must be 0-127");
    }
    
    // Send Bank Select MSB (CC#0) or LSB (CC#32)
    int controller = useMSB ? 0 : 32;
    return sendControlChange(controller, bankNumber);
}

void MidiManager::processAudioThread(juce::MidiBuffer& midiBuffer)
{
    // This is called from processBlock() on the audio thread
    // Read queued messages from FIFO and add to the output MIDI buffer
    
    const juce::ScopedLock sl(midiQueueLock);
    
    int start1, size1, start2, size2;
    midiFifo.prepareToRead(midiFifo.getNumReady(), start1, size1, start2, size2);
    
    // Read first block
    for (int i = 0; i < size1; ++i)
    {
        const auto& message = midiMessageQueue[start1 + i];
        midiBuffer.addEvent(message, 0); // Add at sample 0 (start of block)
    }
    
    // Read second block (if FIFO wrapped)
    for (int i = 0; i < size2; ++i)
    {
        const auto& message = midiMessageQueue[start2 + i];
        midiBuffer.addEvent(message, 0);
    }
    
    midiFifo.finishedRead(size1 + size2);
}

bool MidiManager::isPortOpen() const noexcept
{
    const juce::ScopedLock sl(deviceLock);
    return midiOutput != nullptr;
}

juce::String MidiManager::getCurrentPortName() const noexcept
{
    const juce::ScopedLock sl(deviceLock);
    return currentPortName;
}

int MidiManager::getCurrentChannel() const noexcept
{
    const juce::ScopedLock sl(deviceLock);
    return midiChannel + 1; // Return 1-16 for display
}

void MidiManager::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    // MIDI device list changed - handle hotplug
    refreshPortList();
    sendChangeMessage();
}

void MidiManager::refreshPortList()
{
    const juce::ScopedLock sl(deviceLock);
    
    auto availablePorts = juce::MidiOutput::getDevices();
    
    // If current port is no longer available, close it
    if (!currentPortName.isEmpty() && !availablePorts.contains(currentPortName))
    {
        juce::Logger::writeToLog("MIDI device disconnected: " + currentPortName);
        closePort();
    }
    // If port was closed but is now available again, try to reopen
    else if (midiOutput == nullptr && !currentPortName.isEmpty() && availablePorts.contains(currentPortName))
    {
        juce::Logger::writeToLog("MIDI device reconnected, attempting to reopen: " + currentPortName);
        // Note: We don't call openPort() here directly because we're in a callback
        // The UI should handle reconnection via setOutputPort()
    }
}

juce::Result MidiManager::openPort(const juce::String& portName)
{
    if (portName.isEmpty())
    {
        closePort();
        return juce::Result::ok();
    }
    
    auto availablePorts = juce::MidiOutput::getDevices();
    int portIndex = availablePorts.indexOf(portName);
    
    if (portIndex < 0)
    {
        return juce::Result::fail("MIDI output port not found: " + portName);
    }
    
    midiOutput = juce::MidiOutput::openDevice(portIndex);
    if (midiOutput == nullptr)
    {
        return juce::Result::fail("Failed to open MIDI output port: " + portName);
    }
    
    currentPortName = portName;
    return juce::Result::ok();
}

void MidiManager::closePort()
{
    midiOutput.reset();
    currentPortName = juce::String();
}


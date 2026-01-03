#include "MidiManager.h"

MidiManager::MidiManager()
{
    // Initialize MIDI message queue
    midiMessageQueue.ensureStorageAllocated(MIDI_FIFO_SIZE);
    midiMessageQueue.resize(MIDI_FIFO_SIZE);
    
    // Create input callback
    inputCallback = std::make_unique<MidiInputCallback>(*this);
    
    // Note: MIDI device change listeners have been removed in newer JUCE versions
    // Device hotplug detection will need to be handled via polling or other mechanisms
}

MidiManager::~MidiManager()
{
    // Note: Change listeners removed - no cleanup needed
    closePort();
    closeInputPort();
}

void MidiManager::MidiInputCallback::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    // Forward to callback on message thread
    if (midiManager.onMidiInput)
    {
        juce::MessageManager::callAsync([this, message]()
        {
            midiManager.onMidiInput(message);
        });
    }
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
    juce::StringArray portNames;
    auto devices = juce::MidiOutput::getAvailableDevices();
    for (const auto& device : devices)
    {
        portNames.add(device.name);
    }
    return portNames;
}

juce::StringArray MidiManager::getAvailableInputPorts() const
{
    juce::StringArray portNames;
    auto devices = juce::MidiInput::getAvailableDevices();
    for (const auto& device : devices)
    {
        portNames.add(device.name);
    }
    return portNames;
}

juce::Result MidiManager::setInputPort(const juce::String& portName)
{
    const juce::ScopedLock sl(deviceLock);
    
    if (portName.isEmpty())
    {
        closeInputPort();
        sendChangeMessage();
        return juce::Result::ok();
    }
    
    if (portName == currentInputPortName && midiInput != nullptr)
    {
        return juce::Result::ok(); // Already open
    }
    
    auto result = openInputPort(portName);
    if (result.wasOk())
    {
        sendChangeMessage();
    }
    return result;
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

juce::Result MidiManager::sendSysEx(const juce::uint8* data, int dataSize)
{
    if (data == nullptr || dataSize <= 0)
    {
        return juce::Result::fail("Invalid SysEx data");
    }
    
    {
        const juce::ScopedLock sl(deviceLock);
        if (midiOutput == nullptr)
        {
            return juce::Result::fail("MIDI output port not open");
        }
    }
    
    const juce::ScopedLock sl(midiQueueLock);
    
    // SysEx messages can be large, so we need to handle them carefully
    // For now, we'll queue them like other messages, but they might need special handling
    int start1, size1, start2, size2;
    midiFifo.prepareToWrite(1, start1, size1, start2, size2);
    
    if (size1 + size2 == 0)
    {
        return juce::Result::fail("MIDI output queue full");
    }
    
    juce::MidiMessage message = juce::MidiMessage::createSysExMessage(data, dataSize);
    
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

bool MidiManager::isInputPortOpen() const noexcept
{
    const juce::ScopedLock sl(deviceLock);
    return midiInput != nullptr;
}

juce::String MidiManager::getCurrentPortName() const noexcept
{
    const juce::ScopedLock sl(deviceLock);
    return currentPortName;
}

juce::String MidiManager::getCurrentInputPortName() const noexcept
{
    const juce::ScopedLock sl(deviceLock);
    return currentInputPortName;
}

int MidiManager::getCurrentChannel() const noexcept
{
    const juce::ScopedLock sl(deviceLock);
    return midiChannel + 1; // Return 1-16 for display
}

// Note: changeListenerCallback removed - MIDI device change listeners no longer available in JUCE
// For device hotplug detection, consider polling getAvailableDevices() periodically

void MidiManager::refreshPortList()
{
    const juce::ScopedLock sl(deviceLock);
    
    auto availableDevices = juce::MidiOutput::getAvailableDevices();
    juce::StringArray availablePorts;
    for (const auto& device : availableDevices)
    {
        availablePorts.add(device.name);
    }
    
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
    
    auto availableDevices = juce::MidiOutput::getAvailableDevices();
    juce::MidiDeviceInfo deviceToOpen;
    bool found = false;
    
    for (const auto& device : availableDevices)
    {
        if (device.name == portName)
        {
            deviceToOpen = device;
            found = true;
            break;
        }
    }
    
    if (!found)
    {
        return juce::Result::fail("MIDI output port not found: " + portName);
    }
    
    midiOutput = juce::MidiOutput::openDevice(deviceToOpen.identifier);
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

juce::Result MidiManager::openInputPort(const juce::String& portName)
{
    if (portName.isEmpty())
    {
        closeInputPort();
        return juce::Result::ok();
    }
    
    auto availableDevices = juce::MidiInput::getAvailableDevices();
    juce::MidiDeviceInfo deviceToOpen;
    bool found = false;
    
    for (const auto& device : availableDevices)
    {
        if (device.name == portName)
        {
            deviceToOpen = device;
            found = true;
            break;
        }
    }
    
    if (!found)
    {
        return juce::Result::fail("MIDI input port not found: " + portName);
    }
    
    midiInput = juce::MidiInput::openDevice(deviceToOpen.identifier, inputCallback.get());
    if (midiInput == nullptr)
    {
        return juce::Result::fail("Failed to open MIDI input port: " + portName);
    }
    
    midiInput->start();
    currentInputPortName = portName;
    return juce::Result::ok();
}

void MidiManager::closeInputPort()
{
    if (midiInput != nullptr)
    {
        midiInput->stop();
        midiInput.reset();
    }
    currentInputPortName = juce::String();
}


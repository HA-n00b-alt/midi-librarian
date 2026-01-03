#include "MidiManager.h"

MidiManager::MidiManager()
{
    // Listen for MIDI device changes
    juce::MidiOutput::getDevices(); // Trigger device list refresh
    juce::MidiOutput::addChangeListener(this);
}

MidiManager::~MidiManager()
{
    juce::MidiOutput::removeChangeListener(this);
    closePort();
}

void MidiManager::setOutputPort(const juce::String& portName)
{
    if (portName != currentPortName)
    {
        closePort();
        openPort(portName);
        sendChangeMessage();
    }
}

void MidiManager::setMidiChannel(int channel)
{
    // Channel is 1-16 from UI, convert to 0-15
    jassert(channel >= 1 && channel <= 16);
    midiChannel = juce::jlimit(0, 15, channel - 1);
}

juce::StringArray MidiManager::getAvailableOutputPorts() const
{
    return juce::MidiOutput::getDevices();
}

void MidiManager::sendProgramChange(int programNumber)
{
    // Validate program number (0-127)
    programNumber = juce::jlimit(0, 127, programNumber);
    
    if (midiOutput != nullptr)
    {
        // Create Program Change message on the specified channel
        // MIDI Program Change: 0xC0-0xCF (channel 1-16)
        juce::MidiMessage message = juce::MidiMessage::programChange(midiChannel + 1, programNumber);
        midiOutput->sendMessageNow(message);
    }
}

void MidiManager::sendControlChange(int controller, int value)
{
    if (midiOutput != nullptr)
    {
        juce::MidiMessage message = juce::MidiMessage::controllerEvent(midiChannel + 1, controller, value);
        midiOutput->sendMessageNow(message);
    }
}

bool MidiManager::isPortOpen() const noexcept
{
    return midiOutput != nullptr;
}

juce::String MidiManager::getCurrentPortName() const noexcept
{
    return currentPortName;
}

int MidiManager::getCurrentChannel() const noexcept
{
    return midiChannel + 1; // Return 1-16 for display
}

void MidiManager::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    // MIDI device list changed - refresh available ports
    refreshPortList();
    sendChangeMessage();
}

void MidiManager::refreshPortList()
{
    // If current port is still available, keep it open
    // Otherwise, close it
    auto availablePorts = juce::MidiOutput::getDevices();
    if (!availablePorts.contains(currentPortName))
    {
        closePort();
    }
}

void MidiManager::openPort(const juce::String& portName)
{
    if (portName.isEmpty())
    {
        closePort();
        return;
    }
    
    auto availablePorts = juce::MidiOutput::getDevices();
    int portIndex = availablePorts.indexOf(portName);
    
    if (portIndex >= 0)
    {
        midiOutput = juce::MidiOutput::openDevice(portIndex);
        if (midiOutput != nullptr)
        {
            currentPortName = portName;
        }
    }
}

void MidiManager::closePort()
{
    midiOutput.reset();
    currentPortName = juce::String();
}


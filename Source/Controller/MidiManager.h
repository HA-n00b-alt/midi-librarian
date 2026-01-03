#pragma once

#include <JuceHeader.h>
#include "../Model/DeviceModel.h"

/**
 * Handles all MIDI I/O operations.
 * 
 * IMPORTANT: All MIDI operations run on the message thread, NOT the audio thread.
 * This is safe because:
 * - MIDI messages are not time-critical
 * - We're not processing audio
 * - JUCE's MidiOutput is thread-safe for sending
 * 
 * This class manages the MIDI output port lifecycle and sends program change messages.
 */
class MidiManager : public juce::ChangeListener,
                     public juce::ChangeBroadcaster
{
public:
    MidiManager();
    ~MidiManager() override;
    
    // Device management
    void setOutputPort(const juce::String& portName);
    void setMidiChannel(int channel); // 1-16
    juce::StringArray getAvailableOutputPorts() const;
    
    // MIDI operations
    void sendProgramChange(int programNumber); // 0-127
    void sendControlChange(int controller, int value); // For future use
    
    // State
    bool isPortOpen() const noexcept;
    juce::String getCurrentPortName() const noexcept;
    int getCurrentChannel() const noexcept; // Returns 1-16
    
    // JUCE ChangeListener (for MIDI device list changes)
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
private:
    void refreshPortList();
    void openPort(const juce::String& portName);
    void closePort();
    
    juce::String currentPortName;
    int midiChannel = 0; // 0-15 (channel 1-16)
    std::unique_ptr<juce::MidiOutput> midiOutput;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiManager)
};


#pragma once

#include <JuceHeader.h>
#include "../Model/DeviceModel.h"

/**
 * Handles all MIDI I/O operations.
 * 
 * THREADING MODEL:
 * - Device management (port open/close) happens on message thread
 * - MIDI message sending uses a lock-free FIFO for audio thread processing
 * - User-initiated sends (from UI) queue messages to FIFO
 * - processBlock() on audio thread reads FIFO for sample-accurate timing
 * 
 * This ensures proper DAW integration and sample-accurate MIDI timing.
 */
class MidiManager : public juce::ChangeListener,
                     public juce::ChangeBroadcaster
{
public:
    MidiManager();
    ~MidiManager() override;
    
    // Device management (message thread only)
    juce::Result setOutputPort(const juce::String& portName);
    void setMidiChannel(int channel); // 1-16
    juce::StringArray getAvailableOutputPorts() const;
    
    // MIDI operations (thread-safe, queues to FIFO)
    juce::Result sendProgramChange(int programNumber); // 0-127
    juce::Result sendControlChange(int controller, int value);
    juce::Result sendBankSelect(int bankNumber, bool useMSB = true); // Bank 0-127, MSB (CC#0) or LSB (CC#32)
    
    // Audio thread processing (called from processBlock)
    void processAudioThread(juce::MidiBuffer& midiBuffer);
    
    // State (thread-safe reads)
    bool isPortOpen() const noexcept;
    juce::String getCurrentPortName() const noexcept;
    int getCurrentChannel() const noexcept; // Returns 1-16
    
    // JUCE ChangeListener (for MIDI device list changes)
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
private:
    void refreshPortList();
    juce::Result openPort(const juce::String& portName);
    void closePort();
    
    // Thread-safe MIDI message queue
    static constexpr int MIDI_FIFO_SIZE = 512;
    juce::AbstractFifo midiFifo { MIDI_FIFO_SIZE };
    juce::Array<juce::MidiMessage> midiMessageQueue;
    juce::CriticalSection midiQueueLock;
    
    // Device state (protected by critical section for port operations)
    juce::CriticalSection deviceLock;
    juce::String currentPortName;
    int midiChannel = 0; // 0-15 (channel 1-16)
    std::unique_ptr<juce::MidiOutput> midiOutput;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiManager)
};


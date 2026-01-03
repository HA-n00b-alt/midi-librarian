#pragma once

#include <JuceHeader.h>

/**
 * Represents the selected MIDI device configuration.
 * 
 * Currently minimal - just port and channel selection.
 * Future: Device templates with patch validation, SysEx formats, etc.
 */
class DeviceModel
{
public:
    DeviceModel() = default;
    
    // Getters
    juce::String getMidiOutputPortName() const noexcept { return midiOutputPortName; }
    int getMidiChannel() const noexcept { return midiChannel; }
    juce::Identifier getDeviceID() const noexcept { return deviceID; }
    
    // Setters
    void setMidiOutputPortName(const juce::String& name) noexcept { midiOutputPortName = name; }
    void setMidiChannel(int channel) noexcept 
    { 
        // MIDI channels are 1-16, but we store 0-15 internally
        jassert(channel >= 1 && channel <= 16);
        midiChannel = juce::jlimit(1, 16, channel) - 1; // Store as 0-15
    }
    void setDeviceID(const juce::Identifier& id) noexcept { deviceID = id; }
    
    // Helper: Get MIDI channel as 1-16 for display
    int getMidiChannelDisplay() const noexcept { return midiChannel + 1; }
    
    // Helper: Get MIDI channel as 0-15 for MIDI messages
    int getMidiChannelZeroBased() const noexcept { return midiChannel; }
    
    // Serialization
    juce::var toVar() const;
    void fromVar(const juce::var& v);
    
private:
    juce::String midiOutputPortName;
    int midiChannel = 0; // 0-15 (MIDI channel 1-16)
    juce::Identifier deviceID = "generic";
};


#pragma once

#include <JuceHeader.h>
#include "DeviceTemplate.h"

/**
 * Represents the selected MIDI device configuration.
 * 
 * Now includes device template support for device-specific features.
 */
class DeviceModel
{
public:
    DeviceModel() = default;
    
    // Getters
    juce::String getMidiOutputPortName() const noexcept { return midiOutputPortName; }
    int getMidiChannel() const noexcept { return midiChannel; }
    juce::Identifier getDeviceID() const noexcept { return deviceID; }
    const DeviceTemplate& getTemplate() const noexcept { return deviceTemplate; }
    
    // Setters
    void setMidiOutputPortName(const juce::String& name) noexcept { midiOutputPortName = name; }
    void setMidiChannel(int channel) noexcept 
    { 
        // MIDI channels are 1-16, but we store 0-15 internally
        jassert(channel >= 1 && channel <= 16);
        midiChannel = juce::jlimit(1, 16, channel) - 1; // Store as 0-15
    }
    void setDeviceID(const juce::Identifier& id) noexcept 
    { 
        deviceID = id;
        // Update template when device ID changes
        deviceTemplate.setDeviceID(id);
    }
    void setTemplate(const DeviceTemplate& template_) noexcept { deviceTemplate = template_; }
    
    // Helper: Get MIDI channel as 1-16 for display
    int getMidiChannelDisplay() const noexcept { return midiChannel + 1; }
    
    // Helper: Get MIDI channel as 0-15 for MIDI messages
    int getMidiChannelZeroBased() const noexcept { return midiChannel; }
    
    // Template helpers
    bool isValidPatchNumber(int patchNumber) const noexcept
    {
        return deviceTemplate.isValidPatchNumber(patchNumber);
    }
    
    // Serialization
    juce::var toVar() const;
    void fromVar(const juce::var& v);
    
private:
    juce::String midiOutputPortName;
    int midiChannel = 0; // 0-15 (channel 1-16)
    juce::Identifier deviceID = "generic";
    DeviceTemplate deviceTemplate = DeviceTemplate::createGeneric();
};

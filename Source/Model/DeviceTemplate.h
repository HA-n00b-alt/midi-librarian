#pragma once

#include <JuceHeader.h>

/**
 * Device template/profile for specific hardware synths.
 * 
 * Defines device-specific properties:
 * - Device name and manufacturer
 * - MIDI channel requirements
 * - Bank select method (MSB/LSB/both)
 * - Valid patch ranges
 * - SysEx command formats (future)
 * - Parameter maps (future)
 */
class DeviceTemplate
{
public:
    DeviceTemplate() = default;
    
    DeviceTemplate(const juce::String& name, 
                  const juce::String& manufacturer,
                  const juce::Identifier& id)
        : deviceName(name)
        , manufacturer(manufacturer)
        , deviceID(id)
    {
    }
    
    // Getters
    juce::String getDeviceName() const noexcept { return deviceName; }
    juce::String getManufacturer() const noexcept { return manufacturer; }
    juce::Identifier getDeviceID() const noexcept { return deviceID; }
    int getMinPatchNumber() const noexcept { return minPatchNumber; }
    int getMaxPatchNumber() const noexcept { return maxPatchNumber; }
    bool usesBankSelect() const noexcept { return useBankSelect; }
    bool usesMSB() const noexcept { return useMSB; }
    bool usesLSB() const noexcept { return useLSB; }
    int getDefaultChannel() const noexcept { return defaultChannel; }
    
    // Setters
    void setDeviceName(const juce::String& name) noexcept { deviceName = name; }
    void setManufacturer(const juce::String& mfr) noexcept { manufacturer = mfr; }
    void setDeviceID(const juce::Identifier& id) noexcept { deviceID = id; }
    void setPatchRange(int min, int max) noexcept 
    { 
        minPatchNumber = juce::jlimit(0, 127, min);
        maxPatchNumber = juce::jlimit(0, 127, max);
    }
    void setBankSelect(bool use, bool msb = true, bool lsb = false) noexcept
    {
        useBankSelect = use;
        useMSB = msb;
        useLSB = lsb;
    }
    void setDefaultChannel(int channel) noexcept 
    { 
        defaultChannel = juce::jlimit(1, 16, channel); 
    }
    
    // Validation
    bool isValidPatchNumber(int patchNumber) const noexcept
    {
        return patchNumber >= minPatchNumber && patchNumber <= maxPatchNumber;
    }
    
    // Serialization
    juce::var toVar() const;
    static DeviceTemplate fromVar(const juce::var& v);
    
    // Factory methods for common devices
    static DeviceTemplate createGeneric();
    static DeviceTemplate createRolandJV1080();
    static DeviceTemplate createYamahaDX7();
    static DeviceTemplate createKorgM1();
    
private:
    juce::String deviceName = "Generic";
    juce::String manufacturer = "Generic";
    juce::Identifier deviceID = "generic";
    int minPatchNumber = 0;
    int maxPatchNumber = 127;
    bool useBankSelect = false;
    bool useMSB = true;
    bool useLSB = false;
    int defaultChannel = 1;
};


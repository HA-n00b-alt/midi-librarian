#pragma once

#include <JuceHeader.h>

/**
 * Visual indicator of MIDI device connection status.
 * 
 * Shows green when connected, red when disconnected,
 * with optional status text.
 */
class DeviceStatusIndicator : public juce::Component
{
public:
    DeviceStatusIndicator();
    ~DeviceStatusIndicator() override = default;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void setConnected(bool connected, const juce::String& statusText = juce::String());
    bool isConnected() const noexcept { return connected; }
    
private:
    bool connected = false;
    juce::String statusText;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeviceStatusIndicator)
};


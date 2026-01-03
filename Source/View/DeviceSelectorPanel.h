#pragma once

#include <JuceHeader.h>
#include "../Controller/PatchManager.h"
#include "DeviceStatusIndicator.h"

/**
 * Panel for selecting MIDI output port and channel.
 * 
 * Displays a ComboBox for port selection and a ComboBox for channel (1-16).
 * Updates the PatchManager when selections change.
 * Shows device connection status with visual indicator.
 */
class DeviceSelectorPanel : public juce::Component,
                            public juce::ComboBox::Listener,
                            public juce::Button::Listener,
                            public juce::ChangeListener
{
public:
    DeviceSelectorPanel(PatchManager& patchManager);
    ~DeviceSelectorPanel() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // ComboBox::Listener
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    
    // Button::Listener
    void buttonClicked(juce::Button* button) override;
    
    // ChangeListener (for MIDI device list changes)
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
private:
    PatchManager& patchManager;
    
    juce::Label portLabel;
    juce::ComboBox portComboBox;
    DeviceStatusIndicator statusIndicator;
    
    juce::Label channelLabel;
    juce::ComboBox channelComboBox;
    
    juce::Label bankLabel;
    juce::ComboBox bankComboBox;
    juce::ToggleButton useMSBButton;
    
    void refreshPortList();
    void updateChannelComboBox();
    void updateBankComboBox();
    void updateConnectionStatus();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeviceSelectorPanel)
};


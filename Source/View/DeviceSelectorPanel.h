#pragma once

#include <JuceHeader.h>
#include "../Controller/PatchManager.h"

/**
 * Panel for selecting MIDI output port and channel.
 * 
 * Displays a ComboBox for port selection and a ComboBox for channel (1-16).
 * Updates the PatchManager when selections change.
 */
class DeviceSelectorPanel : public juce::Component,
                            public juce::ComboBox::Listener,
                            public juce::ChangeListener
{
public:
    DeviceSelectorPanel(PatchManager& patchManager);
    ~DeviceSelectorPanel() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // ComboBox::Listener
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    
    // ChangeListener (for MIDI device list changes)
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
private:
    PatchManager& patchManager;
    
    juce::Label portLabel;
    juce::ComboBox portComboBox;
    
    juce::Label channelLabel;
    juce::ComboBox channelComboBox;
    
    void refreshPortList();
    void updateChannelComboBox();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeviceSelectorPanel)
};


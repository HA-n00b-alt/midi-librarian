#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "View/ValhallaLookAndFeel.h"
#include "View/DeviceSelectorPanel.h"
#include "View/PatchListPanel.h"

/**
 * Main plugin editor window.
 * 
 * This is the top-level UI component that contains:
 * - DeviceSelectorPanel (top)
 * - PatchListPanel (main area)
 * 
 * Applies the custom ValhallaLookAndFeel to all child components.
 */
class MidiLibrarianAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MidiLibrarianAudioProcessorEditor(MidiLibrarianAudioProcessor&);
    ~MidiLibrarianAudioProcessorEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    MidiLibrarianAudioProcessor& audioProcessor;
    
    ValhallaLookAndFeel valhallaLookAndFeel;
    
    DeviceSelectorPanel deviceSelectorPanel;
    PatchListPanel patchListPanel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiLibrarianAudioProcessorEditor)
};


#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "View/ValhallaLookAndFeel.h"
#include "View/DeviceSelectorPanel.h"
#include "View/PatchListPanel.h"
#include "View/ToolbarPanel.h"

/**
 * Main plugin editor window.
 * 
 * This is the top-level UI component that contains:
 * - DeviceSelectorPanel (top)
 * - ToolbarPanel (undo/redo, actions)
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
    ToolbarPanel toolbarPanel;
    PatchListPanel patchListPanel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiLibrarianAudioProcessorEditor)
};


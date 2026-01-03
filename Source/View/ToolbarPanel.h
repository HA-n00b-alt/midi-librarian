#pragma once

#include <JuceHeader.h>
#include "../Controller/PatchManager.h"

/**
 * Toolbar panel with undo/redo buttons and other actions.
 */
class ToolbarPanel : public juce::Component,
                     public juce::Button::Listener,
                     public juce::ChangeListener
{
public:
    ToolbarPanel(PatchManager& patchManager);
    ~ToolbarPanel() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // Button::Listener
    void buttonClicked(juce::Button* button) override;
    
    // ChangeListener (for undo manager changes)
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
    
private:
    PatchManager& patchManager;
    
    juce::TextButton undoButton;
    juce::TextButton redoButton;
    juce::TextButton copyButton;
    juce::TextButton clearButton;
    
    void updateUndoRedoButtons();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToolbarPanel)
};


#include "ToolbarPanel.h"
#include "ValhallaLookAndFeel.h"
#include "PatchOperationDialogs.h"

ToolbarPanel::ToolbarPanel(PatchManager& pm)
    : patchManager(pm)
{
    undoButton.setButtonText("Undo");
    undoButton.addListener(this);
    addAndMakeVisible(undoButton);
    
    redoButton.setButtonText("Redo");
    redoButton.addListener(this);
    addAndMakeVisible(redoButton);
    
    copyButton.setButtonText("Copy");
    copyButton.addListener(this);
    addAndMakeVisible(copyButton);
    
    clearButton.setButtonText("Clear Range");
    clearButton.addListener(this);
    addAndMakeVisible(clearButton);
    
    // Listen to undo manager
    patchManager.getUndoManager().addChangeListener(this);
    
    updateUndoRedoButtons();
}

ToolbarPanel::~ToolbarPanel()
{
    patchManager.getUndoManager().removeChangeListener(this);
}

void ToolbarPanel::paint(juce::Graphics& g)
{
    // Background handled by parent
}

void ToolbarPanel::resized()
{
    auto bounds = getLocalBounds().reduced(4);
    const int buttonWidth = 80;
    const int spacing = 8;
    
    undoButton.setBounds(bounds.removeFromLeft(buttonWidth));
    bounds.removeFromLeft(spacing);
    
    redoButton.setBounds(bounds.removeFromLeft(buttonWidth));
    bounds.removeFromLeft(spacing * 2);
    
    copyButton.setBounds(bounds.removeFromLeft(buttonWidth));
    bounds.removeFromLeft(spacing);
    
    clearButton.setBounds(bounds.removeFromLeft(buttonWidth + 20));
}

void ToolbarPanel::buttonClicked(juce::Button* button)
{
    if (button == &undoButton)
    {
        patchManager.undo();
    }
    else if (button == &redoButton)
    {
        patchManager.redo();
    }
    else if (button == &copyButton)
    {
        CopyPatchDialog dialog(128);
        juce::DialogWindow::showDialog("Copy Patch", &dialog, getTopLevelComponent(),
                                      juce::Colours::white, true);
        
        patchManager.copyPatch(dialog.getSourceSlot(), dialog.getDestSlot());
    }
    else if (button == &clearButton)
    {
        PatchRangeDialog dialog(128);
        juce::DialogWindow::showDialog("Clear Patch Range", &dialog, getTopLevelComponent(),
                                      juce::Colours::white, true);
        
        patchManager.clearPatchRange(dialog.getStartSlot(), dialog.getEndSlot());
    }
}

void ToolbarPanel::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &patchManager.getUndoManager())
    {
        updateUndoRedoButtons();
    }
}

void ToolbarPanel::updateUndoRedoButtons()
{
    undoButton.setEnabled(patchManager.canUndo());
    redoButton.setEnabled(patchManager.canRedo());
    
    // Update button text with action description
    if (patchManager.canUndo())
    {
        juce::String desc = patchManager.getUndoDescription();
        if (desc.isNotEmpty())
            undoButton.setButtonText("Undo: " + desc);
        else
            undoButton.setButtonText("Undo");
    }
    else
    {
        undoButton.setButtonText("Undo");
    }
    
    if (patchManager.canRedo())
    {
        juce::String desc = patchManager.getRedoDescription();
        if (desc.isNotEmpty())
            redoButton.setButtonText("Redo: " + desc);
        else
            redoButton.setButtonText("Redo");
    }
    else
    {
        redoButton.setButtonText("Redo");
    }
}


#pragma once

#include <JuceHeader.h>
#include "../Controller/PatchManager.h"
#include "PatchListItem.h"

/**
 * Main panel displaying the scrollable list of 128 patches.
 * 
 * Uses a Viewport with a vertical list of PatchListItem components.
 * Automatically updates when PatchBank changes.
 */
class PatchListPanel : public juce::Component,
                       public juce::ChangeListener
{
public:
    PatchListPanel(PatchManager& patchManager);
    ~PatchListPanel() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // ChangeListener (for PatchBank updates)
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
private:
    PatchManager& patchManager;
    
    juce::Viewport viewport;
    juce::Component listContainer;
    juce::OwnedArray<PatchListItem> patchItems;
    
    void rebuildList();
    void onPatchRename(int slotIndex, const juce::String& newName);
    void onPatchRecall(int slotIndex);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchListPanel)
};


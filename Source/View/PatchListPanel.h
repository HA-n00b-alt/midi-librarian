#pragma once

#include <JuceHeader.h>
#include "../Controller/PatchManager.h"
#include "PatchListItem.h"
#include "SearchBar.h"

/**
 * Main panel displaying the scrollable list of 128 patches.
 * 
 * Uses a Viewport with a vertical list of PatchListItem components.
 * Automatically updates when PatchBank changes.
 * Supports search/filtering and favorites.
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
    
    SearchBar searchBar;
    juce::Viewport viewport;
    juce::Component listContainer;
    juce::OwnedArray<PatchListItem> patchItems;
    
    juce::String currentSearchQuery;
    bool showFavoritesOnly = false;
    
    void rebuildList();
    void applyFilters();
    bool shouldShowPatch(int slotIndex) const;
    void onPatchRename(int slotIndex, const juce::String& newName);
    void onPatchRecall(int slotIndex);
    void onSearchTextChanged(const juce::String& query);
    void onFavoritesFilterChanged(bool favoritesOnly);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchListPanel)
};


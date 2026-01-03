#include "PatchListPanel.h"
#include "ValhallaLookAndFeel.h"

PatchListPanel::PatchListPanel(PatchManager& pm)
    : patchManager(pm)
{
    // Search bar
    searchBar.onSearchTextChanged = [this](const juce::String& query)
    {
        onSearchTextChanged(query);
    };
    searchBar.onFavoritesFilterChanged = [this](bool favoritesOnly)
    {
        onFavoritesFilterChanged(favoritesOnly);
    };
    addAndMakeVisible(searchBar);
    
    addAndMakeVisible(viewport);
    viewport.setViewedComponent(&listContainer, false);
    viewport.setScrollBarsShown(true, false, false, false);
    
    // Listen for patch bank changes and MIDI learn changes
    patchManager.getPatchBank().addChangeListener(this);
    patchManager.getMidiLearnManager().addChangeListener(this);
    
    rebuildList();
}

PatchListPanel::~PatchListPanel()
{
    patchManager.getPatchBank().removeChangeListener(this);
    patchManager.getMidiLearnManager().removeChangeListener(this);
}

void PatchListPanel::paint(juce::Graphics& g)
{
    // Background
    auto& lf = getLookAndFeel();
    g.setColour(static_cast<ValhallaLookAndFeel&>(lf).getBackgroundColour());
    g.fillRect(getLocalBounds());
}

void PatchListPanel::resized()
{
    auto bounds = getLocalBounds();
    
    // Search bar at top
    const int searchHeight = 40;
    searchBar.setBounds(bounds.removeFromTop(searchHeight));
    bounds.removeFromTop(4); // Spacing
    
    // Viewport takes remaining space
    viewport.setBounds(bounds);
    
    // Update list container height based on visible items
    const int itemHeight = 48;
    int visibleCount = 0;
    for (auto* item : patchItems)
    {
        if (item->isVisible())
            visibleCount++;
    }
    
    listContainer.setSize(viewport.getWidth() - viewport.getScrollBarThickness(),
                         visibleCount * itemHeight);
    
    // Update item positions (only for visible items)
    auto containerBounds = listContainer.getLocalBounds();
    for (auto* item : patchItems)
    {
        if (item->isVisible())
        {
            item->setBounds(containerBounds.removeFromTop(itemHeight));
        }
    }
}

void PatchListPanel::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &patchManager.getPatchBank())
    {
        // Update existing items instead of full rebuild if possible
        const auto& bank = patchManager.getPatchBank();
        bool needsRebuild = false;
        
        for (int i = 0; i < patchItems.size() && i < PatchBank::BANK_SIZE; ++i)
        {
            const auto& patch = bank.getPatch(i);
            if (patchItems[i] != nullptr)
            {
                patchItems[i]->setPatchName(patch.getPatchName());
                patchItems[i]->setFavorite(patch.isFavorite());
            }
            else
            {
                needsRebuild = true;
                break;
            }
        }
        
        if (needsRebuild || patchItems.size() != PatchBank::BANK_SIZE)
        {
            rebuildList();
        }
        else
        {
            applyFilters(); // Re-apply filters in case favorites changed
        }
    }
    else if (source == &patchManager.getMidiLearnManager())
    {
        // Update learning states
        updateLearningStates();
    }
}

void PatchListPanel::rebuildList()
{
    patchItems.clear();
    
    const auto& bank = patchManager.getPatchBank();
    
    for (int i = 0; i < PatchBank::BANK_SIZE; ++i)
    {
        const auto& patch = bank.getPatch(i);
        auto* item = new PatchListItem(i, patch.getPatchName());
        
        item->setFavorite(patch.isFavorite());
        
        item->onRename = [this](int slot, const juce::String& name)
        {
            onPatchRename(slot, name);
        };
        
        item->onRecall = [this](int slot)
        {
            onPatchRecall(slot);
        };
        
        item->onFavoriteChanged = [this](int slot, bool favorite)
        {
            patchManager.setPatchFavorite(slot, favorite);
        };
        
        item->onLearn = [this](int slot)
        {
            if (patchManager.getMidiLearnManager().isLearning() && 
                patchManager.getMidiLearnManager().getLearningSlot() == slot)
            {
                // Stop learning if already learning this slot
                patchManager.getMidiLearnManager().stopLearning();
            }
            else
            {
                patchManager.getMidiLearnManager().startLearning(slot);
            }
        };
        
        patchItems.add(item);
        listContainer.addChildComponent(item); // Use addChildComponent so we can hide/show
    }
    
    // Update learning state
    updateLearningStates();
    
    applyFilters();
    resized();
}

void PatchListPanel::applyFilters()
{
    for (int i = 0; i < patchItems.size(); ++i)
    {
        bool shouldShow = shouldShowPatch(i);
        patchItems[i]->setVisible(shouldShow);
    }
    
    resized(); // Update layout
}

bool PatchListPanel::shouldShowPatch(int slotIndex) const
{
    const auto& bank = patchManager.getPatchBank();
    const auto& patch = bank.getPatch(slotIndex);
    
    // Favorites filter
    if (showFavoritesOnly && !patch.isFavorite())
        return false;
    
    // Search query filter
    if (currentSearchQuery.isNotEmpty())
    {
        if (!patch.matchesSearchQuery(currentSearchQuery))
            return false;
    }
    
    return true;
}

void PatchListPanel::onSearchTextChanged(const juce::String& query)
{
    currentSearchQuery = query;
    applyFilters();
}

void PatchListPanel::onFavoritesFilterChanged(bool favoritesOnly)
{
    showFavoritesOnly = favoritesOnly;
    applyFilters();
}

void PatchListPanel::updateLearningStates()
{
    int learningSlot = patchManager.getMidiLearnManager().getLearningSlot();
    for (int i = 0; i < patchItems.size(); ++i)
    {
        if (patchItems[i] != nullptr)
        {
            patchItems[i]->setLearning(i == learningSlot);
        }
    }
}

void PatchListPanel::onPatchRename(int slotIndex, const juce::String& newName)
{
    patchManager.renamePatch(slotIndex, newName);
}

void PatchListPanel::onPatchRecall(int slotIndex)
{
    patchManager.recallPatch(slotIndex);
}


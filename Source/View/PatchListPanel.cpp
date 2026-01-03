#include "PatchListPanel.h"
#include "ValhallaLookAndFeel.h"

PatchListPanel::PatchListPanel(PatchManager& pm)
    : patchManager(pm)
{
    addAndMakeVisible(viewport);
    viewport.setViewedComponent(&listContainer, false);
    viewport.setScrollBarsShown(true, false, false, false);
    
    // Listen for patch bank changes
    patchManager.getPatchBank().addChangeListener(this);
    
    rebuildList();
}

PatchListPanel::~PatchListPanel()
{
    patchManager.getPatchBank().removeChangeListener(this);
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
    viewport.setBounds(getLocalBounds());
    
    // Update list container height based on number of items
    const int itemHeight = 48;
    listContainer.setSize(viewport.getWidth() - viewport.getScrollBarThickness(),
                         patchItems.size() * itemHeight);
    
    // Update item positions
    auto bounds = listContainer.getLocalBounds();
    for (auto* item : patchItems)
    {
        item->setBounds(bounds.removeFromTop(itemHeight));
    }
}

void PatchListPanel::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &patchManager.getPatchBank())
    {
        rebuildList();
    }
}

void PatchListPanel::rebuildList()
{
    patchItems.clear();
    
    const int itemHeight = 48;
    const auto& bank = patchManager.getPatchBank();
    
    for (int i = 0; i < PatchBank::BANK_SIZE; ++i)
    {
        const auto& patch = bank.getPatch(i);
        auto* item = new PatchListItem(i, patch.getPatchName());
        
        item->onRename = [this](int slot, const juce::String& name)
        {
            onPatchRename(slot, name);
        };
        
        item->onRecall = [this](int slot)
        {
            onPatchRecall(slot);
        };
        
        patchItems.add(item);
        listContainer.addAndMakeVisible(item);
    }
    
    // Update container size
    listContainer.setSize(listContainer.getWidth(), patchItems.size() * itemHeight);
    resized();
}

void PatchListPanel::onPatchRename(int slotIndex, const juce::String& newName)
{
    patchManager.renamePatch(slotIndex, newName);
}

void PatchListPanel::onPatchRecall(int slotIndex)
{
    patchManager.recallPatch(slotIndex);
}


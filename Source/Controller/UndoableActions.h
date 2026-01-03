#pragma once

#include <JuceHeader.h>
#include "../Model/PatchBank.h"
#include "../Model/PatchData.h"

/**
 * Undoable action for renaming a patch.
 */
class RenamePatchAction : public juce::UndoableAction
{
public:
    RenamePatchAction(PatchBank& bank, int slotIndex, 
                     const juce::String& newName, const juce::String& oldName)
        : patchBank(bank)
        , slotIndex(slotIndex)
        , newName(newName)
        , oldName(oldName)
    {
    }
    
    bool perform() override
    {
        patchBank.renamePatch(slotIndex, newName);
        return true;
    }
    
    bool undo() override
    {
        patchBank.renamePatch(slotIndex, oldName);
        return true;
    }
    
    int getSizeInUnits() override { return 1; }
    
private:
    PatchBank& patchBank;
    int slotIndex;
    juce::String newName;
    juce::String oldName;
};

/**
 * Undoable action for setting patch favorite status.
 */
class SetFavoriteAction : public juce::UndoableAction
{
public:
    SetFavoriteAction(PatchBank& bank, int slotIndex, bool newFavorite, bool oldFavorite)
        : patchBank(bank)
        , slotIndex(slotIndex)
        , newFavorite(newFavorite)
        , oldFavorite(oldFavorite)
    {
    }
    
    bool perform() override
    {
        auto& patch = patchBank.getPatch(slotIndex);
        patch.setFavorite(newFavorite);
        patchBank.setPatch(slotIndex, patch);
        return true;
    }
    
    bool undo() override
    {
        auto& patch = patchBank.getPatch(slotIndex);
        patch.setFavorite(oldFavorite);
        patchBank.setPatch(slotIndex, patch);
        return true;
    }
    
    int getSizeInUnits() override { return 1; }
    
private:
    PatchBank& patchBank;
    int slotIndex;
    bool newFavorite;
    bool oldFavorite;
};

/**
 * Undoable action for copying a patch to another slot.
 */
class CopyPatchAction : public juce::UndoableAction
{
public:
    CopyPatchAction(PatchBank& bank, int sourceSlot, int destSlot)
        : patchBank(bank)
        , sourceSlot(sourceSlot)
        , destSlot(destSlot)
        , oldPatch(bank.getPatch(destSlot))
    {
    }
    
    bool perform() override
    {
        const auto& sourcePatch = patchBank.getPatch(sourceSlot);
        auto newPatch = sourcePatch;
        newPatch.setSlotIndex(destSlot);
        patchBank.setPatch(destSlot, newPatch);
        return true;
    }
    
    bool undo() override
    {
        patchBank.setPatch(destSlot, oldPatch);
        return true;
    }
    
    int getSizeInUnits() override { return 1; }
    
private:
    PatchBank& patchBank;
    int sourceSlot;
    int destSlot;
    PatchData oldPatch;
};

/**
 * Undoable action for batch renaming patches.
 */
class BatchRenameAction : public juce::UndoableAction
{
public:
    struct PatchChange
    {
        int slotIndex;
        juce::String oldName;
        juce::String newName;
    };
    
    BatchRenameAction(PatchBank& bank, const juce::Array<PatchChange>& changes)
        : patchBank(bank)
        , changes(changes)
    {
    }
    
    bool perform() override
    {
        for (const auto& change : changes)
        {
            patchBank.renamePatch(change.slotIndex, change.newName);
        }
        return true;
    }
    
    bool undo() override
    {
        for (const auto& change : changes)
        {
            patchBank.renamePatch(change.slotIndex, change.oldName);
        }
        return true;
    }
    
    int getSizeInUnits() override { return changes.size(); }
    
private:
    PatchBank& patchBank;
    juce::Array<PatchChange> changes;
};


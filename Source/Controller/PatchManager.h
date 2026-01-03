#pragma once

#include <JuceHeader.h>
#include "../Model/PatchBank.h"
#include "../Model/DeviceModel.h"
#include "MidiManager.h"
#include "PersistenceManager.h"
#include "DeviceTemplateManager.h"
#include "MidiLearnManager.h"
#include "UndoableActions.h"

/**
 * Coordinates patch operations, MIDI I/O, and persistence.
 * 
 * This is the main Controller that ties together Model, View, and I/O.
 * It provides a high-level API for patch management operations.
 * Includes undo/redo support for all patch operations.
 */
class PatchManager : public juce::ChangeBroadcaster,
                     public juce::ChangeListener
{
public:
    PatchManager();
    ~PatchManager() override = default;
    
    // Access to models
    PatchBank& getPatchBank() noexcept { return patchBank; }
    const PatchBank& getPatchBank() const noexcept { return patchBank; }
    DeviceModel& getDeviceModel() noexcept { return deviceModel; }
    const DeviceModel& getDeviceModel() const noexcept { return deviceModel; }
    MidiManager& getMidiManager() noexcept { return midiManager; }
    PersistenceManager& getPersistenceManager() noexcept { return persistenceManager; }
    DeviceTemplateManager& getTemplateManager() noexcept { return templateManager; }
    MidiLearnManager& getMidiLearnManager() noexcept { return midiLearnManager; }
    juce::UndoManager& getUndoManager() noexcept { return undoManager; }
    
    // Patch operations (with undo support)
    void renamePatch(int slotIndex, const juce::String& newName);
    void recallPatch(int slotIndex); // Sends MIDI PC and updates UI
    void setPatchFavorite(int slotIndex, bool favorite);
    void copyPatch(int sourceSlot, int destSlot);
    void batchRenamePatches(const juce::Array<int>& slotIndices, 
                           const juce::String& baseName);
    void clearPatchRange(int startSlot, int endSlot);
    
    // Undo/Redo
    void undo();
    void redo();
    bool canUndo() const noexcept;
    bool canRedo() const noexcept;
    juce::String getUndoDescription() const;
    juce::String getRedoDescription() const;
    
    // Device operations
    void setMidiOutputPort(const juce::String& portName);
    void setMidiChannel(int channel); // 1-16
    
    // Persistence
    void saveAll();
    void loadAll();
    
    // Export/Import
    void exportPatches(const juce::File& file);
    void importPatches(const juce::File& file);
    
    // ChangeListener (for undo manager)
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
private:
    PatchBank patchBank;
    DeviceModel deviceModel;
    MidiManager midiManager;
    PersistenceManager persistenceManager;
    DeviceTemplateManager templateManager;
    MidiLearnManager midiLearnManager;
    juce::UndoManager undoManager;
    
    void syncMidiManagerWithDeviceModel();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchManager)
};


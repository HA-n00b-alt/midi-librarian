#pragma once

#include <JuceHeader.h>
#include "../Model/PatchBank.h"
#include "../Model/DeviceModel.h"
#include "MidiManager.h"
#include "PersistenceManager.h"

/**
 * Coordinates patch operations, MIDI I/O, and persistence.
 * 
 * This is the main Controller that ties together Model, View, and I/O.
 * It provides a high-level API for patch management operations.
 */
class PatchManager : public juce::ChangeBroadcaster
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
    
    // Patch operations
    void renamePatch(int slotIndex, const juce::String& newName);
    void recallPatch(int slotIndex); // Sends MIDI PC and updates UI
    
    // Device operations
    void setMidiOutputPort(const juce::String& portName);
    void setMidiChannel(int channel); // 1-16
    
    // Persistence
    void saveAll();
    void loadAll();
    
    // Export/Import
    void exportPatches(const juce::File& file);
    void importPatches(const juce::File& file);
    
private:
    PatchBank patchBank;
    DeviceModel deviceModel;
    MidiManager midiManager;
    PersistenceManager persistenceManager;
    
    void syncMidiManagerWithDeviceModel();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchManager)
};


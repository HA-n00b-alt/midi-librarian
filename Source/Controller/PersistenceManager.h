#pragma once

#include <JuceHeader.h>
#include "../Model/PatchBank.h"
#include "../Model/DeviceModel.h"

/**
 * Handles all file I/O for persistence.
 * 
 * Stores data as JSON in user's application data directory:
 * - Patch bank: ~/Library/Application Support/MidiLibrarian/patches.json
 * - Device config: ~/Library/Application Support/MidiLibrarian/config.json
 * 
 * All operations are synchronous and run on the message thread.
 * For large operations, consider moving to background thread in future.
 */
class PersistenceManager
{
public:
    PersistenceManager();
    ~PersistenceManager() = default;
    
    // Patch bank persistence
    bool savePatchBank(const PatchBank& bank);
    bool loadPatchBank(PatchBank& bank);
    
    // Device configuration persistence
    bool saveDeviceConfig(const DeviceModel& device);
    bool loadDeviceConfig(DeviceModel& device);
    
    // Export/Import (for backup/restore)
    bool exportToFile(const PatchBank& bank, const juce::File& file);
    bool importFromFile(PatchBank& bank, const juce::File& file);
    
    // Utility
    juce::File getDataDirectory() const;
    
private:
    juce::File getPatchesFile() const;
    juce::File getConfigFile() const;
    
    juce::File dataDirectory;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PersistenceManager)
};


#include "PatchManager.h"

PatchManager::PatchManager()
{
    // Load saved data on startup
    loadAll();
    
    // Sync MIDI manager with device model
    syncMidiManagerWithDeviceModel();
}

void PatchManager::renamePatch(int slotIndex, const juce::String& newName)
{
    patchBank.renamePatch(slotIndex, newName);
    saveAll(); // Auto-save on rename
    sendChangeMessage();
}

void PatchManager::recallPatch(int slotIndex)
{
    if (patchBank.isValidSlot(slotIndex))
    {
        // Send MIDI Program Change
        midiManager.sendProgramChange(slotIndex);
        
        // Notify UI
        sendChangeMessage();
    }
}

void PatchManager::setMidiOutputPort(const juce::String& portName)
{
    deviceModel.setMidiOutputPortName(portName);
    midiManager.setOutputPort(portName);
    saveAll();
    sendChangeMessage();
}

void PatchManager::setMidiChannel(int channel)
{
    deviceModel.setMidiChannel(channel);
    midiManager.setMidiChannel(channel);
    saveAll();
    sendChangeMessage();
}

void PatchManager::saveAll()
{
    persistenceManager.savePatchBank(patchBank);
    persistenceManager.saveDeviceConfig(deviceModel);
}

void PatchManager::loadAll()
{
    persistenceManager.loadPatchBank(patchBank);
    persistenceManager.loadDeviceConfig(deviceModel);
}

void PatchManager::exportPatches(const juce::File& file)
{
    persistenceManager.exportToFile(patchBank, file);
}

void PatchManager::importPatches(const juce::File& file)
{
    persistenceManager.importFromFile(patchBank, file);
    saveAll(); // Save imported data
    sendChangeMessage();
}

void PatchManager::syncMidiManagerWithDeviceModel()
{
    midiManager.setOutputPort(deviceModel.getMidiOutputPortName());
    midiManager.setMidiChannel(deviceModel.getMidiChannelDisplay());
}


#include "PatchManager.h"

PatchManager::PatchManager()
{
    // Load saved data on startup
    loadAll();
    
    // Load device template if device ID is set
    if (deviceModel.getDeviceID() != juce::Identifier("generic"))
    {
        auto template_ = templateManager.getTemplate(deviceModel.getDeviceID());
        deviceModel.setTemplate(template_);
    }
    
    // Sync MIDI manager with device model
    syncMidiManagerWithDeviceModel();
    
    // Setup MIDI learn callback
    midiLearnManager.onPatchRecall = [this](int slotIndex)
    {
        recallPatch(slotIndex);
    };
    
    // Setup MIDI input callback to process learn messages
    midiManager.onMidiInput = [this](const juce::MidiMessage& message)
    {
        midiLearnManager.processMidiMessage(message);
    };
    
    // Listen to undo manager for change notifications
    undoManager.addChangeListener(this);
}

void PatchManager::renamePatch(int slotIndex, const juce::String& newName)
{
    if (patchBank.isValidSlot(slotIndex))
    {
        const auto& oldPatch = patchBank.getPatch(slotIndex);
        juce::String oldName = oldPatch.getPatchName();
        
        if (oldName != newName)
        {
            undoManager.perform(new RenamePatchAction(patchBank, slotIndex, newName, oldName));
            saveAll(); // Auto-save on rename
            sendChangeMessage();
        }
    }
}

void PatchManager::recallPatch(int slotIndex)
{
    if (patchBank.isValidSlot(slotIndex))
    {
        // Send MIDI Program Change (queues to FIFO for audio thread)
        auto result = midiManager.sendProgramChange(slotIndex);
        
        if (result.failed())
        {
            juce::Logger::writeToLog("Failed to send program change: " + result.getErrorMessage());
        }
        
        // Notify UI
        sendChangeMessage();
    }
}

void PatchManager::setPatchFavorite(int slotIndex, bool favorite)
{
    if (patchBank.isValidSlot(slotIndex))
    {
        const auto& patch = patchBank.getPatch(slotIndex);
        bool oldFavorite = patch.isFavorite();
        
        if (oldFavorite != favorite)
        {
            undoManager.perform(new SetFavoriteAction(patchBank, slotIndex, favorite, oldFavorite));
            saveAll();
            sendChangeMessage();
        }
    }
}

void PatchManager::copyPatch(int sourceSlot, int destSlot)
{
    if (patchBank.isValidSlot(sourceSlot) && patchBank.isValidSlot(destSlot) && sourceSlot != destSlot)
    {
        undoManager.perform(new CopyPatchAction(patchBank, sourceSlot, destSlot));
        saveAll();
        sendChangeMessage();
    }
}

void PatchManager::batchRenamePatches(const juce::Array<int>& slotIndices, const juce::String& baseName)
{
    if (slotIndices.isEmpty())
        return;
    
    juce::Array<BatchRenameAction::PatchChange> changes;
    
    for (int slotIndex : slotIndices)
    {
        if (patchBank.isValidSlot(slotIndex))
        {
            const auto& patch = patchBank.getPatch(slotIndex);
            juce::String newName = baseName + " " + juce::String(slotIndex + 1);
            
            BatchRenameAction::PatchChange change;
            change.slotIndex = slotIndex;
            change.oldName = patch.getPatchName();
            change.newName = newName;
            changes.add(change);
        }
    }
    
    if (changes.size() > 0)
    {
        undoManager.perform(new BatchRenameAction(patchBank, changes));
        saveAll();
        sendChangeMessage();
    }
}

void PatchManager::clearPatchRange(int startSlot, int endSlot)
{
    if (!patchBank.isValidSlot(startSlot) || !patchBank.isValidSlot(endSlot))
        return;
    
    if (startSlot > endSlot)
        std::swap(startSlot, endSlot);
    
    juce::Array<BatchRenameAction::PatchChange> changes;
    
    for (int i = startSlot; i <= endSlot; ++i)
    {
        const auto& patch = patchBank.getPatch(i);
        juce::String defaultName = "Patch " + juce::String(i + 1).paddedLeft('0', 3);
        
        BatchRenameAction::PatchChange change;
        change.slotIndex = i;
        change.oldName = patch.getPatchName();
        change.newName = defaultName;
        changes.add(change);
    }
    
    if (changes.size() > 0)
    {
        undoManager.perform(new BatchRenameAction(patchBank, changes));
        saveAll();
        sendChangeMessage();
    }
}

void PatchManager::undo()
{
    undoManager.undo();
    saveAll();
    sendChangeMessage();
}

void PatchManager::redo()
{
    undoManager.redo();
    saveAll();
    sendChangeMessage();
}

bool PatchManager::canUndo() const noexcept
{
    return undoManager.canUndo();
}

bool PatchManager::canRedo() const noexcept
{
    return undoManager.canRedo();
}

juce::String PatchManager::getUndoDescription() const
{
    return undoManager.getUndoDescription();
}

juce::String PatchManager::getRedoDescription() const
{
    return undoManager.getRedoDescription();
}

void PatchManager::setMidiOutputPort(const juce::String& portName)
{
    deviceModel.setMidiOutputPortName(portName);
    auto result = midiManager.setOutputPort(portName);
    
    if (result.wasOk())
    {
        saveAll();
        sendChangeMessage();
    }
    else
    {
        // Log error (in production, you might want to show a user-friendly message)
        juce::Logger::writeToLog("Failed to set MIDI output port: " + result.getErrorMessage());
    }
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
    
    // Save MIDI learn mappings
    auto learnFile = persistenceManager.getDataDirectory().getChildFile("midi_learn.json");
    auto learnVar = midiLearnManager.toVar();
    juce::String jsonString = juce::JSON::toString(learnVar, true);
    learnFile.replaceWithText(jsonString);
}

void PatchManager::loadAll()
{
    persistenceManager.loadPatchBank(patchBank);
    persistenceManager.loadDeviceConfig(deviceModel);
    
    // Load MIDI learn mappings
    auto learnFile = persistenceManager.getDataDirectory().getChildFile("midi_learn.json");
    if (learnFile.existsAsFile())
    {
        juce::String jsonString = learnFile.loadFileAsString();
        auto learnVar = juce::JSON::parse(jsonString);
        if (!learnVar.isUndefined())
        {
            midiLearnManager.fromVar(learnVar);
        }
    }
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

void PatchManager::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &undoManager)
    {
        // Undo manager changed - notify UI to update undo/redo buttons
        sendChangeMessage();
    }
}


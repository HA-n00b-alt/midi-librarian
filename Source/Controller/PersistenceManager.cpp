#include "PersistenceManager.h"

PersistenceManager::PersistenceManager()
{
    // Get user's application data directory
    dataDirectory = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
        .getChildFile("MidiLibrarian");
    
    // Create directory if it doesn't exist
    if (!dataDirectory.exists())
    {
        dataDirectory.createDirectory();
    }
}

bool PersistenceManager::savePatchBank(const PatchBank& bank)
{
    auto file = getPatchesFile();
    auto var = bank.toVar();
    
    juce::String jsonString = juce::JSON::toString(var, true);
    
    juce::TemporaryFile tempFile(file);
    auto stream = tempFile.getFile().createOutputStream();
    
    if (stream == nullptr)
        return false;
    
    stream->writeString(jsonString);
    stream->flush();
    
    bool success = tempFile.overwriteTargetFileWithTemporary();
    return success;
}

bool PersistenceManager::loadPatchBank(PatchBank& bank)
{
    auto file = getPatchesFile();
    
    if (!file.existsAsFile())
        return false;
    
    juce::String jsonString = file.loadFileAsString();
    auto var = juce::JSON::parse(jsonString);
    
    if (var.isUndefined())
        return false;
    
    bank.fromVar(var);
    return true;
}

bool PersistenceManager::saveDeviceConfig(const DeviceModel& device)
{
    auto file = getConfigFile();
    auto var = device.toVar();
    
    juce::String jsonString = juce::JSON::toString(var, true);
    
    juce::TemporaryFile tempFile(file);
    auto stream = tempFile.getFile().createOutputStream();
    
    if (stream == nullptr)
        return false;
    
    stream->writeString(jsonString);
    stream->flush();
    
    bool success = tempFile.overwriteTargetFileWithTemporary();
    return success;
}

bool PersistenceManager::loadDeviceConfig(DeviceModel& device)
{
    auto file = getConfigFile();
    
    if (!file.existsAsFile())
        return false;
    
    juce::String jsonString = file.loadFileAsString();
    auto var = juce::JSON::parse(jsonString);
    
    if (var.isUndefined())
        return false;
    
    device.fromVar(var);
    return true;
}

bool PersistenceManager::exportToFile(const PatchBank& bank, const juce::File& file)
{
    auto var = bank.toVar();
    juce::String jsonString = juce::JSON::toString(var, true);
    
    juce::TemporaryFile tempFile(file);
    auto stream = tempFile.getFile().createOutputStream();
    
    if (stream == nullptr)
        return false;
    
    stream->writeString(jsonString);
    stream->flush();
    
    bool success = tempFile.overwriteTargetFileWithTemporary();
    return success;
}

bool PersistenceManager::importFromFile(PatchBank& bank, const juce::File& file)
{
    if (!file.existsAsFile())
        return false;
    
    juce::String jsonString = file.loadFileAsString();
    auto var = juce::JSON::parse(jsonString);
    
    if (var.isUndefined())
        return false;
    
    bank.fromVar(var);
    return true;
}

juce::File PersistenceManager::getDataDirectory() const
{
    return dataDirectory;
}

juce::File PersistenceManager::getPatchesFile() const
{
    return dataDirectory.getChildFile("patches.json");
}

juce::File PersistenceManager::getConfigFile() const
{
    return dataDirectory.getChildFile("config.json");
}


#include "DeviceTemplateManager.h"
#include "PersistenceManager.h"

DeviceTemplateManager::DeviceTemplateManager()
{
    // Get templates directory
    auto dataDir = PersistenceManager().getDataDirectory();
    templatesDirectory = dataDir.getChildFile("templates");
    ensureTemplatesDirectoryExists();
    
    // Initialize factory templates
    initializeFactoryTemplates();
    
    // Load custom templates from disk
    loadAllTemplates();
}

juce::Array<DeviceTemplate> DeviceTemplateManager::getAvailableTemplates() const
{
    return templates;
}

DeviceTemplate DeviceTemplateManager::getTemplate(const juce::Identifier& deviceID) const
{
    for (const auto& t : templates)
    {
        if (t.getDeviceID() == deviceID)
            return t;
    }
    
    // Return generic template if not found
    return DeviceTemplate::createGeneric();
}

bool DeviceTemplateManager::hasTemplate(const juce::Identifier& deviceID) const
{
    for (const auto& t : templates)
    {
        if (t.getDeviceID() == deviceID)
            return true;
    }
    return false;
}

void DeviceTemplateManager::initializeFactoryTemplates()
{
    templates.clear();
    
    // Add factory templates
    templates.add(DeviceTemplate::createGeneric());
    templates.add(DeviceTemplate::createRolandJV1080());
    templates.add(DeviceTemplate::createYamahaDX7());
    templates.add(DeviceTemplate::createKorgM1());
}

bool DeviceTemplateManager::saveTemplate(const DeviceTemplate& template_)
{
    ensureTemplatesDirectoryExists();
    
    auto file = templatesDirectory.getChildFile(template_.getDeviceID().toString() + ".json");
    auto var = template_.toVar();
    juce::String jsonString = juce::JSON::toString(var, true);
    
    juce::TemporaryFile tempFile(file);
    auto stream = tempFile.getFile().createOutputStream();
    
    if (stream == nullptr)
        return false;
    
    stream->writeString(jsonString);
    stream->flush();
    
    bool success = tempFile.overwriteTargetFileWithTemporary();
    
    if (success)
    {
        // Reload templates
        loadAllTemplates();
    }
    
    return success;
}

bool DeviceTemplateManager::loadTemplate(const juce::Identifier& deviceID, DeviceTemplate& template_)
{
    auto file = templatesDirectory.getChildFile(deviceID.toString() + ".json");
    
    if (!file.existsAsFile())
        return false;
    
    juce::String jsonString = file.loadFileAsString();
    auto var = juce::JSON::parse(jsonString);
    
    if (var.isUndefined())
        return false;
    
    template_ = DeviceTemplate::fromVar(var);
    return true;
}

juce::Array<DeviceTemplate> DeviceTemplateManager::loadAllTemplates()
{
    juce::Array<DeviceTemplate> loadedTemplates;
    
    if (!templatesDirectory.exists())
        return loadedTemplates;
    
    auto files = templatesDirectory.findChildFiles(juce::File::findFiles, false, "*.json");
    
    for (const auto& file : files)
    {
        juce::String jsonString = file.loadFileAsString();
        auto var = juce::JSON::parse(jsonString);
        
        if (!var.isUndefined())
        {
            auto template_ = DeviceTemplate::fromVar(var);
            loadedTemplates.add(template_);
            
            // Add to main templates array if not already present
            bool found = false;
            for (auto& t : templates)
            {
                if (t.getDeviceID() == template_.getDeviceID())
                {
                    t = template_; // Update existing
                    found = true;
                    break;
                }
            }
            
            if (!found)
            {
                templates.add(template_);
            }
        }
    }
    
    return loadedTemplates;
}

juce::File DeviceTemplateManager::getTemplatesDirectory() const
{
    return templatesDirectory;
}

void DeviceTemplateManager::ensureTemplatesDirectoryExists()
{
    if (!templatesDirectory.exists())
    {
        templatesDirectory.createDirectory();
    }
}


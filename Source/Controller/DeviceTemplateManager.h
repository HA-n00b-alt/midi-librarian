#pragma once

#include <JuceHeader.h>
#include "../Model/DeviceTemplate.h"

/**
 * Manages available device templates.
 * 
 * Loads templates from disk and provides factory templates.
 * Templates are stored in ~/Library/Application Support/MidiLibrarian/templates/
 */
class DeviceTemplateManager
{
public:
    DeviceTemplateManager();
    ~DeviceTemplateManager() = default;
    
    // Template access
    juce::Array<DeviceTemplate> getAvailableTemplates() const;
    DeviceTemplate getTemplate(const juce::Identifier& deviceID) const;
    bool hasTemplate(const juce::Identifier& deviceID) const;
    
    // Factory templates
    void initializeFactoryTemplates();
    
    // Load/Save templates
    bool saveTemplate(const DeviceTemplate& template_);
    bool loadTemplate(const juce::Identifier& deviceID, DeviceTemplate& template_);
    juce::Array<DeviceTemplate> loadAllTemplates();
    
    // Template directory
    juce::File getTemplatesDirectory() const;
    
private:
    juce::Array<DeviceTemplate> templates;
    juce::File templatesDirectory;
    
    void ensureTemplatesDirectoryExists();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeviceTemplateManager)
};


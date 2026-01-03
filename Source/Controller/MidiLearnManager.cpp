#include "MidiLearnManager.h"

bool MidiLearnManager::MidiMapping::matches(const juce::MidiMessage& message) const
{
    if (message.getChannel() != channel)
        return false;
    
    if (messageType == juce::MidiMessage::programChange && message.isProgramChange())
    {
        return message.getProgramChangeNumber() == data1;
    }
    else if (messageType == juce::MidiMessage::controller && message.isController())
    {
        return message.getControllerNumber() == data1 && message.getControllerValue() == data2;
    }
    else if (messageType == juce::MidiMessage::noteOn && message.isNoteOn())
    {
        return message.getNoteNumber() == data1;
    }
    
    return false;
}

juce::var MidiLearnManager::MidiMapping::toVar() const
{
    juce::DynamicObject::Ptr obj = new juce::DynamicObject();
    obj->setProperty("patchSlot", patchSlot);
    obj->setProperty("messageType", (int)messageType);
    obj->setProperty("channel", channel);
    obj->setProperty("data1", data1);
    obj->setProperty("data2", data2);
    return juce::var(obj);
}

MidiLearnManager::MidiMapping MidiLearnManager::MidiMapping::fromVar(const juce::var& v)
{
    MidiMapping mapping;
    
    if (auto* obj = v.getDynamicObject())
    {
        mapping.patchSlot = obj->getProperty("patchSlot");
        mapping.messageType = (juce::MidiMessage::MidiMetaType)(int)obj->getProperty("messageType");
        mapping.channel = obj->getProperty("channel");
        mapping.data1 = obj->getProperty("data1");
        mapping.data2 = obj->getProperty("data2");
    }
    
    return mapping;
}

MidiLearnManager::MidiLearnManager()
{
}

void MidiLearnManager::startLearning(int patchSlot)
{
    learningSlot = patchSlot;
    sendChangeMessage();
}

void MidiLearnManager::stopLearning()
{
    learningSlot = -1;
    sendChangeMessage();
}

void MidiLearnManager::addMapping(const MidiMapping& mapping)
{
    // Remove existing mapping for this patch slot
    removeMapping(mapping.patchSlot);
    
    mappings.add(mapping);
    sendChangeMessage();
}

void MidiLearnManager::removeMapping(int patchSlot)
{
    for (int i = mappings.size() - 1; i >= 0; --i)
    {
        if (mappings[i].patchSlot == patchSlot)
        {
            mappings.remove(i);
        }
    }
    sendChangeMessage();
}

MidiLearnManager::MidiMapping* MidiLearnManager::findMapping(const juce::MidiMessage& message)
{
    for (auto& mapping : mappings)
    {
        if (mapping.matches(message))
            return &mapping;
    }
    return nullptr;
}

juce::Array<MidiLearnManager::MidiMapping> MidiLearnManager::getAllMappings() const
{
    return mappings;
}

void MidiLearnManager::processMidiMessage(const juce::MidiMessage& message)
{
    // If in learning mode, learn from this message
    if (learningSlot >= 0)
    {
        MidiMapping mapping;
        mapping.patchSlot = learningSlot;
        mapping.channel = message.getChannel();
        
        if (message.isProgramChange())
        {
            mapping.messageType = juce::MidiMessage::programChange;
            mapping.data1 = message.getProgramChangeNumber();
            mapping.data2 = 0;
        }
        else if (message.isController())
        {
            mapping.messageType = juce::MidiMessage::controller;
            mapping.data1 = message.getControllerNumber();
            mapping.data2 = message.getControllerValue();
        }
        else if (message.isNoteOn())
        {
            mapping.messageType = juce::MidiMessage::noteOn;
            mapping.data1 = message.getNoteNumber();
            mapping.data2 = message.getVelocity();
        }
        else
        {
            return; // Don't learn unsupported message types
        }
        
        addMapping(mapping);
        stopLearning();
        
        return;
    }
    
    // Check if this message matches any mapping
    if (auto* mapping = findMapping(message))
    {
        if (onPatchRecall)
        {
            onPatchRecall(mapping->patchSlot);
        }
    }
}

juce::var MidiLearnManager::toVar() const
{
    juce::Array<juce::var> mappingArray;
    for (const auto& mapping : mappings)
    {
        mappingArray.add(mapping.toVar());
    }
    return juce::var(mappingArray);
}

void MidiLearnManager::fromVar(const juce::var& v)
{
    mappings.clear();
    
    if (auto* arr = v.getArray())
    {
        for (const auto& var : *arr)
        {
            mappings.add(MidiMapping::fromVar(var));
        }
    }
    
    sendChangeMessage();
}


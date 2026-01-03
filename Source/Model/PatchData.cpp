#include "PatchData.h"

bool PatchData::matchesSearchQuery(const juce::String& query) const
{
    if (query.isEmpty())
        return true;
    
    auto lowerQuery = query.toLowerCase();
    auto lowerName = patchName.toLowerCase();
    
    // Match patch name
    if (lowerName.contains(lowerQuery))
        return true;
    
    // Match slot number
    auto slotString = juce::String(slotIndex + 1).paddedLeft('0', 3);
    if (slotString.contains(lowerQuery))
        return true;
    
    // Match tags
    for (const auto& tag : tags)
    {
        if (tag.toLowerCase().contains(lowerQuery))
            return true;
    }
    
    return false;
}

juce::var PatchData::toVar() const
{
    juce::DynamicObject::Ptr obj = new juce::DynamicObject();
    obj->setProperty("slotIndex", slotIndex);
    obj->setProperty("patchName", patchName);
    obj->setProperty("deviceID", deviceID.toString());
    obj->setProperty("isFavorite", isFavoriteFlag);
    
    // Serialize tags array
    juce::Array<juce::var> tagArray;
    for (const auto& tag : tags)
        tagArray.add(juce::var(tag));
    obj->setProperty("tags", juce::var(tagArray));
    
    return juce::var(obj);
}

PatchData PatchData::fromVar(const juce::var& v)
{
    if (auto* obj = v.getDynamicObject())
    {
        PatchData patch;
        patch.slotIndex = obj->getProperty("slotIndex");
        patch.patchName = obj->getProperty("patchName").toString();
        patch.deviceID = juce::Identifier(obj->getProperty("deviceID").toString());
        patch.isFavoriteFlag = obj->getProperty("isFavorite", false);
        
        // Deserialize tags array
        if (auto* tagArray = obj->getProperty("tags").getArray())
        {
            for (const auto& tagVar : *tagArray)
                patch.tags.add(tagVar.toString());
        }
        
        return patch;
    }
    return PatchData();
}


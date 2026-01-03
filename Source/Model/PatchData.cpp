#include "PatchData.h"

juce::var PatchData::toVar() const
{
    juce::DynamicObject::Ptr obj = new juce::DynamicObject();
    obj->setProperty("slotIndex", slotIndex);
    obj->setProperty("patchName", patchName);
    obj->setProperty("deviceID", deviceID.toString());
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
        return patch;
    }
    return PatchData();
}


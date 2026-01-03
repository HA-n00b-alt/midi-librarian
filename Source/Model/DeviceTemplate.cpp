#include "DeviceTemplate.h"

juce::var DeviceTemplate::toVar() const
{
    juce::DynamicObject::Ptr obj = new juce::DynamicObject();
    obj->setProperty("deviceName", deviceName);
    obj->setProperty("manufacturer", manufacturer);
    obj->setProperty("deviceID", deviceID.toString());
    obj->setProperty("minPatchNumber", minPatchNumber);
    obj->setProperty("maxPatchNumber", maxPatchNumber);
    obj->setProperty("useBankSelect", useBankSelect);
    obj->setProperty("useMSB", useMSB);
    obj->setProperty("useLSB", useLSB);
    obj->setProperty("defaultChannel", defaultChannel);
    return juce::var(obj);
}

DeviceTemplate DeviceTemplate::fromVar(const juce::var& v)
{
    DeviceTemplate template_;
    
    if (auto* obj = v.getDynamicObject())
    {
        template_.deviceName = obj->getProperty("deviceName").toString();
        template_.manufacturer = obj->getProperty("manufacturer").toString();
        template_.deviceID = juce::Identifier(obj->getProperty("deviceID").toString());
        template_.minPatchNumber = obj->getProperty("minPatchNumber");
        template_.maxPatchNumber = obj->getProperty("maxPatchNumber");
        template_.useBankSelect = obj->getProperty("useBankSelect", false);
        template_.useMSB = obj->getProperty("useMSB", true);
        template_.useLSB = obj->getProperty("useLSB", false);
        template_.defaultChannel = obj->getProperty("defaultChannel", 1);
    }
    
    return template_;
}

DeviceTemplate DeviceTemplate::createGeneric()
{
    DeviceTemplate t("Generic", "Generic", "generic");
    t.setPatchRange(0, 127);
    t.setDefaultChannel(1);
    return t;
}

DeviceTemplate DeviceTemplate::createRolandJV1080()
{
    DeviceTemplate t("JV-1080", "Roland", "roland_jv1080");
    t.setPatchRange(0, 127);
    t.setBankSelect(true, true, false); // Uses MSB only
    t.setDefaultChannel(1);
    return t;
}

DeviceTemplate DeviceTemplate::createYamahaDX7()
{
    DeviceTemplate t("DX7", "Yamaha", "yamaha_dx7");
    t.setPatchRange(0, 31); // DX7 has 32 patches
    t.setBankSelect(false); // No bank select
    t.setDefaultChannel(1);
    return t;
}

DeviceTemplate DeviceTemplate::createKorgM1()
{
    DeviceTemplate t("M1", "Korg", "korg_m1");
    t.setPatchRange(0, 127);
    t.setBankSelect(true, true, true); // Uses both MSB and LSB
    t.setDefaultChannel(1);
    return t;
}


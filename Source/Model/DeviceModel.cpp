#include "DeviceModel.h"

juce::var DeviceModel::toVar() const
{
    juce::DynamicObject::Ptr obj = new juce::DynamicObject();
    obj->setProperty("midiOutputPortName", midiOutputPortName);
    obj->setProperty("midiChannel", midiChannel + 1); // Store as 1-16
    obj->setProperty("deviceID", deviceID.toString());
    obj->setProperty("deviceTemplate", deviceTemplate.toVar());
    return juce::var(obj);
}

void DeviceModel::fromVar(const juce::var& v)
{
    if (auto* obj = v.getDynamicObject())
    {
        midiOutputPortName = obj->getProperty("midiOutputPortName").toString();
        int channel = obj->getProperty("midiChannel");
        setMidiChannel(channel); // This handles validation
        deviceID = juce::Identifier(obj->getProperty("deviceID").toString());
        
        // Load template if present
        if (obj->hasProperty("deviceTemplate"))
        {
            deviceTemplate = DeviceTemplate::fromVar(obj->getProperty("deviceTemplate"));
        }
    }
}


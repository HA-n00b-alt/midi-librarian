#include "PatchBank.h"

PatchBank::PatchBank()
{
    patches.ensureStorageAllocated(BANK_SIZE);
    initializeDefaults();
}

const PatchData& PatchBank::getPatch(int slotIndex) const
{
    jassert(isValidSlot(slotIndex));
    return patches[slotIndex];
}

PatchData& PatchBank::getPatch(int slotIndex)
{
    jassert(isValidSlot(slotIndex));
    return patches[slotIndex];
}

void PatchBank::setPatch(int slotIndex, const PatchData& patch)
{
    if (isValidSlot(slotIndex))
    {
        patches.set(slotIndex, patch);
        sendChangeMessage();
    }
}

void PatchBank::renamePatch(int slotIndex, const juce::String& newName)
{
    if (isValidSlot(slotIndex))
    {
        patches.getReference(slotIndex).setPatchName(newName);
        sendChangeMessage();
    }
}

bool PatchBank::isValidSlot(int slotIndex) const noexcept
{
    return slotIndex >= 0 && slotIndex < BANK_SIZE;
}

void PatchBank::clear()
{
    patches.clear();
    patches.ensureStorageAllocated(BANK_SIZE);
    for (int i = 0; i < BANK_SIZE; ++i)
    {
        patches.add(PatchData(i, "Init", juce::Identifier("generic")));
    }
    sendChangeMessage();
}

void PatchBank::initializeDefaults()
{
    patches.clear();
    patches.ensureStorageAllocated(BANK_SIZE);
    
    for (int i = 0; i < BANK_SIZE; ++i)
    {
        juce::String defaultName = "Patch " + juce::String(i + 1).paddedLeft('0', 3);
        patches.add(PatchData(i, defaultName, juce::Identifier("generic")));
    }
}

juce::var PatchBank::toVar() const
{
    juce::Array<juce::var> patchArray;
    for (const auto& patch : patches)
    {
        patchArray.add(patch.toVar());
    }
    return juce::var(patchArray);
}

void PatchBank::fromVar(const juce::var& v)
{
    if (auto* arr = v.getArray())
    {
        patches.clear();
        patches.ensureStorageAllocated(BANK_SIZE);
        
        for (int i = 0; i < arr->size() && i < BANK_SIZE; ++i)
        {
            patches.add(PatchData::fromVar(arr->getUnchecked(i)));
        }
        
        // Ensure we always have 128 patches
        while (patches.size() < BANK_SIZE)
        {
            int index = patches.size();
            juce::String defaultName = "Patch " + juce::String(index + 1).paddedLeft('0', 3);
            patches.add(PatchData(index, defaultName, juce::Identifier("generic")));
        }
        
        sendChangeMessage();
    }
}


#pragma once

#include <JuceHeader.h>
#include "PatchData.h"

/**
 * Manages a bank of 128 patches (standard MIDI program range).
 * 
 * This is the core Model class that holds all patch data.
 * It broadcasts changes so Views can update automatically.
 * 
 * Thread-safe: All operations should be called from the message thread.
 */
class PatchBank : public juce::ChangeBroadcaster
{
public:
    static constexpr int BANK_SIZE = 128;
    
    PatchBank();
    ~PatchBank() override = default;
    
    // Patch access
    const PatchData& getPatch(int slotIndex) const;
    PatchData& getPatch(int slotIndex);
    
    // Patch modification
    void setPatch(int slotIndex, const PatchData& patch);
    void renamePatch(int slotIndex, const juce::String& newName);
    
    // Validation
    bool isValidSlot(int slotIndex) const noexcept;
    
    // Bulk operations
    void clear();
    void initializeDefaults(); // Creates 128 patches with default names
    
    // Serialization
    juce::var toVar() const;
    void fromVar(const juce::var& v);
    
private:
    juce::Array<PatchData> patches;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchBank)
};


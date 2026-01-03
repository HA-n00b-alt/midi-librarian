#pragma once

#include <JuceHeader.h>

/**
 * Represents a single patch/program in the librarian.
 * 
 * This is a value-type class that holds patch metadata.
 * The actual patch data (parameters) would be stored in the device itself
 * or in a future device template system.
 */
class PatchData
{
public:
    PatchData() = default;
    
    PatchData(int slotIndex, const juce::String& patchName, const juce::Identifier& deviceID)
        : slotIndex(slotIndex)
        , patchName(patchName)
        , deviceID(deviceID)
    {
    }
    
    // Getters
    int getSlotIndex() const noexcept { return slotIndex; }
    juce::String getPatchName() const noexcept { return patchName; }
    juce::Identifier getDeviceID() const noexcept { return deviceID; }
    bool isFavorite() const noexcept { return isFavoriteFlag; }
    juce::StringArray getTags() const noexcept { return tags; }
    
    // Setters
    void setSlotIndex(int index) noexcept { slotIndex = index; }
    void setPatchName(const juce::String& name) noexcept { patchName = name; }
    void setDeviceID(const juce::Identifier& id) noexcept { deviceID = id; }
    void setFavorite(bool favorite) noexcept { isFavoriteFlag = favorite; }
    void setTags(const juce::StringArray& newTags) noexcept { tags = newTags; }
    void addTag(const juce::String& tag) noexcept { if (!tags.contains(tag)) tags.add(tag); }
    void removeTag(const juce::String& tag) noexcept { tags.removeString(tag); }
    
    // Comparison
    bool operator==(const PatchData& other) const noexcept
    {
        return slotIndex == other.slotIndex
            && patchName == other.patchName
            && deviceID == other.deviceID;
    }
    
    bool operator!=(const PatchData& other) const noexcept
    {
        return !(*this == other);
    }
    
    // Search/filter helpers
    bool matchesSearchQuery(const juce::String& query) const;
    bool hasTag(const juce::String& tag) const noexcept { return tags.contains(tag); }
    
    // Serialization helpers (used by PersistenceManager)
    juce::var toVar() const;
    static PatchData fromVar(const juce::var& v);
    
private:
    int slotIndex = 0;                    // 0-127 (MIDI program numbers)
    juce::String patchName = "Init";      // User-friendly name
    juce::Identifier deviceID = "generic"; // For future device template system
    bool isFavoriteFlag = false;          // Favorite/starred patch
    juce::StringArray tags;               // Tags/categories (bass, lead, pad, etc.)
};


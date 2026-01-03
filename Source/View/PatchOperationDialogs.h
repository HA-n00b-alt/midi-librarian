#pragma once

#include <JuceHeader.h>

/**
 * Dialog for selecting patch slots for copy operation.
 */
class CopyPatchDialog : public juce::Component,
                        public juce::ComboBox::Listener
{
public:
    CopyPatchDialog(int maxSlots = 128);
    ~CopyPatchDialog() override = default;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    
    int getSourceSlot() const noexcept { return sourceSlot; }
    int getDestSlot() const noexcept { return destSlot; }
    
private:
    juce::Label sourceLabel;
    juce::ComboBox sourceComboBox;
    juce::Label destLabel;
    juce::ComboBox destComboBox;
    
    int sourceSlot = 0;
    int destSlot = 0;
    int maxSlots;
    
    void updateSlots();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CopyPatchDialog)
};

/**
 * Dialog for selecting patch range for batch operations.
 */
class PatchRangeDialog : public juce::Component,
                         public juce::ComboBox::Listener
{
public:
    PatchRangeDialog(int maxSlots = 128);
    ~PatchRangeDialog() override = default;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    
    int getStartSlot() const noexcept { return startSlot; }
    int getEndSlot() const noexcept { return endSlot; }
    
private:
    juce::Label startLabel;
    juce::ComboBox startComboBox;
    juce::Label endLabel;
    juce::ComboBox endComboBox;
    
    int startSlot = 0;
    int endSlot = 0;
    int maxSlots;
    
    void updateSlots();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchRangeDialog)
};


#include "PatchOperationDialogs.h"
#include "ValhallaLookAndFeel.h"

CopyPatchDialog::CopyPatchDialog(int max)
    : maxSlots(max)
{
    sourceLabel.setText("Source Slot:", juce::dontSendNotification);
    sourceLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(sourceLabel);
    
    sourceComboBox.addListener(this);
    updateSlots();
    addAndMakeVisible(sourceComboBox);
    
    destLabel.setText("Destination Slot:", juce::dontSendNotification);
    destLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(destLabel);
    
    destComboBox.addListener(this);
    updateSlots();
    addAndMakeVisible(destComboBox);
    
    setSize(300, 120);
}

void CopyPatchDialog::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void CopyPatchDialog::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    const int labelWidth = 120;
    const int controlHeight = 30;
    const int spacing = 8;
    
    auto sourceRow = bounds.removeFromTop(controlHeight);
    sourceLabel.setBounds(sourceRow.removeFromLeft(labelWidth));
    sourceRow.removeFromLeft(spacing);
    sourceComboBox.setBounds(sourceRow);
    
    bounds.removeFromTop(spacing);
    
    auto destRow = bounds.removeFromTop(controlHeight);
    destLabel.setBounds(destRow.removeFromLeft(labelWidth));
    destRow.removeFromLeft(spacing);
    destComboBox.setBounds(destRow);
}

void CopyPatchDialog::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == &sourceComboBox)
    {
        sourceSlot = sourceComboBox.getSelectedId() - 1;
    }
    else if (comboBox == &destComboBox)
    {
        destSlot = destComboBox.getSelectedId() - 1;
    }
}

void CopyPatchDialog::updateSlots()
{
    sourceComboBox.clear();
    destComboBox.clear();
    
    for (int i = 0; i < maxSlots; ++i)
    {
        juce::String slotName = juce::String(i + 1).paddedLeft('0', 3) + " - Patch " + juce::String(i + 1);
        sourceComboBox.addItem(slotName, i + 1);
        destComboBox.addItem(slotName, i + 1);
    }
    
    sourceComboBox.setSelectedId(1, juce::dontSendNotification);
    destComboBox.setSelectedId(2, juce::dontSendNotification);
}

PatchRangeDialog::PatchRangeDialog(int max)
    : maxSlots(max)
{
    startLabel.setText("Start Slot:", juce::dontSendNotification);
    startLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(startLabel);
    
    startComboBox.addListener(this);
    updateSlots();
    addAndMakeVisible(startComboBox);
    
    endLabel.setText("End Slot:", juce::dontSendNotification);
    endLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(endLabel);
    
    endComboBox.addListener(this);
    updateSlots();
    addAndMakeVisible(endComboBox);
    
    setSize(300, 120);
}

void PatchRangeDialog::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PatchRangeDialog::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    const int labelWidth = 120;
    const int controlHeight = 30;
    const int spacing = 8;
    
    auto startRow = bounds.removeFromTop(controlHeight);
    startLabel.setBounds(startRow.removeFromLeft(labelWidth));
    startRow.removeFromLeft(spacing);
    startComboBox.setBounds(startRow);
    
    bounds.removeFromTop(spacing);
    
    auto endRow = bounds.removeFromTop(controlHeight);
    endLabel.setBounds(endRow.removeFromLeft(labelWidth));
    endRow.removeFromLeft(spacing);
    endComboBox.setBounds(endRow);
}

void PatchRangeDialog::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == &startComboBox)
    {
        startSlot = startComboBox.getSelectedId() - 1;
    }
    else if (comboBox == &endComboBox)
    {
        endSlot = endComboBox.getSelectedId() - 1;
    }
}

void PatchRangeDialog::updateSlots()
{
    startComboBox.clear();
    endComboBox.clear();
    
    for (int i = 0; i < maxSlots; ++i)
    {
        juce::String slotName = juce::String(i + 1).paddedLeft('0', 3) + " - Patch " + juce::String(i + 1);
        startComboBox.addItem(slotName, i + 1);
        endComboBox.addItem(slotName, i + 1);
    }
    
    startComboBox.setSelectedId(1, juce::dontSendNotification);
    endComboBox.setSelectedId(10, juce::dontSendNotification);
}


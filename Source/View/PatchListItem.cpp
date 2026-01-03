#include "PatchListItem.h"
#include "ValhallaLookAndFeel.h"

PatchListItem::PatchListItem(int slot, const juce::String& name)
    : slotIndex(slot)
    , patchName(name)
{
    // Slot number label
    slotLabel.setText(getDisplaySlotNumber(), juce::dontSendNotification);
    slotLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(slotLabel);
    
    // Patch name label (clickable to edit)
    nameLabel.setText(patchName, juce::dontSendNotification);
    nameLabel.setJustificationType(juce::Justification::centredLeft);
    nameLabel.setInterceptsMouseClicks(true, false);
    addAndMakeVisible(nameLabel);
    
    // Text editor for renaming (hidden by default)
    nameEditor.setMultiLine(false);
    nameEditor.setReturnKeyStartsNewLine(false);
    nameEditor.addListener(this);
    nameEditor.setVisible(false);
    addChildComponent(nameEditor);
    
    // Recall button
    recallButton.setButtonText("Recall");
    recallButton.addListener(this);
    addAndMakeVisible(recallButton);
    
    // Make entire row clickable for editing
    nameLabel.addMouseListener(this, false);
}

void PatchListItem::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    
    // Background
    auto& lf = getLookAndFeel();
    auto bgColour = isSelected
        ? static_cast<ValhallaLookAndFeel&>(lf).getAccentColour().withAlpha(0.1f)
        : static_cast<ValhallaLookAndFeel&>(lf).getBackgroundColour();
    
    g.setColour(bgColour);
    g.fillRect(bounds);
    
    // Subtle border
    g.setColour(static_cast<ValhallaLookAndFeel&>(lf).getBorderColour());
    g.drawLine(bounds.getBottomLeft(), bounds.getBottomRight(), 0.5f);
}

void PatchListItem::resized()
{
    auto bounds = getLocalBounds().reduced(4);
    const int slotWidth = 60;
    const int buttonWidth = 80;
    const int spacing = 8;
    
    slotLabel.setBounds(bounds.removeFromLeft(slotWidth));
    bounds.removeFromLeft(spacing);
    
    recallButton.setBounds(bounds.removeFromRight(buttonWidth));
    bounds.removeFromRight(spacing);
    
    if (isEditing)
    {
        nameEditor.setBounds(bounds);
    }
    else
    {
        nameLabel.setBounds(bounds);
    }
}

void PatchListItem::textEditorTextChanged(juce::TextEditor& editor)
{
    // Allow real-time editing
}

void PatchListItem::textEditorReturnKeyPressed(juce::TextEditor& editor)
{
    stopEditing(true);
}

void PatchListItem::textEditorEscapeKeyPressed(juce::TextEditor& editor)
{
    stopEditing(false);
}

void PatchListItem::textEditorFocusLost(juce::TextEditor& editor)
{
    stopEditing(true);
}

void PatchListItem::buttonClicked(juce::Button* button)
{
    if (button == &recallButton && onRecall)
    {
        onRecall(slotIndex);
    }
}

void PatchListItem::setPatchName(const juce::String& name)
{
    patchName = name;
    nameLabel.setText(patchName, juce::dontSendNotification);
    repaint();
}

void PatchListItem::setSelected(bool selected)
{
    if (isSelected != selected)
    {
        isSelected = selected;
        repaint();
    }
}

void PatchListItem::startEditing()
{
    if (!isEditing)
    {
        isEditing = true;
        nameEditor.setText(patchName, false);
        nameEditor.setVisible(true);
        nameLabel.setVisible(false);
        nameEditor.grabKeyboardFocus();
        nameEditor.selectAll();
        resized();
    }
}

void PatchListItem::stopEditing(bool commit)
{
    if (isEditing)
    {
        isEditing = false;
        nameEditor.setVisible(false);
        nameLabel.setVisible(true);
        
        if (commit && onRename)
        {
            juce::String newName = nameEditor.getText().trim();
            if (newName.isEmpty())
                newName = "Init";
            
            if (newName != patchName)
            {
                onRename(slotIndex, newName);
            }
        }
        
        resized();
    }
}

juce::String PatchListItem::getDisplaySlotNumber() const
{
    return juce::String(slotIndex + 1).paddedLeft('0', 3);
}

// Add mouse click handler
void PatchListItem::mouseDown(const juce::MouseEvent& e)
{
    if (e.eventComponent == &nameLabel && !isEditing)
    {
        startEditing();
    }
}


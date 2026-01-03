#pragma once

#include <JuceHeader.h>
#include "../Model/PatchData.h"

/**
 * Represents a single row in the patch list.
 * 
 * Displays slot number and patch name, with ability to rename inline.
 * Clicking the row recalls the patch (sends MIDI PC).
 */
class PatchListItem : public juce::Component,
                      public juce::TextEditor::Listener,
                      public juce::Button::Listener
{
public:
    PatchListItem(int slotIndex, const juce::String& patchName);
    ~PatchListItem() override = default;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // TextEditor::Listener
    void textEditorTextChanged(juce::TextEditor& editor) override;
    void textEditorReturnKeyPressed(juce::TextEditor& editor) override;
    void textEditorEscapeKeyPressed(juce::TextEditor& editor) override;
    void textEditorFocusLost(juce::TextEditor& editor) override;
    
    // Button::Listener
    void buttonClicked(juce::Button* button) override;
    
    // Callbacks
    std::function<void(int slotIndex, const juce::String& newName)> onRename;
    std::function<void(int slotIndex)> onRecall;
    std::function<void(int slotIndex, bool favorite)> onFavoriteChanged;
    std::function<void(int slotIndex)> onLearn;
    
    void setPatchName(const juce::String& name);
    void setSelected(bool selected);
    void setFavorite(bool favorite);
    bool isFavorite() const noexcept { return isFavoriteFlag; }
    void setLearning(bool learning) noexcept { isLearning = learning; repaint(); }
    
    void mouseDown(const juce::MouseEvent& e) override;
    
private:
    int slotIndex;
    juce::String patchName;
    bool isSelected = false;
    bool isEditing = false;
    bool isFavoriteFlag = false;
    bool isLearning = false;
    
    juce::Label slotLabel;
    juce::Label nameLabel;
    juce::TextEditor nameEditor;
    juce::TextButton recallButton;
    juce::TextButton favoriteButton;
    juce::TextButton learnButton;
    
    void startEditing();
    void stopEditing(bool commit);
    juce::String getDisplaySlotNumber() const;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchListItem)
};


#pragma once

#include <JuceHeader.h>

/**
 * Search bar component for filtering patches.
 * 
 * Provides real-time search with text input and filter options
 * (favorites, tags, etc.).
 */
class SearchBar : public juce::Component,
                  public juce::TextEditor::Listener
{
public:
    SearchBar();
    ~SearchBar() override = default;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // TextEditor::Listener
    void textEditorTextChanged(juce::TextEditor& editor) override;
    
    // Callbacks
    std::function<void(const juce::String& query)> onSearchTextChanged;
    std::function<void(bool showFavoritesOnly)> onFavoritesFilterChanged;
    
    juce::String getSearchQuery() const noexcept { return searchEditor.getText(); }
    bool isFavoritesOnly() const noexcept { return favoritesOnly; }
    
private:
    juce::Label searchLabel;
    juce::TextEditor searchEditor;
    juce::TextButton favoritesButton;
    bool favoritesOnly = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SearchBar)
};


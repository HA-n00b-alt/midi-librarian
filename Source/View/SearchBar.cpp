#include "SearchBar.h"
#include "ValhallaLookAndFeel.h"

SearchBar::SearchBar()
{
    searchLabel.setText("Search:", juce::dontSendNotification);
    searchLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(searchLabel);
    
    searchEditor.setMultiLine(false);
    searchEditor.setReturnKeyStartsNewLine(false);
    searchEditor.addListener(this);
    searchEditor.setTextToShowWhenEmpty("Search patches...", juce::Colours::grey);
    addAndMakeVisible(searchEditor);
    
    favoritesButton.setButtonText("★ Favorites");
    favoritesButton.setClickingTogglesState(true);
    favoritesButton.onClick = [this]()
    {
        favoritesOnly = favoritesButton.getToggleState();
        if (onFavoritesFilterChanged)
            onFavoritesFilterChanged(favoritesOnly);
    };
    addAndMakeVisible(favoritesButton);
}

void SearchBar::paint(juce::Graphics& g)
{
    // Background handled by parent
}

void SearchBar::resized()
{
    auto bounds = getLocalBounds().reduced(4);
    const int labelWidth = 60;
    const int buttonWidth = 100;
    const int spacing = 8;
    
    searchLabel.setBounds(bounds.removeFromLeft(labelWidth));
    bounds.removeFromLeft(spacing);
    
    favoritesButton.setBounds(bounds.removeFromRight(buttonWidth));
    bounds.removeFromRight(spacing);
    
    searchEditor.setBounds(bounds);
}

void SearchBar::textEditorTextChanged(juce::TextEditor& editor)
{
    if (&editor == &searchEditor && onSearchTextChanged)
    {
        onSearchTextChanged(editor.getText());
    }
}


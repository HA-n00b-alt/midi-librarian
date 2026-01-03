#include "ValhallaLookAndFeel.h"

ValhallaLookAndFeel::ValhallaLookAndFeel()
{
    setupColours();
    setupFonts();
}

void ValhallaLookAndFeel::setupColours()
{
    backgroundColour = juce::Colour::fromFloatRGBA(
        BACKGROUND_BRIGHTNESS, BACKGROUND_BRIGHTNESS, BACKGROUND_BRIGHTNESS, 1.0f);
    
    accentColour = juce::Colour::fromHSV(
        ACCENT_HUE, ACCENT_SATURATION, ACCENT_BRIGHTNESS, 1.0f);
    
    textColour = juce::Colour::fromFloatRGBA(0.1f, 0.1f, 0.1f, 1.0f);
    borderColour = juce::Colour::fromFloatRGBA(0.85f, 0.85f, 0.85f, 1.0f);
}

void ValhallaLookAndFeel::setupFonts()
{
    // Use system font for crisp rendering (using new FontOptions API)
    defaultFont = juce::Font(juce::FontOptions().withHeight(14.0f));
}

juce::Colour ValhallaLookAndFeel::getBackgroundColour() const
{
    return backgroundColour;
}

juce::Colour ValhallaLookAndFeel::getAccentColour() const
{
    return accentColour;
}

juce::Colour ValhallaLookAndFeel::getTextColour() const
{
    return textColour;
}

juce::Colour ValhallaLookAndFeel::getBorderColour() const
{
    return borderColour;
}

void ValhallaLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button,
                                               const juce::Colour& backgroundColour,
                                               bool shouldDrawButtonAsHighlighted,
                                               bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    auto cornerSize = 4.0f;
    
    // Background
    g.setColour(this->backgroundColour);
    g.fillRoundedRectangle(bounds, cornerSize);
    
    // Border
    g.setColour(borderColour);
    g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
    
    // Accent fill on hover/press
    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
    {
        g.setColour(accentColour.withAlpha(shouldDrawButtonAsDown ? 0.3f : 0.15f));
        g.fillRoundedRectangle(bounds, cornerSize);
    }
}

void ValhallaLookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton& button,
                                         bool shouldDrawButtonAsHighlighted,
                                         bool shouldDrawButtonAsDown)
{
    g.setColour(textColour);
    g.setFont(defaultFont);
    
    auto textArea = button.getLocalBounds();
    g.drawFittedText(button.getButtonText(), textArea,
                     juce::Justification::centred, 1);
}

void ValhallaLookAndFeel::drawComboBox(juce::Graphics& g, int width, int height,
                                      bool isButtonDown, int buttonX, int buttonY,
                                      int buttonW, int buttonH, juce::ComboBox& box)
{
    auto bounds = juce::Rectangle<float>(0, 0, width, height);
    auto cornerSize = 4.0f;
    
    // Background
    g.setColour(backgroundColour);
    g.fillRoundedRectangle(bounds, cornerSize);
    
    // Border
    g.setColour(borderColour);
    g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
    
    // Arrow indicator
    auto arrowBounds = juce::Rectangle<float>(buttonX, buttonY, buttonW, buttonH)
        .reduced(4.0f);
    juce::Path arrow;
    arrow.addTriangle(arrowBounds.getCentreX(), arrowBounds.getY() + 3.0f,
                     arrowBounds.getX(), arrowBounds.getBottom() - 3.0f,
                     arrowBounds.getRight(), arrowBounds.getBottom() - 3.0f);
    g.setColour(textColour.withAlpha(0.7f));
    g.fillPath(arrow);
}

void ValhallaLookAndFeel::drawComboBoxTextWhenNothingSelected(juce::Graphics& g, juce::ComboBox& box,
                                                             juce::Label& label)
{
    g.setColour(textColour.withAlpha(0.5f));
    g.setFont(defaultFont);
    g.drawFittedText(box.getTextWhenNothingSelected(), label.getBounds(),
                     juce::Justification::centredLeft, 1);
}

void ValhallaLookAndFeel::drawTextEditorOutline(juce::Graphics& g, int width, int height,
                                               juce::TextEditor& editor)
{
    auto bounds = juce::Rectangle<float>(0, 0, width, height);
    auto cornerSize = 4.0f;
    
    if (editor.isEnabled())
    {
        g.setColour(borderColour);
        g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
        
        if (editor.hasKeyboardFocus(false))
        {
            g.setColour(accentColour);
            g.drawRoundedRectangle(bounds, cornerSize, 2.0f);
        }
    }
}

void ValhallaLookAndFeel::drawScrollbar(juce::Graphics& g, juce::ScrollBar& scrollbar,
                                        int x, int y, int width, int height,
                                        bool isScrollbarVertical, int thumbStartPosition,
                                        int thumbSize, bool isMouseOver, bool isMouseDown)
{
    auto thumbArea = isScrollbarVertical
        ? juce::Rectangle<int>(x, thumbStartPosition, width, thumbSize)
        : juce::Rectangle<int>(thumbStartPosition, y, thumbSize, height);
    
    g.setColour(backgroundColour);
    g.fillRect(x, y, width, height);
    
    auto thumbColour = isMouseDown ? accentColour
                     : isMouseOver ? accentColour.withAlpha(0.5f)
                     : borderColour;
    
    g.setColour(thumbColour);
    g.fillRoundedRectangle(thumbArea.toFloat(), 2.0f);
}

juce::Font ValhallaLookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight)
{
    return defaultFont.withHeight(juce::jmax(14.0f, buttonHeight * 0.5f));
}

juce::Font ValhallaLookAndFeel::getComboBoxFont(juce::ComboBox&)
{
    return defaultFont;
}

juce::Font ValhallaLookAndFeel::getLabelFont(juce::Label&)
{
    return defaultFont;
}

int ValhallaLookAndFeel::getDefaultScrollbarWidth()
{
    return 12; // Thin, modern scrollbar
}


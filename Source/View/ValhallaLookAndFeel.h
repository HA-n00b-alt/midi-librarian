#pragma once

#include <JuceHeader.h>

/**
 * Custom LookAndFeel implementing the Valhalla DSP aesthetic:
 * - Clean, minimal design
 * - White/light background
 * - Single accent color
 * - Large, touch-friendly elements
 * - No skeuomorphism
 * - Crisp, modern typography
 * 
 * This class overrides JUCE's default drawing methods to achieve
 * the desired visual style across all components.
 */
class ValhallaLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ValhallaLookAndFeel();
    ~ValhallaLookAndFeel() override = default;
    
    // Override key drawing methods for consistent styling
    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                             const juce::Colour& backgroundColour,
                             bool shouldDrawButtonAsHighlighted,
                             bool shouldDrawButtonAsDown) override;
    
    void drawButtonText(juce::Graphics& g, juce::TextButton& button,
                       bool shouldDrawButtonAsHighlighted,
                       bool shouldDrawButtonAsDown) override;
    
    void drawComboBox(juce::Graphics& g, int width, int height,
                     bool isButtonDown, int buttonX, int buttonY,
                     int buttonW, int buttonH, juce::ComboBox& box) override;
    
    void drawComboBoxTextWhenNothingSelected(juce::Graphics& g, juce::ComboBox& box,
                                            juce::Label& label) override;
    
    void drawTextEditorOutline(juce::Graphics& g, int width, int height,
                              juce::TextEditor& editor) override;
    
    void drawScrollbar(juce::Graphics& g, juce::ScrollBar& scrollbar,
                      int x, int y, int width, int height,
                      bool isScrollbarVertical, int thumbStartPosition,
                      int thumbSize, bool isMouseOver, bool isMouseDown) override;
    
    juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override;
    juce::Font getComboBoxFont(juce::ComboBox&) override;
    juce::Font getLabelFont(juce::Label&) override;
    
    int getDefaultScrollbarWidth() override;
    
    // Color scheme
    static constexpr float BACKGROUND_BRIGHTNESS = 0.98f;
    static constexpr float ACCENT_HUE = 0.6f; // Blue-green (adjust as needed)
    static constexpr float ACCENT_SATURATION = 0.7f;
    static constexpr float ACCENT_BRIGHTNESS = 0.5f;
    
    juce::Colour getBackgroundColour() const;
    juce::Colour getAccentColour() const;
    juce::Colour getTextColour() const;
    juce::Colour getBorderColour() const;
    
private:
    juce::Colour backgroundColour;
    juce::Colour accentColour;
    juce::Colour textColour;
    juce::Colour borderColour;
    juce::Font defaultFont;
    
    void setupColours();
    void setupFonts();
};


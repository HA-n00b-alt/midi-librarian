#include "DeviceStatusIndicator.h"
#include "ValhallaLookAndFeel.h"

DeviceStatusIndicator::DeviceStatusIndicator()
{
    setSize(100, 24);
}

void DeviceStatusIndicator::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    auto& lf = getLookAndFeel();
    
    // Status circle
    auto circleSize = 12.0f;
    auto circleX = 4.0f;
    auto circleY = (bounds.getHeight() - circleSize) * 0.5f;
    
    juce::Colour statusColour = connected 
        ? juce::Colours::green
        : juce::Colours::red;
    
    g.setColour(statusColour);
    g.fillEllipse(circleX, circleY, circleSize, circleSize);
    
    // Status text
    if (statusText.isNotEmpty())
    {
        g.setColour(static_cast<ValhallaLookAndFeel&>(lf).getTextColour());
        g.setFont(12.0f);
        g.drawText(statusText, 
                  bounds.removeFromLeft(20).removeFromRight(getWidth() - 20),
                  juce::Justification::centredLeft);
    }
}

void DeviceStatusIndicator::resized()
{
    // Auto-sized based on content
}

void DeviceStatusIndicator::setConnected(bool isConnected, const juce::String& text)
{
    if (connected != isConnected || statusText != text)
    {
        connected = isConnected;
        statusText = text;
        repaint();
    }
}


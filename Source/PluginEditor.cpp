#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiLibrarianAudioProcessorEditor::MidiLibrarianAudioProcessorEditor(MidiLibrarianAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , deviceSelectorPanel(p.getPatchManager())
    , patchListPanel(p.getPatchManager())
{
    // Apply custom look and feel
    setLookAndFeel(&valhallaLookAndFeel);
    
    // Add child components
    addAndMakeVisible(deviceSelectorPanel);
    addAndMakeVisible(patchListPanel);
    
    // Set initial window size (resizable)
    // Minimum size for comfortable use
    setResizable(true, true);
    setResizeLimits(400, 300, 2000, 1500);
    setSize(600, 800);
}

MidiLibrarianAudioProcessorEditor::~MidiLibrarianAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void MidiLibrarianAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Fill background with look and feel color
    g.fillAll(valhallaLookAndFeel.getBackgroundColour());
}

void MidiLibrarianAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced(8);
    
    // Device selector at top
    const int selectorHeight = 80;
    deviceSelectorPanel.setBounds(bounds.removeFromTop(selectorHeight));
    
    bounds.removeFromTop(8); // Spacing
    
    // Patch list takes remaining space
    patchListPanel.setBounds(bounds);
}


#pragma once

#include <JuceHeader.h>
#include "../Controller/MidiManager.h"

/**
 * Real-time MIDI monitoring panel.
 * 
 * Displays incoming and outgoing MIDI messages for debugging.
 * Shows message type, channel, data, and timestamp.
 */
class MidiMonitorPanel : public juce::Component,
                         public juce::TextEditor::Listener
{
public:
    MidiMonitorPanel();
    ~MidiMonitorPanel() override = default;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // TextEditor::Listener
    void textEditorTextChanged(juce::TextEditor& editor) override;
    
    // MIDI message logging
    void logMidiMessage(const juce::MidiMessage& message, bool isOutgoing);
    void clearLog();
    
    // Settings
    void setMaxLines(int maxLines) noexcept { maxLogLines = maxLines; }
    int getMaxLines() const noexcept { return maxLogLines; }
    
private:
    juce::TextEditor logEditor;
    juce::TextButton clearButton;
    juce::TextButton exportButton;
    int maxLogLines = 100;
    
    juce::String formatMidiMessage(const juce::MidiMessage& message, bool isOutgoing) const;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiMonitorPanel)
};


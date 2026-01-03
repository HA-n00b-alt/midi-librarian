#include "MidiMonitorPanel.h"
#include "ValhallaLookAndFeel.h"

MidiMonitorPanel::MidiMonitorPanel()
{
    logEditor.setMultiLine(true);
    logEditor.setReadOnly(true);
    // Create monospaced font - FontOptions doesn't have withFamily, so use Font constructor directly
    juce::Font monospacedFont(juce::Font::getDefaultMonospacedFontName(), 11.0f, juce::Font::plain);
    logEditor.setFont(monospacedFont);
    logEditor.setScrollbarsShown(true);
    addAndMakeVisible(logEditor);
    
    clearButton.setButtonText("Clear");
    clearButton.onClick = [this]() { clearLog(); };
    addAndMakeVisible(clearButton);
    
    exportButton.setButtonText("Export");
    exportButton.onClick = [this]()
    {
        juce::FileChooser chooser("Export MIDI Log", juce::File(), "*.txt");
        auto chooserFlags = juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::canSelectFiles;
        chooser.launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            if (file != juce::File())
            {
                file.replaceWithText(logEditor.getText());
            }
        });
    };
    addAndMakeVisible(exportButton);
}

void MidiMonitorPanel::paint(juce::Graphics& g)
{
    // Background handled by parent
}

void MidiMonitorPanel::resized()
{
    auto bounds = getLocalBounds().reduced(4);
    
    auto buttonRow = bounds.removeFromTop(30);
    exportButton.setBounds(buttonRow.removeFromRight(80));
    buttonRow.removeFromRight(8);
    clearButton.setBounds(buttonRow.removeFromRight(80));
    bounds.removeFromTop(4);
    
    logEditor.setBounds(bounds);
}

void MidiMonitorPanel::textEditorTextChanged(juce::TextEditor& editor)
{
    // Read-only, so no action needed
}

void MidiMonitorPanel::logMidiMessage(const juce::MidiMessage& message, bool isOutgoing)
{
    juce::String logLine = formatMidiMessage(message, isOutgoing);
    
    juce::MessageManager::callAsync([this, logLine]()
    {
        auto currentText = logEditor.getText();
        currentText += logLine + "\n";
        
        // Limit to max lines
        auto lines = juce::StringArray::fromLines(currentText);
        if (lines.size() > maxLogLines)
        {
            lines.removeRange(0, lines.size() - maxLogLines);
            currentText = lines.joinIntoString("\n") + "\n";
        }
        
        logEditor.setText(currentText);
        logEditor.moveCaretToEnd();
    });
}

void MidiMonitorPanel::clearLog()
{
    logEditor.clear();
}

juce::String MidiMonitorPanel::formatMidiMessage(const juce::MidiMessage& message, bool isOutgoing) const
{
    juce::String direction = isOutgoing ? "OUT" : "IN ";
    juce::String timestamp = juce::Time::getCurrentTime().toString(true, true, false, true);
    juce::String description;
    
    if (message.isProgramChange())
    {
        int channel = message.getChannel();
        int program = message.getProgramChangeNumber();
        description = juce::String::formatted("PC Ch%d Prg%d", channel, program);
    }
    else if (message.isController())
    {
        int channel = message.getChannel();
        int controller = message.getControllerNumber();
        int value = message.getControllerValue();
        description = juce::String::formatted("CC Ch%d #%d=%d", channel, controller, value);
    }
    else if (message.isNoteOn())
    {
        int channel = message.getChannel();
        int note = message.getNoteNumber();
        int velocity = message.getVelocity();
        description = juce::String::formatted("NoteOn Ch%d Note%d Vel%d", channel, note, velocity);
    }
    else if (message.isNoteOff())
    {
        int channel = message.getChannel();
        int note = message.getNoteNumber();
        description = juce::String::formatted("NoteOff Ch%d Note%d", channel, note);
    }
    else if (message.isSysEx())
    {
        description = "SysEx (" + juce::String(message.getSysExDataSize()) + " bytes)";
    }
    else
    {
        description = "Other (0x" + juce::String::toHexString(message.getRawData(), message.getRawDataSize()) + ")";
    }
    
    // Convert String objects to C strings for formatted (variadic functions can't handle String objects)
    auto timeStr = timestamp.substring(11, 19);
    return juce::String::formatted("[%s] %s %s", timeStr.toRawUTF8(), direction.toRawUTF8(), description.toRawUTF8());
}


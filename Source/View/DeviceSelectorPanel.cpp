#include "DeviceSelectorPanel.h"
#include "ValhallaLookAndFeel.h"

DeviceSelectorPanel::DeviceSelectorPanel(PatchManager& pm)
    : patchManager(pm)
{
    // Port selection
    portLabel.setText("MIDI Output:", juce::dontSendNotification);
    portLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(portLabel);
    
    portComboBox.addListener(this);
    addAndMakeVisible(portComboBox);
    
    // Channel selection
    channelLabel.setText("Channel:", juce::dontSendNotification);
    channelLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(channelLabel);
    
    channelComboBox.addListener(this);
    updateChannelComboBox();
    addAndMakeVisible(channelComboBox);
    
    // Listen for MIDI device changes
    patchManager.getMidiManager().addChangeListener(this);
    
    // Initial refresh
    refreshPortList();
    
    // Set initial values from model
    auto currentPort = patchManager.getDeviceModel().getMidiOutputPortName();
    if (currentPort.isNotEmpty())
    {
        portComboBox.setText(currentPort, juce::dontSendNotification);
    }
    
    channelComboBox.setSelectedId(patchManager.getDeviceModel().getMidiChannelDisplay(),
                                  juce::dontSendNotification);
}

DeviceSelectorPanel::~DeviceSelectorPanel()
{
    patchManager.getMidiManager().removeChangeListener(this);
}

void DeviceSelectorPanel::paint(juce::Graphics& g)
{
    // Background is handled by parent
}

void DeviceSelectorPanel::resized()
{
    auto bounds = getLocalBounds().reduced(8);
    const int labelWidth = 100;
    const int controlHeight = 32;
    const int spacing = 8;
    
    // Port selection row
    auto portRow = bounds.removeFromTop(controlHeight);
    portLabel.setBounds(portRow.removeFromLeft(labelWidth));
    portRow.removeFromLeft(spacing);
    portComboBox.setBounds(portRow);
    
    bounds.removeFromTop(spacing);
    
    // Channel selection row
    auto channelRow = bounds.removeFromTop(controlHeight);
    channelLabel.setBounds(channelRow.removeFromLeft(labelWidth));
    channelRow.removeFromLeft(spacing);
    channelComboBox.setBounds(channelRow.removeFromLeft(80));
}

void DeviceSelectorPanel::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &portComboBox)
    {
        juce::String selectedPort = portComboBox.getText();
        patchManager.setMidiOutputPort(selectedPort);
    }
    else if (comboBoxThatHasChanged == &channelComboBox)
    {
        int selectedChannel = channelComboBox.getSelectedId();
        if (selectedChannel > 0)
        {
            patchManager.setMidiChannel(selectedChannel);
        }
    }
}

void DeviceSelectorPanel::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    refreshPortList();
}

void DeviceSelectorPanel::refreshPortList()
{
    portComboBox.clear();
    portComboBox.addItem("(No Output)", 1);
    
    auto ports = patchManager.getMidiManager().getAvailableOutputPorts();
    for (int i = 0; i < ports.size(); ++i)
    {
        portComboBox.addItem(ports[i], i + 2);
    }
    
    // Restore selection if still available
    auto currentPort = patchManager.getDeviceModel().getMidiOutputPortName();
    if (currentPort.isNotEmpty())
    {
        int index = ports.indexOf(currentPort);
        if (index >= 0)
        {
            portComboBox.setSelectedId(index + 2, juce::dontSendNotification);
        }
    }
}

void DeviceSelectorPanel::updateChannelComboBox()
{
    channelComboBox.clear();
    for (int i = 1; i <= 16; ++i)
    {
        channelComboBox.addItem(juce::String(i), i);
    }
}


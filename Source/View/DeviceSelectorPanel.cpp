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
    
    // Status indicator
    addAndMakeVisible(statusIndicator);
    
    // Channel selection
    channelLabel.setText("Channel:", juce::dontSendNotification);
    channelLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(channelLabel);
    
    channelComboBox.addListener(this);
    updateChannelComboBox();
    addAndMakeVisible(channelComboBox);
    
    // Bank selection
    bankLabel.setText("Bank:", juce::dontSendNotification);
    bankLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(bankLabel);
    
    bankComboBox.addListener(this);
    updateBankComboBox();
    addAndMakeVisible(bankComboBox);
    
    useMSBButton.setButtonText("MSB");
    useMSBButton.setClickingTogglesState(true);
    useMSBButton.setToggleState(true, juce::dontSendNotification);
    useMSBButton.addListener(this);
    addAndMakeVisible(useMSBButton);
    
    // Listen for MIDI device changes
    patchManager.getMidiManager().addChangeListener(this);
    
    // Initial refresh
    refreshPortList();
    updateConnectionStatus();
    
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
    const int statusWidth = 120;
    
    // Port selection row
    auto portRow = bounds.removeFromTop(controlHeight);
    portLabel.setBounds(portRow.removeFromLeft(labelWidth));
    portRow.removeFromLeft(spacing);
    
    statusIndicator.setBounds(portRow.removeFromRight(statusWidth));
    portRow.removeFromRight(spacing);
    
    portComboBox.setBounds(portRow);
    
    bounds.removeFromTop(spacing);
    
    // Channel selection row
    auto channelRow = bounds.removeFromTop(controlHeight);
    channelLabel.setBounds(channelRow.removeFromLeft(labelWidth));
    channelRow.removeFromLeft(spacing);
    channelComboBox.setBounds(channelRow.removeFromLeft(80));
    
    bounds.removeFromTop(spacing);
    
    // Bank selection row
    auto bankRow = bounds.removeFromTop(controlHeight);
    bankLabel.setBounds(bankRow.removeFromLeft(labelWidth));
    bankRow.removeFromLeft(spacing);
    
    useMSBButton.setBounds(bankRow.removeFromRight(50));
    bankRow.removeFromRight(spacing);
    
    bankComboBox.setBounds(bankRow.removeFromLeft(80));
}

void DeviceSelectorPanel::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &portComboBox)
    {
        juce::String selectedPort = portComboBox.getText();
        patchManager.setMidiOutputPort(selectedPort);
        updateConnectionStatus();
    }
    else if (comboBoxThatHasChanged == &channelComboBox)
    {
        int selectedChannel = channelComboBox.getSelectedId();
        if (selectedChannel > 0)
        {
            patchManager.setMidiChannel(selectedChannel);
        }
    }
    else if (comboBoxThatHasChanged == &bankComboBox)
    {
        int selectedBank = bankComboBox.getSelectedId() - 1; // IDs are 1-based
        if (selectedBank >= 0 && selectedBank <= 127)
        {
            bool useMSB = useMSBButton.getToggleState();
            patchManager.getMidiManager().sendBankSelect(selectedBank, useMSB);
        }
    }
}

void DeviceSelectorPanel::buttonClicked(juce::Button* button)
{
    if (button == &useMSBButton)
    {
        // If bank is selected, resend bank select with new MSB/LSB setting
        int selectedBank = bankComboBox.getSelectedId() - 1;
        if (selectedBank >= 0 && selectedBank <= 127)
        {
            bool useMSB = useMSBButton.getToggleState();
            patchManager.getMidiManager().sendBankSelect(selectedBank, useMSB);
        }
    }
}

void DeviceSelectorPanel::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    refreshPortList();
    updateConnectionStatus();
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

void DeviceSelectorPanel::updateBankComboBox()
{
    bankComboBox.clear();
    bankComboBox.addItem("Bank 0", 1);
    for (int i = 1; i <= 127; ++i)
    {
        bankComboBox.addItem("Bank " + juce::String(i), i + 1);
    }
    bankComboBox.setSelectedId(1, juce::dontSendNotification); // Default to bank 0
}

void DeviceSelectorPanel::updateConnectionStatus()
{
    bool isConnected = patchManager.getMidiManager().isPortOpen();
    auto portName = patchManager.getMidiManager().getCurrentPortName();
    
    juce::String statusText;
    if (isConnected && portName.isNotEmpty())
    {
        statusText = "Connected: " + portName;
    }
    else if (!portName.isEmpty())
    {
        statusText = "Disconnected";
    }
    else
    {
        statusText = "No device selected";
    }
    
    statusIndicator.setConnected(isConnected, statusText);
}


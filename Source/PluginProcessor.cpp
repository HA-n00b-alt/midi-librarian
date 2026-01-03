#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiLibrarianAudioProcessor::MidiLibrarianAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MidiLibrarianAudioProcessor::~MidiLibrarianAudioProcessor()
{
}

const juce::String MidiLibrarianAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiLibrarianAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiLibrarianAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiLibrarianAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiLibrarianAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiLibrarianAudioProcessor::getNumPrograms()
{
    return 1;
}

int MidiLibrarianAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiLibrarianAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String MidiLibrarianAudioProcessor::getProgramName(int index)
{
    return {};
}

void MidiLibrarianAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

void MidiLibrarianAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // No audio processing needed
}

void MidiLibrarianAudioProcessor::releaseResources()
{
    // No resources to release
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiLibrarianAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}
#endif

void MidiLibrarianAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Clear audio buffer (MIDI-only plugin)
    buffer.clear();
    
    // Process queued MIDI messages from MidiManager (sample-accurate timing)
    patchManager.getMidiManager().processAudioThread(midiMessages);
}

void MidiLibrarianAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Serialize plugin state (patch bank and device config)
    // This is for DAW project save/load
    juce::MemoryOutputStream mos(destData, true);
    
    // Create state object (same pattern as DeviceModel::toVar and PatchData::toVar)
    juce::DynamicObject::Ptr stateObj = new juce::DynamicObject();
    stateObj->setProperty("patchBank", patchManager.getPatchBank().toVar());
    stateObj->setProperty("deviceConfig", patchManager.getDeviceModel().toVar());
    
    // Convert to var - var constructor accepts ReferenceCountedObject* (raw pointer)
    // Use .get() to get the raw pointer from the Ptr
    juce::var stateVar(stateObj.get());
    juce::JSON::writeToStream(mos, stateVar);
}

void MidiLibrarianAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // Deserialize plugin state
    auto jsonString = juce::String::fromUTF8(static_cast<const char*>(data), sizeInBytes);
    auto var = juce::JSON::parse(jsonString);
    
    if (auto* obj = var.getDynamicObject())
    {
        if (obj->hasProperty("patchBank"))
            patchManager.getPatchBank().fromVar(obj->getProperty("patchBank"));
        
        if (obj->hasProperty("deviceConfig"))
        {
            patchManager.getDeviceModel().fromVar(obj->getProperty("deviceConfig"));
            // Sync MIDI manager (will handle errors gracefully)
            auto portName = patchManager.getDeviceModel().getMidiOutputPortName();
            if (!portName.isEmpty())
            {
                patchManager.setMidiOutputPort(portName);
            }
            patchManager.setMidiChannel(patchManager.getDeviceModel().getMidiChannelDisplay());
        }
    }
}

juce::AudioProcessorEditor* MidiLibrarianAudioProcessor::createEditor()
{
    return new MidiLibrarianAudioProcessorEditor(*this);
}

bool MidiLibrarianAudioProcessor::hasEditor() const
{
    return true;
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiLibrarianAudioProcessor();
}


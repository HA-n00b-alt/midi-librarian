#pragma once

#include <JuceHeader.h>
#include "Controller/PatchManager.h"

/**
 * Main AUv3 plugin processor.
 * 
 * Since this is a MIDI-only plugin (no audio processing), the processor
 * is minimal. It mainly holds the PatchManager instance and handles
 * plugin state serialization.
 */
class MidiLibrarianAudioProcessor : public juce::AudioProcessor
{
public:
    MidiLibrarianAudioProcessor();
    ~MidiLibrarianAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    // Access to PatchManager (for editor)
    PatchManager& getPatchManager() noexcept { return patchManager; }
    const PatchManager& getPatchManager() const noexcept { return patchManager; }

private:
    PatchManager patchManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiLibrarianAudioProcessor)
};


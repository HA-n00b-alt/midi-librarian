#pragma once

#include <JuceHeader.h>

/**
 * Manages MIDI Learn functionality.
 * 
 * Allows mapping MIDI messages (PC, CC, Note) to patch recall operations.
 * Learned mappings are stored in config and can trigger patch selection.
 */
class MidiLearnManager : public juce::ChangeBroadcaster
{
public:
    enum MessageType
    {
        ProgramChange = 0,
        ControlChange = 1,
        NoteOn = 2
    };
    
    struct MidiMapping
    {
        int patchSlot = 0;
        MessageType messageType = ProgramChange;
        int channel = 1; // 1-16
        int data1 = 0;   // Program number, CC number, or Note number
        int data2 = 0;   // CC value or Note velocity (0 for PC)
        
        bool matches(const juce::MidiMessage& message) const;
        juce::var toVar() const;
        static MidiMapping fromVar(const juce::var& v);
    };
    
    MidiLearnManager();
    ~MidiLearnManager() override = default;
    
    // Learning mode
    void startLearning(int patchSlot);
    void stopLearning();
    bool isLearning() const noexcept { return learningSlot >= 0; }
    int getLearningSlot() const noexcept { return learningSlot; }
    
    // Mapping management
    void addMapping(const MidiMapping& mapping);
    void removeMapping(int patchSlot);
    MidiMapping* findMapping(const juce::MidiMessage& message);
    juce::Array<MidiMapping> getAllMappings() const;
    
    // Process incoming MIDI (called from MidiManager callback)
    void processMidiMessage(const juce::MidiMessage& message);
    
    // Callback when mapping triggers patch recall
    std::function<void(int patchSlot)> onPatchRecall;
    
    // Persistence
    juce::var toVar() const;
    void fromVar(const juce::var& v);
    
private:
    juce::Array<MidiMapping> mappings;
    int learningSlot = -1; // -1 = not learning, >= 0 = learning for this slot
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiLearnManager)
};


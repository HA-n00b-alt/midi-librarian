# Threading Model Explanation

## Overview

The MIDI Librarian plugin uses a **hybrid threading model** that ensures both user-friendly UI interactions and sample-accurate MIDI timing for DAW integration.

## Architecture

### Message Thread (UI Thread)
- **Purpose**: User interface, device management, file I/O
- **Operations**:
  - User clicks "Recall" button → queues MIDI message
  - User selects MIDI port → opens/closes device
  - User renames patch → updates model, saves to disk
  - All UI updates and component rendering

### Audio Thread (processBlock)
- **Purpose**: Sample-accurate MIDI output processing
- **Operations**:
  - Reads queued MIDI messages from FIFO
  - Adds messages to output `MidiBuffer` at correct sample positions
  - Ensures timing accuracy for DAW automation

## MIDI Message Flow

```
User clicks "Recall" (Message Thread)
    ↓
PatchManager::recallPatch()
    ↓
MidiManager::sendProgramChange() → Validates, queues to FIFO
    ↓
[FIFO Buffer - Lock-free, thread-safe]
    ↓
processBlock() called (Audio Thread)
    ↓
MidiManager::processAudioThread() → Reads FIFO, adds to MidiBuffer
    ↓
DAW receives MIDI messages (sample-accurate)
```

## Implementation Details

### AbstractFifo Usage

```cpp
// In MidiManager
juce::AbstractFifo midiFifo { 512 };  // Lock-free FIFO
juce::Array<juce::MidiMessage> midiMessageQueue;

// Message thread: Queue message
void sendProgramChange(int program) {
    int start1, size1, start2, size2;
    midiFifo.prepareToWrite(1, start1, size1, start2, size2);
    // Write message to queue[start1] or queue[start2]
    midiFifo.finishedWrite(size1 + size2);
}

// Audio thread: Process queue
void processAudioThread(MidiBuffer& buffer) {
    int start1, size1, start2, size2;
    midiFifo.prepareToRead(numReady, start1, size1, start2, size2);
    // Read messages and add to buffer
    midiFifo.finishedRead(size1 + size2);
}
```

### Why This Approach?

**Previous (Incorrect) Approach**:
```cpp
// ❌ BAD: Direct send from message thread
void sendProgramChange(int program) {
    midiOutput->sendMessageNow(message);  // Timing jitter!
}
```

**Problems**:
- Timing jitter in DAW context
- No sample-accurate positioning
- Breaks DAW automation timing
- Can cause missed beats

**Current (Correct) Approach**:
```cpp
// ✅ GOOD: Queue from message thread, process on audio thread
void sendProgramChange(int program) {
    // Queue to FIFO (fast, lock-free)
    queueMessage(message);
}

void processBlock(..., MidiBuffer& midi) {
    // Process queue on audio thread (sample-accurate)
    processAudioThread(midi);
}
```

**Benefits**:
- Sample-accurate MIDI timing
- No audio thread blocking
- Works with DAW automation
- Thread-safe communication

## Thread Safety

### Critical Sections

**Device Management** (port open/close):
- Protected by `CriticalSection deviceLock`
- Only accessed from message thread
- Safe because device operations are not time-critical

**MIDI Queue**:
- Protected by `CriticalSection midiQueueLock`
- `AbstractFifo` provides lock-free read/write
- Critical section only for array access

### Lock-Free Operations

`AbstractFifo` uses atomic operations internally, making it safe for:
- One writer (message thread)
- One reader (audio thread)
- No blocking or contention

## Error Handling

### Message Thread Errors
- Return `juce::Result` from operations
- Log errors for debugging
- Show user-friendly messages in UI (future)

### Audio Thread Errors
- Never throw exceptions
- Never block
- Log errors asynchronously (post to message thread)

## Performance Considerations

### FIFO Size
- Current: 512 messages
- Typical usage: 1-2 messages per user action
- Overflow: Returns error, user can retry

### Latency
- Queue time: < 1ms (negligible)
- Audio thread processing: < 0.1ms per block
- Total latency: < 1 audio buffer (typically 1-5ms)

## Testing

### Unit Tests (Future)
- Test FIFO overflow handling
- Test thread safety with concurrent access
- Test message ordering

### Integration Tests
- Verify sample-accurate timing in DAW
- Test with automation
- Test with high MIDI message rate

## Common Pitfalls to Avoid

### ❌ Don't Send MIDI Directly from Audio Thread
```cpp
// BAD: Device operations on audio thread
void processBlock(...) {
    midiOutput->openDevice(...);  // NEVER!
}
```

### ❌ Don't Access UI from Audio Thread
```cpp
// BAD: UI updates from audio thread
void processBlock(...) {
    label.setText("...");  // NEVER!
}
```

### ✅ Do Queue Messages from Message Thread
```cpp
// GOOD: Queue from UI
void onRecallButtonClicked() {
    midiManager.sendProgramChange(patchNumber);  // Queues to FIFO
}
```

### ✅ Do Process Queue on Audio Thread
```cpp
// GOOD: Process in processBlock
void processBlock(..., MidiBuffer& midi) {
    midiManager.processAudioThread(midi);  // Reads FIFO
}
```

## Future Enhancements

### High-Priority MIDI Messages
- Could add priority queue for urgent messages
- Currently all messages treated equally (acceptable for patch changes)

### MIDI Input Processing
- Would use `MidiInputCallback` on background thread
- Post messages to message thread for UI updates
- Never process on audio thread

### Multiple MIDI Outputs
- Extend FIFO to support multiple outputs
- Route messages based on device selection


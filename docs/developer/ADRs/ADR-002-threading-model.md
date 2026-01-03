# ADR-002: Threading Model for MIDI I/O

**Status**: Accepted  
**Date**: 2024  
**Deciders**: Development Team

## Context

MIDI messages need to be sent with sample-accurate timing for proper DAW integration. However, MIDI device management (opening/closing ports) should not block the audio thread. We needed a threading model that:
- Ensures sample-accurate MIDI timing
- Doesn't block the audio thread
- Provides simple API for UI code
- Is thread-safe

## Decision

We implemented a **hybrid threading model**:

1. **Device Management**: Message thread only (port open/close)
2. **MIDI Message Sending**: 
   - UI queues messages to `AbstractFifo` (message thread)
   - Audio thread processes queue in `processBlock()` (sample-accurate)
3. **MIDI Input**: Background thread callbacks forwarded to message thread

This uses JUCE's `AbstractFifo` for lock-free communication between threads.

## Consequences

### Positive
- Sample-accurate MIDI timing for DAW automation
- No audio thread blocking
- Simple API for UI code (just queue messages)
- Thread-safe by design
- Works with DAW automation

### Negative
- Slightly more complex than direct sending
- Requires understanding of threading model
- Small latency (one audio buffer, typically < 5ms)

### Neutral
- FIFO size limits (512 messages - more than enough)
- Queue can overflow (returns error, user can retry)

## Alternatives Considered

1. **Direct Send from Message Thread**: Rejected - causes timing jitter
2. **Direct Send from Audio Thread**: Rejected - device operations would block
3. **Separate MIDI Thread**: Considered but unnecessary complexity

## Notes

This approach follows JUCE best practices and ensures proper DAW integration. The small latency is acceptable for patch changes (not time-critical like audio).


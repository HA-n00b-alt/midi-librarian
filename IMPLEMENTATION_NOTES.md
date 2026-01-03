# Implementation Notes & Best Practices

## Why This Architecture?

### 1. MVC Separation
**Problem**: Mixing UI, business logic, and data makes code hard to test and maintain.

**Solution**: Clear separation:
- **Model**: Pure data structures, no UI dependencies
- **View**: Pure UI components, minimal logic
- **Controller**: Business logic, coordinates Model and View

**Benefit**: You can test `PatchBank` independently, swap UI components easily, and add features without touching unrelated code.

### 2. Custom LookAndFeel
**Problem**: Styling individual components leads to inconsistent appearance and duplicated code.

**Solution**: Override `LookAndFeel` drawing methods once, apply to all components.

**Benefit**: Change the entire UI theme by modifying one class. All buttons, combos, text editors automatically get the new style.

### 3. MIDI on Message Thread
**Problem**: MIDI I/O on audio thread can cause glitches and timing issues.

**Solution**: `MidiManager` sends MIDI messages from the message thread using `sendMessageNow()`.

**Why it's safe**: 
- MIDI messages are not time-critical (unlike audio samples)
- JUCE's `MidiOutput` is thread-safe for sending
- No audio processing in this plugin anyway

**Note**: If you later add MIDI input processing, use `MidiInputCallback` on a background thread, not the audio thread.

### 4. ChangeBroadcaster Pattern
**Problem**: Views need to update when Model changes, but Model shouldn't know about Views.

**Solution**: Model classes inherit `ChangeBroadcaster`, Views implement `ChangeListener`.

**Benefit**: Loose coupling. Model just broadcasts "I changed", Views decide how to respond.

### 5. JSON Persistence
**Problem**: Binary formats are hard to debug and not human-readable.

**Solution**: Use JUCE's built-in JSON support (`JSON::toString()`, `JSON::parse()`).

**Benefits**:
- Human-readable (easy debugging)
- Easy to version control
- Simple to extend (just add properties to `toVar()`/`fromVar()`)
- Can be edited manually if needed

**File Location**: User's Application Support directory (standard macOS location, survives app updates).

## UI Design Principles

### 1. Large Touch Targets
- Minimum 32px height for buttons/controls
- 48px for list items (comfortable for touch)
- Generous padding (8-12px)

### 2. Minimal Visual Clutter
- No gradients, shadows, or 3D effects
- Flat colors only
- Thin borders (1-2px)
- Subtle hover states (alpha transparency)

### 3. Clear Hierarchy
- Device selector at top (setup)
- Patch list below (main content)
- Consistent spacing (8px grid)

### 4. Resizable Window
- Set minimum size (400x300)
- Set maximum size (2000x1500) for very large screens
- Default size (600x800) comfortable for most users
- Components scale proportionally

## Common Pitfalls to Avoid

### 1. Don't Block the Audio Thread
❌ **Wrong**: Sending MIDI in `processBlock()`
```cpp
void processBlock(...) {
    midiOutput->sendMessageNow(message); // BAD!
}
```

✅ **Right**: Send MIDI from message thread
```cpp
void recallPatch(int slot) {
    midiManager.sendProgramChange(slot); // Called from UI
}
```

### 2. Don't Access JUCE Components from Background Threads
❌ **Wrong**: Updating UI from MIDI callback thread
```cpp
void handleIncomingMidiMessage(...) {
    label.setText("Received!"); // BAD! Not thread-safe
}
```

✅ **Right**: Post message to message thread
```cpp
void handleIncomingMidiMessage(...) {
    juce::MessageManager::callAsync([this] {
        label.setText("Received!"); // Safe
    });
}
```

### 3. Don't Store Raw Pointers to Components
❌ **Wrong**: 
```cpp
PatchListItem* selectedItem; // Can become dangling
```

✅ **Right**: Use `OwnedArray` or `std::unique_ptr`
```cpp
juce::OwnedArray<PatchListItem> items; // Automatically managed
```

### 4. Don't Forget to Remove ChangeListeners
❌ **Wrong**: 
```cpp
~MyComponent() {
    // Forgot to remove listener - memory leak!
}
```

✅ **Right**: 
```cpp
~MyComponent() {
    patchManager.removeChangeListener(this);
}
```

## Testing Strategy

### Unit Tests (Future)
- Test `PatchBank` operations independently
- Test `PersistenceManager` with mock files
- Test `MidiManager` with mock MIDI devices

### Integration Tests
- Test full workflow: rename patch → save → reload → verify
- Test MIDI output with virtual MIDI port

### Manual Testing Checklist
- [ ] Select MIDI port → verify connection
- [ ] Change channel → verify MIDI messages use correct channel
- [ ] Rename patch → verify save/load
- [ ] Recall patch → verify MIDI PC sent
- [ ] Resize window → verify UI scales correctly
- [ ] Export/import → verify data integrity

## Performance Considerations

### Current Implementation
- **Startup**: Loads JSON synchronously (fast, < 1ms for 128 patches)
- **Save**: Writes to temp file then atomic rename (safe, fast)
- **UI Updates**: Rebuilds entire list on change (acceptable for 128 items)

### Future Optimizations
- **Large Banks**: If supporting > 128 patches, use virtualized list (only render visible items)
- **Background Save**: Move file I/O to background thread for very large exports
- **Incremental Updates**: Only update changed list items instead of full rebuild

## Extension Examples

### Adding a Patch Editor
1. Create `PatchEditorPanel.h/cpp` in `View/`
2. Extend `PatchData` with parameter map:
   ```cpp
   juce::HashMap<juce::Identifier, float> parameters;
   ```
3. Add editor UI (sliders, knobs) for parameters
4. Update `PatchManager` to save parameter data

### Adding Device Templates
1. Create `DeviceTemplate.h/cpp` in `Model/`
2. Store templates in `templates/` subdirectory
3. Add template selection to `DeviceSelectorPanel`
4. Validate patch names/parameters against template

### Adding SysEx Backup
1. Add `sendSysExRequest()` to `MidiManager`
2. Create `SysExBackupPanel` in `View/`
3. Use background thread for large transfers
4. Show progress bar during backup

## Code Organization Tips

### File Naming
- One class per file pair (.h/.cpp)
- Match class name to filename
- Group related classes in subdirectories

### Include Order
1. Corresponding header
2. JUCE headers
3. Project headers (Model → View → Controller)
4. Standard library

### Forward Declarations
Use forward declarations in headers when possible:
```cpp
class PatchManager; // Forward declare
// Instead of: #include "PatchManager.h"
```

This reduces compile times and avoids circular dependencies.

## Debugging Tips

### JSON Parsing Errors
- Use `JSON::parse()` which returns `var()` on error
- Check `var.isUndefined()` before accessing
- Log JSON string before parsing to see what went wrong

### MIDI Not Working
- Verify port is open: `midiManager.isPortOpen()`
- Check channel: MIDI channels are 1-16 in UI, 0-15 internally
- Use MIDI monitor app to verify messages are sent

### UI Not Updating
- Verify `ChangeListener` is registered
- Check `sendChangeMessage()` is called after model changes
- Ensure UI updates happen on message thread


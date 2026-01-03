# Improvement Roadmap

This document prioritizes and tracks implementation of suggested improvements to the MIDI Librarian plugin.

## ✅ Completed (Critical Fixes)

### 1. Threading Model Fix ⚠️ **CRITICAL - FIXED**
**Status**: ✅ Implemented

**What Changed**:
- Added `AbstractFifo`-based MIDI message queue for audio thread processing
- `sendProgramChange()` now queues messages instead of sending directly
- `processAudioThread()` called from `processBlock()` for sample-accurate timing
- Maintains thread-safe interface for UI while ensuring proper DAW integration

**Why Critical**: 
- Previous implementation would cause timing jitter in DAW context
- Sample-accurate MIDI timing is essential for automation and synchronization
- Now supports both user-initiated (UI) and DAW-automated patch changes

**Files Modified**:
- `MidiManager.h/cpp` - Added FIFO queue and audio thread processing
- `PluginProcessor.cpp` - Calls `processAudioThread()` in `processBlock()`

### 2. Error Handling with Result-Based API
**Status**: ✅ Implemented

**What Changed**:
- All MIDI operations now return `juce::Result` instead of void
- Validation for program numbers, controller values, port availability
- Graceful error handling with logging

**Files Modified**:
- `MidiManager.h/cpp` - Result-based API
- `PatchManager.cpp` - Error handling for MIDI operations

### 3. Device Hotplug Handling
**Status**: ✅ Basic implementation

**What Changed**:
- Detects MIDI device disconnection
- Logs device state changes
- UI can handle reconnection (via `setOutputPort()`)

**Future Enhancement**: Add automatic reconnection with user notification

---

## 🔴 High Priority (Must-Have for MVP+)

### 4. MIDI Program Change Integration
**Status**: ✅ Core implemented, enhancements pending

**Completed**:
- ✅ Basic Program Change sending
- ✅ Bank Select (CC#0/32) support for multi-bank synths

**Remaining Work**:
- [ ] Optional PC sending toggle (some users prefer manual control)
- [ ] PC message preview/debug mode
- [ ] Bank Select UI (dropdown/selector in DeviceSelectorPanel)

**Files Modified**:
- `MidiManager.h/cpp` - Added `sendBankSelect()` method

**Estimated Effort**: 1-2 hours (for remaining features)

### 5. Search & Filtering
**Status**: ✅ Implemented

**Features**:
- ✅ Search patches by name (real-time filtering)
- ✅ Tag/category system (bass, lead, pad, etc.) - data model ready
- ✅ Favorites/starred patches
- ⏳ Recently used patches list (future)

**Implementation Notes**:
- Extended `PatchData` with tags/favorites
- Added `SearchBar` component with real-time filtering
- `PatchListPanel` filters patches based on search query and favorites
- Favorites button in each patch row

**Files Added/Modified**:
- `SearchBar.h/cpp` - New search component
- `PatchData.h/cpp` - Added favorites and tags
- `PatchListPanel.h/cpp` - Added filtering logic
- `PatchListItem.h/cpp` - Added favorites button

### 6. Undo/Redo System
**Status**: ✅ Implemented

**Features**:
- ✅ Full undo/redo stack for all operations
- ✅ Undo/redo for rename, favorites, copy, batch operations
- ✅ Uses JUCE's `UndoManager`

**Implementation Notes**:
- Created `UndoableActions.h` with action classes:
  - `RenamePatchAction`
  - `SetFavoriteAction`
  - `CopyPatchAction`
  - `BatchRenameAction`
- Integrated with `PatchManager`
- `ToolbarPanel` provides undo/redo UI buttons
- Buttons show action descriptions and enable/disable appropriately

**Files Added/Modified**:
- `UndoableActions.h` - All undoable action classes
- `PatchManager.h/cpp` - Integrated UndoManager
- `ToolbarPanel.h/cpp` - Undo/redo UI
- `PluginEditor.h/cpp` - Added toolbar to main window

**Estimated Effort**: ✅ Completed

### 7. Enhanced Device Hotplug
**Status**: ✅ Implemented

**Features**:
- ✅ Visual indicator of device connection state in UI
- ✅ Status text showing connection state
- ⏳ Automatic reconnection when device returns (detection ready, auto-reconnect pending)
- ⏳ User notification (toast/alert) on disconnect/reconnect (future enhancement)

**Implementation Notes**:
- `DeviceStatusIndicator` component shows green/red status
- Updates automatically on device list changes
- Status text shows current port name or "Disconnected"

**Files Added/Modified**:
- `DeviceStatusIndicator.h/cpp` - New status indicator component
- `DeviceSelectorPanel.h/cpp` - Integrated status indicator
- `MidiManager.cpp` - Enhanced hotplug detection

**Estimated Effort**: 1-2 hours (for auto-reconnect and notifications)

---

## 🟡 Medium Priority (Should-Have Features)

### 8. Multi-Bank Support
**Status**: ⏳ Partially implemented (UI ready, data model pending)

**Completed**:
- ✅ Bank Select UI (dropdown + MSB/LSB toggle)
- ✅ Bank Select MIDI support (CC#0/CC#32)
- ✅ Integration with device selector panel

**Remaining**:
- [ ] Extend `PatchBank` to support multiple banks in memory
- [ ] Bank navigation (switch between banks in UI)
- [ ] Import/export individual banks
- [ ] Persist bank selection

**Implementation Notes**:
- Bank selector added to `DeviceSelectorPanel`
- MSB/LSB toggle for devices with >128 banks
- Sends bank select before program change (when implemented)

**Files Modified**:
- `DeviceSelectorPanel.h/cpp` - Added bank selector UI
- `MidiManager.h/cpp` - Already had `sendBankSelect()` method

**Estimated Effort**: 4-6 hours (for data model extension)

### 9. Device Profiles/Templates
**Status**: 📋 Planned

**Features**:
- Pre-built profiles for popular synths
- Device-specific features: SysEx commands, parameter maps
- Community-shareable device profile format (JSON)

**Implementation Notes**:
- Create `DeviceTemplate` class
- Store templates in `templates/` directory
- Device selector shows available templates
- Extend `DeviceModel` with template-specific properties

**Estimated Effort**: 12-16 hours

### 10. Patch Organization Features
**Status**: 📋 Planned

**Features**:
- Drag-and-drop reordering
- Copy/paste patches between slots
- Batch operations (rename multiple, clear range)
- Import patches from other MIDI file formats

**Estimated Effort**: 10-14 hours

### 11. Real-time MIDI Monitoring
**Status**: 📋 Planned

**Features**:
- Display incoming MIDI messages (debugging)
- Show current patch on external device (SysEx query)
- MIDI activity indicators in UI

**Estimated Effort**: 6-8 hours

---

## 🟢 Low Priority (Nice-to-Have)

### 12. SysEx Backup/Restore
**Status**: 📋 Future

**Features**:
- Bidirectional SysEx communication
- Bulk dump and single patch dump
- Progress UI with cancel option
- Checksum validation

**Estimated Effort**: 16-20 hours

### 13. MIDI Learn & Mapping
**Status**: 📋 Future

**Features**:
- MIDI learn for patch selection
- Store learned mappings in config
- Support PC messages triggering patch recall

**Estimated Effort**: 8-10 hours

### 14. Preset Management
**Status**: 📋 Future

**Features**:
- Factory preset banks
- User-created setlist mode
- Quick-save snapshots

**Estimated Effort**: 10-12 hours

### 15. Host Integration Enhancements
**Status**: 📋 Future

**Features**:
- DAW automation for patch selection
- Session recall improvements
- MIDI CC mapping for DAW controllers

**Estimated Effort**: 8-12 hours

---

## 🔧 Technical Improvements

### 16. State Management with AudioProcessorValueTreeState
**Status**: 📋 Consider for v2.0

**Notes**: 
- Current JSON approach works well for patch bank data
- Consider ValueTree for currently selected patch (small state)
- Keep JSON for large patch bank data

**Estimated Effort**: 6-8 hours

### 17. Memory Management Audit
**Status**: ✅ Mostly good

**Current State**:
- Using `std::unique_ptr` for MIDI output
- `OwnedArray` for UI components
- RAII for resources

**Remaining**: Audit all raw pointers, ensure no leaks

**Estimated Effort**: 2-3 hours

### 18. Lazy Loading for Large Banks
**Status**: 📋 Future optimization

**When Needed**: Only if supporting > 128 patches or very large patch data

**Estimated Effort**: 8-10 hours

### 19. UI Optimization
**Status**: 📋 Future optimization

**Features**:
- Virtualized list (only render visible items)
- Reduce paint() calls
- Cache rendered components

**Estimated Effort**: 6-8 hours

### 20. Unit Tests
**Status**: 📋 Planned

**Priority Tests**:
- Patch bank operations
- MIDI message generation
- JSON serialization
- Thread-safe operations

**Estimated Effort**: 12-16 hours

### 21. Logging & Diagnostics
**Status**: ⏳ Partially implemented

**Current**: Basic logging in error cases

**Remaining**:
- Debug mode with verbose MIDI logging
- Performance profiling hooks
- User-facing error messages

**Estimated Effort**: 4-6 hours

### 22. Configuration Validation
**Status**: 📋 Planned

**Features**:
- JSON schema validation on load
- Migrate old config formats
- Sensible defaults for corrupt config

**Estimated Effort**: 4-6 hours

### 23. Const Correctness Audit
**Status**: 📋 Planned

**Action**: Review all methods, mark read-only as `const`

**Estimated Effort**: 2-3 hours

---

## 📚 Documentation Improvements

### 24. API Documentation
**Status**: ⏳ Partially done (inline comments)

**Remaining**: Add Doxygen-style comments for public API

**Estimated Effort**: 4-6 hours

### 25. User Manual
**Status**: 📋 Planned

**Estimated Effort**: 8-12 hours

### 26. Developer Guide
**Status**: ⏳ Started (ARCHITECTURE.md, IMPLEMENTATION_NOTES.md)

**Remaining**: Contributing guidelines, ADRs

**Estimated Effort**: 4-6 hours

---

## 🌍 Cross-Platform Considerations

### 27. Windows/Linux Support
**Status**: 📋 Future

**Notes**: Current code should work, but needs testing and validation

**Estimated Effort**: 8-12 hours (testing)

### 28. Plugin Format Support
**Status**: 📋 Future

**Current**: AUv3 only (as requested)

**Future**: VST3, standalone app

**Estimated Effort**: 4-6 hours per format

### 29. Accessibility
**Status**: 📋 Planned

**Features**:
- Keyboard navigation
- Screen reader support
- High contrast mode

**Estimated Effort**: 6-8 hours

---

## Implementation Priority Summary

### Phase 1: Critical Fixes (✅ Done)
- [x] Threading model fix
- [x] Error handling
- [x] Basic hotplug handling

### Phase 2: MVP+ Features (Next 2-3 weeks)
1. Enhanced device hotplug with notifications
2. Search & filtering
3. Undo/redo system
4. Bank Select support

### Phase 3: Core Features (Next 1-2 months)
1. Multi-bank support
2. Device profiles/templates
3. Patch organization (drag-drop, copy/paste)
4. MIDI monitoring

### Phase 4: Advanced Features (Future)
1. SysEx backup/restore
2. MIDI learn
3. Preset management
4. Host integration enhancements

### Phase 5: Polish & Optimization
1. Unit tests
2. UI optimization (virtualization)
3. Documentation
4. Cross-platform testing

---

## Notes

- **Threading**: The critical threading fix ensures proper DAW integration. All MIDI messages now go through the audio thread for sample-accurate timing.

- **Error Handling**: Result-based API provides better error reporting and user feedback.

- **Extensibility**: Architecture supports all planned features without major refactoring.

- **Performance**: Current implementation is efficient for 128 patches. Optimizations only needed for larger banks.


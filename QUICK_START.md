# Quick Start Guide

## Answers to Your Questions

### 1. Recommended Folder/Class Structure

```
Source/
├── Model/              # Data structures
│   ├── PatchData.h/cpp      # Individual patch (slot, name, deviceID)
│   ├── PatchBank.h/cpp      # 128-slot collection
│   └── DeviceModel.h/cpp    # MIDI device config
│
├── View/               # UI Components
│   ├── ValhallaLookAndFeel.h/cpp    # Custom styling
│   ├── DeviceSelectorPanel.h/cpp    # Port/channel selection
│   ├── PatchListPanel.h/cpp         # Main patch list
│   └── PatchListItem.h/cpp          # Individual patch row
│
├── Controller/         # Business Logic
│   ├── PatchManager.h/cpp           # Main coordinator
│   ├── MidiManager.h/cpp             # MIDI I/O (message thread)
│   └── PersistenceManager.h/cpp      # JSON file I/O
│
├── PluginProcessor.h/cpp    # AUv3 processor
└── PluginEditor.h/cpp       # Main window
```

**Responsibilities**:
- **Model**: Data only, no UI, broadcasts changes via `ChangeBroadcaster`
- **View**: UI rendering only, listens to Model changes, delegates actions to Controller
- **Controller**: Business logic, coordinates Model/View, handles I/O

### 2. Main Plugin Window Structure

**PluginEditor** (top level):
```cpp
class MidiLibrarianAudioProcessorEditor {
    ValhallaLookAndFeel lookAndFeel;        // Applied globally
    DeviceSelectorPanel devicePanel;         // Top section
    PatchListPanel patchListPanel;          // Main area (scrollable)
};
```

**PatchListPanel** (scrollable list):
```cpp
class PatchListPanel {
    juce::Viewport viewport;                // Handles scrolling
    juce::Component listContainer;        // Container for items
    juce::OwnedArray<PatchListItem> items; // 128 patch rows
};
```

**PatchListItem** (individual row):
```cpp
class PatchListItem {
    juce::Label slotLabel;        // "001"
    juce::Label nameLabel;        // "Patch Name" (click to edit)
    juce::TextEditor nameEditor;  // Inline editing
    juce::TextButton recallButton; // "Recall"
};
```

### 3. JSON Persistence Structure

**File Location**: `~/Library/Application Support/MidiLibrarian/`

**patches.json** (array of patch objects):
```json
[
  {
    "slotIndex": 0,
    "patchName": "Init",
    "deviceID": "generic"
  },
  {
    "slotIndex": 1,
    "patchName": "Bass Pad",
    "deviceID": "generic"
  },
  ...
]
```

**config.json** (device configuration):
```json
{
  "midiOutputPortName": "My Synth",
  "midiChannel": 1,
  "deviceID": "generic"
}
```

**Implementation**: 
- `PersistenceManager` handles all file I/O
- Uses JUCE's `JSON::toString()` and `JSON::parse()`
- Atomic writes (temp file → rename) for safety
- Auto-saves on patch rename, manual save for export

### 4. UI Tips for Crisp, Minimal, Resizable Design

**Custom LookAndFeel**:
- Override all drawing methods in `ValhallaLookAndFeel`
- Single source of truth for colors, fonts, borders
- Apply once: `setLookAndFeel(&valhallaLookAndFeel)`

**Key Overrides**:
- `drawButtonBackground()`: Flat colors, subtle hover
- `drawComboBox()`: Minimal border, clean arrow
- `drawTextEditorOutline()`: Thin border, accent on focus
- `drawScrollbar()`: Thin, modern scrollbar

**Resizable Window**:
```cpp
setResizable(true, true);
setResizeLimits(400, 300, 2000, 1500);  // Min/max sizes
setSize(600, 800);  // Default size
```

**Layout Strategy**:
- Use `getLocalBounds().reduced(padding)` for spacing
- Remove sections with `removeFromTop()` / `removeFromLeft()`
- Let `Viewport` handle scrolling automatically
- Fixed heights for headers, flexible for content

**Touch-Friendly Sizing**:
- Minimum 32px for buttons
- 48px for list items
- 8-12px padding between elements
- Large, readable fonts (14pt minimum)

## Next Steps

1. **Create JUCE Project**:
   - Open Projucer
   - Create new AUv3 plugin project
   - Add all files from `Source/` directory
   - Configure as MIDI Effect plugin

2. **Build & Test**:
   - Generate Xcode project
   - Build and install in Logic Pro
   - Test MIDI output with a hardware synth

3. **Customize**:
   - Adjust accent color in `ValhallaLookAndFeel.h`
   - Modify default patch names in `PatchBank::initializeDefaults()`
   - Add export/import UI buttons (use `PersistenceManager`)

4. **Extend** (Future):
   - Device templates (extend `DeviceModel`)
   - SysEx backup (add to `MidiManager`)
   - Patch editor (new View component)

## Key Design Decisions Explained

### Why MVC?
- **Testability**: Model can be tested without UI
- **Maintainability**: Clear responsibilities, easy to find bugs
- **Extensibility**: Add features without touching unrelated code

### Why Custom LookAndFeel?
- **Consistency**: One place to change all styling
- **JUCE Standard**: Recommended way to customize appearance
- **Performance**: Drawing code runs once per component, not per frame

### Why MIDI on Message Thread?
- **Safety**: Audio thread must never block
- **Simplicity**: No complex thread synchronization needed
- **JUCE Design**: `MidiOutput::sendMessageNow()` is thread-safe

### Why JSON?
- **Human-readable**: Easy to debug and edit manually
- **Extensible**: Just add properties to `toVar()` methods
- **Standard**: JUCE has built-in JSON support

## Common Issues & Solutions

**Problem**: UI not updating after patch rename
**Solution**: Ensure `PatchBank::renamePatch()` calls `sendChangeMessage()`

**Problem**: MIDI not sending
**Solution**: Check `MidiManager::isPortOpen()` and verify port name matches

**Problem**: Window not resizable
**Solution**: Call `setResizable(true, true)` in editor constructor

**Problem**: JSON save fails
**Solution**: Check `PersistenceManager::getDataDirectory()` exists and is writable


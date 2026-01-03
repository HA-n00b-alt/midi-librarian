# MIDI Librarian - AUv3 Plugin

A minimalist MIDI librarian plugin for Logic Pro (macOS) built with JUCE and C++.

## Features

- **MIDI Device Selection**: Choose MIDI output port and channel (1-16)
- **Patch Management**: 128-slot patch bank with rename and recall
- **Local Persistence**: Automatic save/load of patch data as JSON
- **Clean UI**: Valhalla DSP-inspired minimalist design
- **Resizable Interface**: Touch-friendly, modern UI

## Architecture

This plugin follows a **Model-View-Controller (MVC)** pattern:

### Model Layer (`Source/Model/`)
- `PatchData`: Individual patch structure (slot, name, device ID)
- `PatchBank`: Collection of 128 patches with change broadcasting
- `DeviceModel`: MIDI device configuration

### View Layer (`Source/View/`)
- `ValhallaLookAndFeel`: Custom styling for all components
- `DeviceSelectorPanel`: MIDI port/channel selection
- `PatchListPanel`: Scrollable list of patches
- `PatchListItem`: Individual patch row component

### Controller Layer (`Source/Controller/`)
- `PatchManager`: Main coordinator (ties Model, View, I/O together)
- `MidiManager`: MIDI I/O handling (runs on message thread)
- `PersistenceManager`: JSON file I/O

## Threading Model

**Critical**: All MIDI operations run on the **message thread**, NOT the audio thread.

- **Audio Thread**: Not used (MIDI-only plugin, `processBlock` just clears buffer)
- **Message Thread**: UI updates, MIDI I/O, file I/O
- **Background Thread**: Optional for future large file operations

## Data Persistence

### Local Storage
- **Location**: `~/Library/Application Support/MidiLibrarian/`
- **Files**:
  - `patches.json`: Patch bank data
  - `config.json`: Device configuration

### JSON Structure

**patches.json**:
```json
[
  {
    "slotIndex": 0,
    "patchName": "Init",
    "deviceID": "generic"
  },
  ...
]
```

**config.json**:
```json
{
  "midiOutputPortName": "My Synth",
  "midiChannel": 1,
  "deviceID": "generic"
}
```

### Export/Import
Use `PersistenceManager::exportToFile()` and `importFromFile()` for backup/restore.

## Building

1. Open the `.jucer` file in Projucer (or create one)
2. Add all source files from `Source/` directory
3. Configure as AUv3 plugin
4. Generate Xcode project
5. Build in Xcode

## Extension Points

### Device Templates
- Extend `DeviceModel` with device-specific properties
- Add validation to `PatchBank` for device-specific constraints
- Store templates in separate JSON files

### SysEx Backup
- Add methods to `MidiManager` for bulk SysEx operations
- Create background thread for large transfers
- Add progress UI component

### Patch Editor
- Create new View component for parameter editing
- Extend `PatchData` with parameter maps
- Add device-specific parameter definitions

## UI Styling

The `ValhallaLookAndFeel` class provides:
- Light background (98% white)
- Single accent color (configurable hue)
- Large, touch-friendly controls
- Minimal borders and shadows
- Crisp typography

To customize colors, modify constants in `ValhallaLookAndFeel.h`:
```cpp
static constexpr float ACCENT_HUE = 0.6f; // Blue-green
static constexpr float ACCENT_SATURATION = 0.7f;
static constexpr float ACCENT_BRIGHTNESS = 0.5f;
```

## Code Style

- Modern C++17 features where helpful
- Clear separation of concerns (MVC)
- Inline comments for non-trivial logic
- JUCE coding conventions
- No single-file mega-blobs

## License

[Your License Here]


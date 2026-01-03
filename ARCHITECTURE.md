# MIDI Librarian Plugin Architecture

## Overview
This plugin follows a **Model-View-Controller (MVC)** pattern with clear separation of concerns:

- **Model**: Data structures and state (patches, devices, configuration)
- **View**: JUCE Components and custom LookAndFeel for UI rendering
- **Controller**: Business logic, MIDI I/O, persistence, and coordination

## Folder Structure

```
midi-librarian/
├── Source/
│   ├── PluginProcessor.h/cpp          # Main AUv3 processor
│   ├── PluginEditor.h/cpp              # Main editor window
│   │
│   ├── Model/                          # Data models
│   │   ├── PatchData.h/cpp            # Individual patch structure
│   │   ├── PatchBank.h/cpp            # Collection of patches (128 slots)
│   │   └── DeviceModel.h/cpp          # Device configuration (future: templates)
│   │
│   ├── View/                           # UI Components
│   │   ├── ValhallaLookAndFeel.h/cpp  # Custom styling
│   │   ├── DeviceSelectorPanel.h/cpp  # MIDI port/channel selection
│   │   ├── PatchListPanel.h/cpp       # Main patch list view
│   │   └── PatchListItem.h/cpp        # Individual patch row component
│   │
│   ├── Controller/                     # Business logic
│   │   ├── MidiManager.h/cpp          # MIDI I/O handling (message thread)
│   │   ├── PatchManager.h/cpp         # Patch CRUD operations
│   │   └── PersistenceManager.h/cpp   # JSON save/load
│   │
│   └── Utils/                          # Utilities
│       └── JsonHelpers.h/cpp          # JSON serialization helpers
│
└── Resources/                           # Assets (if needed)
```

## Key Design Decisions

### 1. MVC Separation
**Why**: Testability, maintainability, and clear responsibilities. The Model can be tested independently, Views can be swapped, and Controllers handle all side effects (MIDI, file I/O).

### 2. Custom LookAndFeel
**Why**: JUCE's LookAndFeel is the standard way to customize appearance across all components. By overriding drawing methods in one place, we ensure consistent styling and easy theme changes.

### 3. MIDI Threading Model
**Why**: MIDI messages are queued from the message thread (UI) but processed on the audio thread via `AbstractFifo` for sample-accurate timing. This ensures proper DAW integration while maintaining a simple UI API. Device management (port open/close) remains on the message thread as it's not time-critical.

### 4. PatchBank as Model
**Why**: Encapsulates the 128-slot structure, provides validation, and makes it easy to extend (e.g., different bank sizes per device template).

### 5. PersistenceManager
**Why**: Separates file I/O from business logic. Makes it easy to switch storage formats or add cloud sync later.

## Data Flow

1. **User Action** → View Component
2. **View** → Controller (e.g., `PatchManager::renamePatch()`)
3. **Controller** → Updates Model (`PatchBank`)
4. **Controller** → Triggers persistence (`PersistenceManager::save()`)
5. **Controller** → Sends MIDI if needed (`MidiManager::sendProgramChange()`)
6. **Model** → Notifies View (via `ChangeBroadcaster` or `ValueTree`)
7. **View** → Updates UI

## Threading Model

- **Audio Thread**: Processes queued MIDI messages from FIFO for sample-accurate timing
- **Message Thread**: UI updates, MIDI message queuing, file I/O, device management
- **Background Thread**: Optional for large file operations (future)

**Critical**: MIDI messages are queued from the message thread (UI) and processed on the audio thread via `AbstractFifo`. This ensures:
- Sample-accurate timing for DAW automation
- No blocking of audio thread
- Thread-safe communication between UI and audio processing

## Extension Points

- **Device Templates**: Add to `DeviceModel`, extend `PatchBank` with device-specific validation
- **SysEx Backup**: Add methods to `MidiManager` for bulk operations
- **Patch Editor**: Create new View component, extend `PatchData` with parameter maps
- **Cloud Sync**: Replace `PersistenceManager` implementation, keep interface


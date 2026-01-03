# MIDI Librarian

A minimalist MIDI librarian plugin for Logic Pro (macOS) built with JUCE and C++.

## Overview

MIDI Librarian is an AUv3 plugin designed for managing patches on hardware synthesizers and digital FX units. It provides a clean, modern interface for organizing, renaming, and recalling patches via MIDI Program Change messages.

## Features

### Core Features
- **MIDI Device Selection** - Choose MIDI output port and channel (1-16)
- **Patch Management** - 128-slot patch bank with rename and recall
- **Local Persistence** - Automatic save/load of patch data as JSON
- **Clean UI** - Valhalla DSP-inspired minimalist design
- **Resizable Interface** - Touch-friendly, modern UI

### Advanced Features
- **Search & Filtering** - Real-time search and favorites filter
- **Undo/Redo** - Full undo/redo system for all operations
- **Device Templates** - Pre-built profiles for popular synths
- **MIDI Learn** - Map hardware controllers to patch recall
- **Batch Operations** - Copy, clear range, batch rename
- **MIDI Monitoring** - Real-time MIDI input/output logging
- **Bank Select** - Support for multi-bank synths (MSB/LSB)

## Quick Start

1. **Build the Plugin**
   ```bash
   # Open in Projucer, configure as AUv3, generate Xcode project
   # Build and install in Logic Pro
   ```

2. **First Use**
   - Select your MIDI output device
   - Choose MIDI channel (1-16)
   - Select device template (optional)
   - Start organizing your patches!

3. **Basic Operations**
   - **Rename**: Click patch name, type new name, press Enter
   - **Recall**: Click "Recall" button to send Program Change
   - **Search**: Type in search bar to filter patches
   - **Favorite**: Click ★ to mark as favorite

See [User Guide](docs/user/USER_GUIDE.md) for detailed instructions.

## Documentation

- **[User Guide](docs/user/USER_GUIDE.md)** - Complete user documentation
- **[Quick Start](docs/user/QUICK_START.md)** - Getting started guide
- **[Architecture](docs/developer/ARCHITECTURE.md)** - Technical architecture
- **[Developer Guide](docs/developer/DEVELOPER_GUIDE.md)** - For contributors

## Requirements

- macOS 10.13+ (for AUv3 support)
- JUCE 7.0+ (latest recommended)
- Xcode 12+ (for building)
- Logic Pro (for testing/use)

## Building

1. Open Projucer
2. Create new AUv3 plugin project (or open existing `.jucer` file)
3. Add all source files from `Source/` directory
4. Configure as MIDI Effect plugin
5. Generate Xcode project
6. Build and install

See [Developer Guide](docs/developer/DEVELOPER_GUIDE.md) for detailed build instructions.

## Project Structure

```
midi-librarian/
├── Source/              # Source code
│   ├── Model/          # Data models
│   ├── View/           # UI components
│   ├── Controller/     # Business logic
│   ├── PluginProcessor.h/cpp
│   └── PluginEditor.h/cpp
│
├── docs/               # Documentation
│   ├── user/          # User documentation
│   ├── developer/     # Developer documentation
│   └── development/   # Development notes
│
└── README.md          # This file
```

## License

[Your License Here]

## Support

For issues, questions, or contributions, please see the [Developer Guide](docs/developer/DEVELOPER_GUIDE.md).

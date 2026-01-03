# Developer Guide

## Table of Contents

1. [Getting Started](#getting-started)
2. [Project Structure](#project-structure)
3. [Building the Plugin](#building-the-plugin)
4. [Architecture Overview](#architecture-overview)
5. [Contributing](#contributing)
6. [Code Style](#code-style)
7. [Testing](#testing)
8. [Debugging](#debugging)

## Getting Started

### Prerequisites

- **macOS 10.13+** (for AUv3 support)
- **JUCE 7.0+** (latest recommended)
- **Xcode 12+** (for building)
- **Projucer** (JUCE's project generator)
- **C++17** compatible compiler

### Initial Setup

1. **Clone the Repository**
   ```bash
   git clone [repository-url]
   cd midi-librarian
   ```

2. **Open in Projucer**
   - Launch Projucer
   - Open or create `.jucer` project file
   - Add all source files from `Source/` directory

3. **Configure Project**
   - Set plugin format to AUv3
   - Configure as MIDI Effect (not audio effect)
   - Set C++ standard to C++17
   - Add JUCE modules: Core, Audio, GUI Basics, Data Structures

4. **Generate Xcode Project**
   - Click "Save and Open in IDE"
   - Or generate project manually

5. **Build**
   - Select scheme: "MIDI Librarian - AU"
   - Build (Cmd+B)
   - Install to Logic Pro for testing

## Project Structure

```
midi-librarian/
├── Source/
│   ├── Model/              # Data models (no UI dependencies)
│   │   ├── PatchData.h/cpp
│   │   ├── PatchBank.h/cpp
│   │   ├── DeviceModel.h/cpp
│   │   └── DeviceTemplate.h/cpp
│   │
│   ├── View/               # UI components
│   │   ├── ValhallaLookAndFeel.h/cpp
│   │   ├── DeviceSelectorPanel.h/cpp
│   │   ├── PatchListPanel.h/cpp
│   │   ├── PatchListItem.h/cpp
│   │   ├── SearchBar.h/cpp
│   │   ├── ToolbarPanel.h/cpp
│   │   ├── MidiMonitorPanel.h/cpp
│   │   └── PatchOperationDialogs.h/cpp
│   │
│   ├── Controller/         # Business logic
│   │   ├── PatchManager.h/cpp
│   │   ├── MidiManager.h/cpp
│   │   ├── PersistenceManager.h/cpp
│   │   ├── DeviceTemplateManager.h/cpp
│   │   ├── MidiLearnManager.h/cpp
│   │   └── UndoableActions.h
│   │
│   ├── PluginProcessor.h/cpp
│   └── PluginEditor.h/cpp
│
├── docs/
│   ├── user/              # User documentation
│   ├── developer/         # Developer documentation
│   └── development/       # Development notes
│
└── README.md
```

## Building the Plugin

### Debug Build

1. Open Xcode project
2. Select "Debug" configuration
3. Build (Cmd+B)
4. Plugin installs to: `~/Library/Audio/Plug-Ins/Components/`

### Release Build

1. Select "Release" configuration
2. Build (Cmd+B)
3. Code signing required for distribution

### Testing in Logic Pro

1. Build plugin
2. Launch Logic Pro
3. Create new project
4. Add MIDI track
5. Insert plugin: "MIDI Librarian"
6. Test MIDI output with hardware synth

## Architecture Overview

### MVC Pattern

The plugin follows **Model-View-Controller** architecture:

- **Model**: Data structures (`PatchData`, `PatchBank`, `DeviceModel`)
- **View**: UI components (all `*Panel`, `*Item` classes)
- **Controller**: Business logic (`PatchManager`, `MidiManager`, etc.)

See [Architecture Documentation](ARCHITECTURE.md) for details.

### Threading Model

- **Audio Thread**: Processes MIDI queue (sample-accurate)
- **Message Thread**: UI, device management, file I/O
- **Background Thread**: MIDI input callbacks

See [Threading Model](THREADING_MODEL.md) for details.

### Data Flow

```
User Action → View → Controller → Model → Persistence
                ↓
            UI Update
```

## Contributing

### Branch Strategy

- **`main`**: Production-ready code
- **`development`**: Active development (MVP1)
- **`mvp2`**: Future features branch

### Workflow

1. **Create Feature Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make Changes**
   - Follow [Code Style Guide](CODE_STYLE.md)
   - Write clear commit messages
   - Test thoroughly

3. **Commit**
   ```bash
   git add .
   git commit -m "feat: add feature description"
   ```

4. **Push and Create PR**
   ```bash
   git push origin feature/your-feature-name
   # Create pull request
   ```

### Commit Message Format

Use conventional commits:
- `feat:` New feature
- `fix:` Bug fix
- `docs:` Documentation
- `style:` Code style (formatting)
- `refactor:` Code refactoring
- `test:` Tests
- `chore:` Maintenance

Example:
```
feat: add MIDI learn support for Control Change messages
```

### Code Review Process

1. All code must be reviewed before merge
2. Reviewer checks:
   - Code style compliance
   - Architecture adherence
   - Test coverage
   - Documentation updates

## Code Style

See [Code Style Guide](CODE_STYLE.md) for detailed guidelines.

### Quick Reference

- **Naming**: camelCase for variables, PascalCase for classes
- **Files**: One class per file pair (.h/.cpp)
- **Indentation**: 4 spaces (no tabs)
- **Comments**: Inline for non-trivial logic
- **Const**: Use `const` wherever possible

## Testing

### Manual Testing Checklist

- [ ] Patch operations (rename, recall, copy)
- [ ] Search and filtering
- [ ] Favorites
- [ ] Undo/redo
- [ ] Device selection
- [ ] MIDI output
- [ ] MIDI input
- [ ] Template selection
- [ ] Batch operations
- [ ] Export/import

### Unit Tests (Future)

Unit tests should be added for:
- Model operations
- MIDI message generation
- JSON serialization
- Thread-safe operations

## Debugging

### Common Issues

**MIDI Not Sending**
- Check `MidiManager::isPortOpen()`
- Verify port name matches
- Check MIDI channel (1-16 vs 0-15)

**UI Not Updating**
- Verify `ChangeListener` registered
- Check `sendChangeMessage()` called
- Ensure updates on message thread

**Threading Issues**
- Never access UI from audio thread
- Use `MessageManager::callAsync()` for UI updates
- Check critical sections are used correctly

### Debug Tools

- **MIDI Monitor**: Use `MidiMonitorPanel` to see all MIDI messages
- **JUCE Logger**: Use `juce::Logger::writeToLog()` for debugging
- **Xcode Debugger**: Set breakpoints, inspect variables

## Architecture Decision Records

See [ADRs](ADRs/) directory for architecture decisions.

## Resources

- [JUCE Documentation](https://juce.com/learn/documentation)
- [JUCE Forum](https://forum.juce.com/)
- [C++17 Reference](https://en.cppreference.com/w/cpp/17)

## Questions?

- Check [Architecture Documentation](ARCHITECTURE.md)
- Review [Code Style Guide](CODE_STYLE.md)
- See [ADRs](ADRs/) for design decisions
- Open an issue for questions


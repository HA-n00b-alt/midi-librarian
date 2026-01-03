# MIDI Librarian - Complete Developer Manual

**Version**: 1.0  
**Last Updated**: 2024

---

## Table of Contents

### Part I: Getting Started
- [1. Quick Start](#1-quick-start)
- [2. Prerequisites](#2-prerequisites)
- [3. Initial Setup](#3-initial-setup)

### Part II: Setup & Installation
- [4. Installing Xcode](#4-installing-xcode)
- [5. Setting Up JUCE](#5-setting-up-juce)
- [6. Project Configuration](#6-project-configuration)

### Part III: Building & Testing
- [7. Building in Xcode](#7-building-in-xcode)
- [8. Testing the Plugin](#8-testing-the-plugin)
- [9. Code Signing](#9-code-signing)

### Part IV: Development
- [10. Architecture Overview](#10-architecture-overview)
- [11. Code Style Guidelines](#11-code-style-guidelines)
- [12. Adding Source Files](#12-adding-source-files)
- [13. Threading Model](#13-threading-model)
- [14. Contributing](#14-contributing)

### Part V: Troubleshooting
- [15. Common Build Issues](#15-common-build-issues)
- [16. Plugin Installation Issues](#16-plugin-installation-issues)
- [17. Xcode Issues](#17-xcode-issues)

### Part VI: Reference
- [18. Git Workflow](#18-git-workflow)
- [19. Architecture Decision Records](#19-architecture-decision-records)
- [20. Resources & Links](#20-resources--links)

---

# Part I: Getting Started

## 1. Quick Start

If you're new to the project, follow these steps to get started quickly:

1. **Install Prerequisites** (see [Section 2](#2-prerequisites))
2. **Clone the Repository**
   ```bash
   git clone [repository-url]
   cd midi-librarian
   ```
3. **Open in Projucer**
   - Launch Projucer
   - Open `MIDI Librarian/MIDI Librarian.jucer`
4. **Generate Xcode Project**
   - Click "Save and Open in IDE"
5. **Build**
   - Select scheme: "MIDI Librarian - All"
   - Build (Cmd+B)
6. **Test**
   - Launch Logic Pro
   - Insert plugin on MIDI track
   - Test functionality

For detailed instructions, continue reading this manual.

## 2. Prerequisites

### Required Software

- **macOS 10.13+** (for AUv3 support)
- **Xcode 12+** (for building)
- **JUCE 7.0+** (latest recommended)
- **Projucer** (included with JUCE)
- **C++17** compatible compiler (included with Xcode)
- **Git** (for version control)

### System Requirements

- Minimum: macOS 10.13 (High Sierra)
- Recommended: macOS 11.0+ (Big Sur) or later
- Xcode Command Line Tools

### Installing Prerequisites

See detailed installation guides:
- Xcode: [Section 4](#4-installing-xcode)
- JUCE: [Section 5](#5-setting-up-juce)

## 3. Initial Setup

### 3.1 Clone the Repository

```bash
git clone [repository-url]
cd midi-librarian
```

### 3.2 Project Structure

```
midi-librarian/
├── Source/
│   ├── Model/              # Data models (no UI dependencies)
│   ├── View/               # UI components
│   ├── Controller/         # Business logic
│   ├── PluginProcessor.h/cpp
│   └── PluginEditor.h/cpp
├── MIDI Librarian/
│   ├── MIDI Librarian.jucer  # Projucer project file
│   └── Builds/              # Generated build files (gitignored)
├── docs/
│   ├── user/               # User documentation
│   ├── developer/          # Developer documentation (this manual)
│   └── development/        # Development notes
└── README.md
```

### 3.3 First Build

1. Open `MIDI Librarian/MIDI Librarian.jucer` in Projucer
2. Click "Save and Open in IDE" to generate Xcode project
3. In Xcode, select scheme "MIDI Librarian - All"
4. Build (Cmd+B)
5. Plugin installs to: `~/Library/Audio/Plug-Ins/Components/`

---

# Part II: Setup & Installation

## 4. Installing Xcode

### 4.1 Download Xcode

1. Open the Mac App Store
2. Search for "Xcode"
3. Click "Get" or "Install"
4. Wait for download (Xcode is large, ~10GB+)

### 4.2 First Launch Setup

1. Launch Xcode (Applications → Xcode)
2. Accept license agreement
3. Install additional components when prompted
4. Complete setup wizard

### 4.3 Command Line Tools

Command Line Tools should install automatically, but verify:

```bash
xcode-select --install
```

If already installed, you'll see: "command line tools are already installed"

### 4.4 Verify Installation

```bash
xcodebuild -version
# Should show version number
```

## 5. Setting Up JUCE

### 5.1 Download JUCE

1. Go to [https://juce.com/get-juce](https://juce.com/get-juce)
2. Download latest version (JUCE 7.x recommended)
3. Extract ZIP file

### 5.2 Install JUCE

**Recommended Location:**
```bash
mv ~/Downloads/JUCE ~/Development/JUCE
# Or another permanent location
```

**Alternative (Homebrew):**
```bash
brew install --cask juce
```
*Note: Homebrew version may not be latest*

### 5.3 Build Projucer

Projucer is included with JUCE:

```bash
cd ~/Development/JUCE/extras/Projucer/Builds/MacOSX
open Projucer.xcodeproj
# Build in Xcode, or use pre-built if available
```

### 5.4 Verify JUCE Setup

1. Launch Projucer
2. Projucer → Global Paths
3. Set JUCE Path to: `~/Development/JUCE` (or your location)

## 6. Project Configuration

### 6.1 Projucer Configuration Overview

The Projucer project file (`MIDI Librarian.jucer`) contains all project settings. Key configuration areas:

- **Project Information**: Name, version, bundle identifier
- **Plugin Formats**: AUv3, VST3, etc.
- **Plugin Characteristics**: MIDI Effect, Input/Output
- **Plugin Identification**: Manufacturer, codes, AU Main Type
- **Advanced Settings**: C++ standard, preprocessor definitions

### 6.2 Critical Settings

**⚠️ MUST Configure Correctly:**

1. **Plugin Formats Tab**
   - ✅ AUv3 enabled (REQUIRED)
   - ✅ VST3 enabled (optional)
   - ❌ VST (Legacy) disabled (unless needed)

2. **Plugin Characteristics Tab**
   - ✅ MIDI Effect Plugin (CRITICAL!)
   - ✅ Plugin MIDI Input
   - ✅ Plugin MIDI Output
   - ❌ Plugin is a Synth (unchecked)

3. **Plugin Identification Tab**
   - ✅ Plugin AU Main Type: **kAudioUnitType_MIDIProcessor**
   - Plugin Name: "MIDI Librarian"
   - Plugin Manufacturer: Your company name
   - Plugin Manufacturer Code: 4-letter code (e.g., "DELM")
   - Plugin Code: 4-letter code (e.g., "MLBR")

4. **Advanced Settings Tab**
   - ✅ C++ Language Standard: **C++17**
   - Preprocessor Definitions: (add if needed)

### 6.3 Audio/MIDI Track Support

For plugin to work on both audio and MIDI tracks:

- **Plugin AU Main Type**: `kAudioUnitType_MIDIProcessor` ✅ (CORRECT!)
- This allows the plugin to work on:
  - MIDI tracks (primary use)
  - Audio tracks (for controlling external FX via I/O plugin)

### 6.4 Adding App Icon

1. Prepare 1024x1024 PNG file (or .icns file)
2. In Projucer: Project Information → Icon (if available)
3. Or in Xcode: General tab → App Icons section
4. Save and regenerate Xcode project

### 6.5 Regenerating Xcode Project

After changing Projucer settings:

1. In Projucer, click "Save and Open in IDE"
2. Or: File → Save Project, then open `.xcodeproj` manually
3. Xcode project is regenerated with new settings

**⚠️ Important**: Don't edit generated Xcode project files directly - changes will be lost when regenerating!

---

# Part III: Building & Testing

## 7. Building in Xcode

### 7.1 Opening the Project

1. Navigate to: `MIDI Librarian/Builds/MacOSX/`
2. Double-click `MIDI Librarian.xcodeproj`
3. Xcode opens with your project

**Note**: `.xcodeproj` is a bundle (folder), not a file - this is normal!

### 7.2 Understanding Schemes

For AUv3 plugins, you'll see multiple schemes:

- **"MIDI Librarian - All"**: Builds everything (recommended)
- **"MIDI Librarian AUv3 AppExtension"**: Plugin extension only
- **"MIDI Librarian - VST3"**: VST3 format
- **"MIDI Librarian - Shared Code"**: Shared code library

**Which to Use:**
- Use **"MIDI Librarian - All"** for complete builds
- Or build individual targets as needed

### 7.3 Selecting Scheme and Platform

1. **Show Toolbar**: View → Show Toolbar (Cmd+Option+T)
2. **Scheme Selector**: Top toolbar, left side
   - Click dropdown
   - Select "MIDI Librarian - All"
3. **Platform**: Next to scheme selector
   - Select "My Mac"

### 7.4 Build Settings

**Check C++ Settings:**

1. Select project (top item in navigator)
2. Select target (e.g., "MIDI Librarian AUv3 AppExtension")
3. Build Settings tab
4. Search for "C++ Language Standard"
5. Verify: **C++17** (or GNU++17)

**If not set:**
- Set in Projucer: Advanced Settings → C++ Language Standard
- Or set in Xcode Build Settings
- Regenerate Xcode project

### 7.5 Building

**Method 1: Menu**
- Product → Build (Cmd+B)

**Method 2: Toolbar**
- Click Build button (hammer icon)

**Method 3: Keyboard**
- Press Cmd+B

### 7.6 Build Output

After successful build:

- Plugin installs to: `~/Library/Audio/Plug-Ins/Components/`
- For AUv3: Creates `.app` bundle with `.appex` extension
- For VST3: Creates `.vst3` bundle

**Verify Installation:**
```bash
ls -la ~/Library/Audio/Plug-Ins/Components/ | grep -i midi
```

### 7.7 Clean Build

To clean build artifacts:

1. **Clean Build Folder**: Product → Clean Build Folder (Shift+Cmd+K)
2. Or delete: `MIDI Librarian/Builds/MacOSX/build/`
3. Rebuild (Cmd+B)

## 8. Testing the Plugin

### 8.1 Testing in Logic Pro

1. **Launch Logic Pro**
   - Quit if already running (to detect new plugin)

2. **Create MIDI Track**
   - Create new project or open existing
   - Add MIDI track (Cmd+Option+N)
   - Choose "Software Instrument" or "External MIDI"

3. **Insert Plugin**
   - Click track header
   - Track inspector → MIDI Effects section
   - Click empty slot
   - Navigate to: **MIDI Effects → MIDI Librarian**

4. **Plugin Opens**
   - UI should appear
   - Test functionality

### 8.2 Testing Checklist

- [ ] Plugin appears in MIDI Effects menu
- [ ] Plugin window opens correctly
- [ ] UI elements display properly
- [ ] MIDI Output dropdown shows devices
- [ ] Patch recall sends Program Change
- [ ] Patch renaming works
- [ ] Search/filter works
- [ ] Undo/redo works
- [ ] No crashes or errors

### 8.3 Testing on Audio Tracks

The plugin should also work on audio tracks:

1. Create audio track
2. Insert plugin (should be available)
3. Test MIDI output to external FX via I/O plugin

## 9. Code Signing

### 9.1 Development Signing

For local development and testing:

1. In Xcode, select target
2. Go to **Signing & Capabilities** tab
3. **Code Signing Identity**: Select **"Sign to Run Locally"**
4. **Automatically manage signing**: Can be enabled or disabled
5. No certificate needed for development

### 9.2 Distribution Signing

For distribution (outside App Store):

1. Get **Developer ID Application** certificate from Apple
2. In Xcode: Signing & Capabilities
3. Set **Code Signing Identity** to your Developer ID
4. Enable **"Automatically manage signing"** with your team
5. Build in **Release** configuration

### 9.3 Common Signing Errors

**Error**: "No signing certificate found"

**Solution**: Use "Sign to Run Locally" for development

**Error**: "CodeSign failed with a nonzero exit code"

**Solutions**:
1. Clean build folder (Shift+Cmd+K)
2. Remove extended attributes: `xattr -rc Builds/`
3. Rebuild

See [Section 15.2](#152-code-signing-errors) for more.

---

# Part IV: Development

## 10. Architecture Overview

### 10.1 MVC Pattern

The plugin follows **Model-View-Controller** architecture:

- **Model**: Data structures (`PatchData`, `PatchBank`, `DeviceModel`)
  - No UI dependencies
  - Pure data representation
  - Located in: `Source/Model/`

- **View**: UI components (`DeviceSelectorPanel`, `PatchListPanel`, etc.)
  - Visual presentation only
  - Minimal logic
  - Located in: `Source/View/`

- **Controller**: Business logic (`PatchManager`, `MidiManager`, etc.)
  - Coordinates Model and View
  - Handles user actions
  - Located in: `Source/Controller/`

### 10.2 Data Flow

```
User Action → View → Controller → Model → Persistence
                ↓
            UI Update (via ChangeBroadcaster)
```

### 10.3 Key Components

**PluginProcessor**:
- Main plugin entry point
- Holds PatchManager instance
- Handles plugin state serialization

**PluginEditor**:
- Main UI container
- Manages child panels
- Applies LookAndFeel

**PatchManager**:
- Central controller
- Coordinates all operations
- Manages undo/redo

**MidiManager**:
- MIDI I/O operations
- Device management
- Thread-safe MIDI sending

### 10.4 Threading Model

- **Audio Thread**: Processes MIDI queue (sample-accurate timing)
- **Message Thread**: UI, device management, file I/O
- **Background Thread**: MIDI input callbacks (if needed)

See [Section 13](#13-threading-model) for details.

## 11. Code Style Guidelines

### 11.1 Naming Conventions

**Classes**: PascalCase
```cpp
class PatchManager { };
class DeviceSelectorPanel { };
```

**Functions/Methods**: camelCase
```cpp
void sendProgramChange(int program);
bool isPortOpen() const;
```

**Variables**: camelCase
```cpp
int patchIndex;
juce::String portName;
```

**Constants**: UPPER_SNAKE_CASE or camelCase with `constexpr`
```cpp
static constexpr float BACKGROUND_BRIGHTNESS = 0.98f;
```

**Private Members**: camelCase (no prefix, or `m_` prefix if preferred)
```cpp
private:
    PatchBank patchBank;
    MidiManager midiManager;
```

### 11.2 File Organization

- **One class per file pair** (.h/.cpp)
- **File names match class names**: `PatchManager.h` → `class PatchManager`
- **Header guards**: Use `#pragma once`

### 11.3 Formatting

- **Indentation**: 4 spaces (no tabs)
- **Line length**: 100-120 characters (reasonable limit)
- **Braces**: Opening brace on same line for functions/classes

```cpp
class Example {
public:
    void doSomething() {
        if (condition) {
            // code
        }
    }
};
```

### 11.4 Comments

**Documentation Comments**:
```cpp
/**
 * Sends a MIDI Program Change message to the selected output port.
 * @param program Program number (0-127)
 * @return Result indicating success or failure
 */
juce::Result sendProgramChange(int program);
```

**Inline Comments**:
```cpp
// Process MIDI queue from audio thread for sample-accurate timing
processAudioThread(midiBuffer);
```

### 11.5 Const Correctness

Use `const` wherever possible:

```cpp
const juce::String getName() const;
void processBlock(const juce::AudioBuffer<float>& buffer) const;
```

### 11.6 Memory Management

- Use JUCE's smart pointers when appropriate
- Prefer stack allocation when possible
- Follow RAII principles
- No raw `new`/`delete` in modern code

### 11.7 Error Handling

Use `juce::Result` for operations that can fail:

```cpp
juce::Result sendProgramChange(int program);
if (auto result = midiManager.sendProgramChange(program); result.failed()) {
    // Handle error
}
```

See `CODE_STYLE.md` for complete guidelines.

## 12. Adding Source Files

### 12.1 Adding Files to Projucer

1. **Open Projucer**
2. **Open Project**: `MIDI Librarian/MIDI Librarian.jucer`
3. **Add Files**:
   - Drag files into appropriate group in file tree
   - Or: Right-click group → Add Existing Files
4. **Maintain Folder Structure**:
   - Model files → Model group
   - View files → View group
   - Controller files → Controller group
5. **Save Project**
6. **Regenerate Xcode Project**

### 12.2 File Organization

**Model Files** (`Source/Model/`):
- Pure data structures
- No UI dependencies
- JSON serialization methods

**View Files** (`Source/View/`):
- UI components
- Inherit from `juce::Component`
- Use LookAndFeel for styling

**Controller Files** (`Source/Controller/`):
- Business logic
- Coordinate Model and View
- Handle user actions

### 12.3 Including in PluginProcessor/Editor

1. Add `#include "YourFile.h"` to appropriate header
2. Use the class in implementation
3. Rebuild to verify compilation

## 13. Threading Model

### 13.1 Thread Architecture

**Audio Thread** (`processBlock()`):
- Sample-accurate MIDI processing
- Processes MIDI queue from FIFO
- Must never block
- Must never access UI

**Message Thread**:
- UI updates
- User interactions
- MIDI device management
- File I/O
- State changes

**Background Thread** (if needed):
- MIDI input callbacks
- Long-running operations

### 13.2 MIDI Sending

MIDI messages are queued from the message thread and processed on the audio thread:

1. **UI Action**: User clicks "Recall"
2. **Queue Message**: `MidiManager::sendProgramChange()` queues to FIFO
3. **Audio Thread**: `processBlock()` calls `processAudioThread()`
4. **Send MIDI**: Messages sent with sample-accurate timing

### 13.3 Thread Safety

**Lock-Free FIFO**:
- MIDI message queue uses `AbstractFifo`
- Thread-safe for single producer/single consumer
- No locks needed

**Critical Sections**:
- Device management uses `CriticalSection`
- Protects MIDI port access
- Short-lived locks only

**UI Updates from Other Threads**:
```cpp
juce::MessageManager::callAsync([this]() {
    // Update UI safely
    repaint();
});
```

See `THREADING_MODEL.md` for complete details.

## 14. Contributing

### 14.1 Branch Strategy

- **`main`**: Production-ready, stable code
- **`development`**: Active development branch
- **`mvp2`**: Future features branch
- **`feature/*`**: Feature branches
- **`fix/*`**: Bug fix branches

### 14.2 Development Workflow

1. **Create Feature Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make Changes**
   - Follow code style guidelines
   - Write clear, self-documenting code
   - Add comments for non-trivial logic

3. **Test Thoroughly**
   - Test in Logic Pro
   - Verify no regressions
   - Test edge cases

4. **Commit**
   ```bash
   git add .
   git commit -m "feat: add feature description"
   ```

5. **Push and Create PR**
   ```bash
   git push origin feature/your-feature-name
   # Create pull request
   ```

### 14.3 Commit Message Format

Use [Conventional Commits](https://www.conventionalcommits.org/):

**Types**:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `style`: Code style (formatting)
- `refactor`: Code refactoring
- `test`: Tests
- `chore`: Maintenance

**Examples**:
```
feat: add MIDI learn support for Control Change messages

fix: resolve crash when MIDI port is disconnected

docs: update developer guide with build instructions
```

### 14.4 Code Review Process

1. All code must be reviewed before merge
2. Reviewer checks:
   - Code style compliance
   - Architecture adherence
   - Test coverage
   - Documentation updates

See `CONTRIBUTING.md` for complete guidelines.

---

# Part V: Troubleshooting

## 15. Common Build Issues

### 15.1 Compilation Errors

**Error**: "No such module 'juce_xxx'"

**Solution**:
1. Check JUCE path in Projucer: Global Paths
2. Verify modules are enabled in Projucer: Modules tab
3. Regenerate Xcode project

**Error**: "File not found"

**Solution**:
1. Check files are added in Projucer: Files tab
2. Verify file paths are relative (not absolute)
3. Regenerate Xcode project

**Error**: C++17 features not recognized

**Solution**:
1. Projucer: Advanced Settings → C++ Language Standard → C++17
2. Or Xcode: Build Settings → C++ Language Standard → C++17
3. Regenerate/rebuild

### 15.2 Code Signing Errors

**Error**: "CodeSign failed with a nonzero exit code"

**Common Causes**:
- Extended attributes on build files
- Missing signing certificate
- Build folder permissions

**Solutions**:

1. **Remove Extended Attributes**:
   ```bash
   cd "MIDI Librarian/Builds/MacOSX"
   xattr -rc build
   ```

2. **Use "Sign to Run Locally"**:
   - Xcode: Target → Signing & Capabilities
   - Code Signing Identity: "Sign to Run Locally"

3. **Clean Build Folder**:
   - Product → Clean Build Folder (Shift+Cmd+K)
   - Rebuild

4. **Delete Build Folder**:
   ```bash
   rm -rf "MIDI Librarian/Builds/MacOSX/build"
   ```

See `CODE_SIGNING_FIX.md` and `FIX_EXTENDED_ATTRIBUTES.md` for details.

### 15.3 VST3 Parameter Conflict Error

**Error**: "You may have a conflict with parameter automation between VST2 and VST3"

**Solution**:

1. **Check Projucer**: Plugin Formats tab
   - ✅ VST3 enabled
   - ❌ VST (Legacy/VST2) disabled

2. **Add Preprocessor Define** (if VST2 is already disabled):
   - Projucer: Advanced Settings → Preprocessor Definitions
   - Add: `JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1`
   - Or Xcode: Build Settings → Preprocessor Macros
   - Add: `JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1`

3. **Clean and Rebuild**

See `FIX_VST3_PARAMETER_CONFLICT.md` for details.

### 15.4 Build Succeeds But No Output

**Problem**: Build succeeds but plugin file not found

**Solutions**:

1. **Check Build Log**:
   - Xcode: Report Navigator (Cmd+9)
   - Look for "Copy Files" or "BUILT_PRODUCTS_DIR"
   - Find output path

2. **Check Copy Files Build Phase**:
   - Target → Build Phases
   - Verify "Copy Files" phase exists (for VST3)
   - For AUv3, check if App container is built

3. **Check Schemes**:
   - Build "MIDI Librarian - All" (builds everything)
   - Or build App container + AppExtension separately

4. **Search Manually**:
   ```bash
   find ~/Library/Developer/Xcode/DerivedData -name "*MIDI*Librarian*.app"
   find "MIDI Librarian/Builds/MacOSX/build" -name "*.app"
   ```

See `FINDING_BUILD_OUTPUT.md` for details.

## 16. Plugin Installation Issues

### 16.1 Plugin Not Appearing in Logic Pro

**Problem**: Plugin built successfully but doesn't appear in Logic Pro

**Solutions**:

1. **Verify Installation**:
   ```bash
   ls -la ~/Library/Audio/Plug-Ins/Components/ | grep -i midi
   ```

2. **Check Plugin Structure**:
   - For AUv3: Should be `.app` bundle with `.appex` inside
   - Verify structure is correct

3. **Restart Logic Pro**:
   - Quit Logic Pro completely
   - Relaunch
   - Logic Pro scans plugins on startup

4. **Check Plugin Manager**:
   - Logic Pro → Preferences → Plug-in Manager
   - Look for "MIDI Librarian"
   - Check validation status
   - Click "Reset & Rescan Selection" if needed

5. **Clear Audio Unit Cache**:
   ```bash
   rm ~/Library/Caches/AudioUnitCache/com.apple.audiounits.cache
   ```
   Then restart Logic Pro

6. **Check Code Signing**:
   - Plugin must be signed (even "Sign to Run Locally" works)
   - Verify: `codesign -dv plugin.app`

See `AUV3_INSTALLATION_TROUBLESHOOTING.md` for details.

### 16.2 Plugin Built But Structure Wrong

**Problem**: Plugin builds but Logic Pro doesn't recognize it

**Solutions**:

1. **Check AUv3 Configuration**:
   - Projucer: Plugin Formats → AUv3 enabled
   - May need Standalone enabled too (for App container)
   - Regenerate Xcode project

2. **Verify Schemes**:
   - Should see "MIDI Librarian" (App container) and "MIDI Librarian AUv3 AppExtension"
   - Build both if needed

3. **Check Build Phases**:
   - AUv3 AppExtension target should have installation steps
   - May need to add "Copy Files" build phase manually

See `FIX_PROJUCER_AUV3_CONFIG.md` for details.

### 16.3 Missing Copy Files Build Phase

**Problem**: Plugin builds but doesn't auto-install

**Solution**: Add Copy Files build phase manually:

1. Xcode: Select target → Build Phases tab
2. Click "+" → "New Copy Files Phase"
3. Configure:
   - Destination: "Absolute Path"
   - Path: `$(HOME)/Library/Audio/Plug-Ins/Components`
   - Add plugin file to copy

See `ADD_COPY_FILES_PHASE.md` for details.

## 17. Xcode Issues

### 17.1 Can't Find Scheme Selector

**Problem**: Scheme selector not visible in Xcode

**Solution**:
1. View → Show Toolbar (Cmd+Option+T)
2. Scheme selector is in toolbar at top of window
3. Left side, next to Run/Stop buttons

See `FIND_SCHEME_SELECTOR.md` for details.

### 17.2 Can't Find C++ Settings

**Problem**: C++ Language Standard setting not visible

**Solution**:
1. Build Settings tab
2. Make sure "All" is selected (not "Basic")
3. Search for "C++ Language Standard" or "C++ Language Dialect"
4. If still not found, set in Projucer: Advanced Settings

See `XCODE_CPP_SETTINGS.md` for details.

### 17.3 Build Log Navigation

**Problem**: Can't find build output in build log

**Solution**:
1. Report Navigator: View → Navigators → Show Report Navigator (Cmd+9)
2. Click latest build
3. Search for: "BUILT_PRODUCTS_DIR", "Copy Files", ".app"
4. Scroll to end of build log for installation steps

See `FIND_APP_IN_BUILD_LOG.md` for details.

---

# Part VI: Reference

## 18. Git Workflow

### 18.1 Branch Strategy

- **`main`**: Production-ready code
- **`development`**: Active development (MVP1)
- **`mvp2`**: Future features
- **`feature/*`**: Feature branches
- **`fix/*`**: Bug fix branches

### 18.2 Common Commands

```bash
# Create feature branch
git checkout -b feature/your-feature

# Commit changes
git add .
git commit -m "feat: add feature description"

# Push branch
git push origin feature/your-feature

# Switch branches
git checkout development

# Update from remote
git pull origin development
```

### 18.3 Commit Message Format

See [Section 14.3](#143-commit-message-format) for format details.

## 19. Architecture Decision Records

Architecture Decision Records (ADRs) document important design decisions:

- **ADR-001**: MVC Architecture
- **ADR-002**: Threading Model
- **ADR-003**: JSON Persistence
- **ADR-004**: Custom LookAndFeel
- **ADR-005**: Device Templates

See `ADRs/` directory for complete ADRs.

## 20. Resources & Links

### 20.1 JUCE Resources

- **JUCE Documentation**: https://juce.com/learn/documentation
- **JUCE Forum**: https://forum.juce.com/
- **JUCE Tutorials**: https://juce.com/learn/tutorials
- **JUCE API Reference**: https://juce.com/doc/

### 20.2 Apple Resources

- **Audio Unit Programming Guide**: https://developer.apple.com/documentation/audiotoolbox
- **AUv3 Documentation**: Apple Developer Documentation
- **Code Signing Guide**: https://developer.apple.com/documentation/security

### 20.3 C++ Resources

- **C++17 Reference**: https://en.cppreference.com/w/cpp/17
- **Modern C++ Guidelines**: https://isocpp.github.io/CppCoreGuidelines/

### 20.4 Project Documentation

- **User Guide**: `docs/user/USER_GUIDE.md`
- **Quick Start**: `docs/user/QUICK_START.md`
- **Architecture**: `docs/developer/ARCHITECTURE.md`
- **Code Style**: `docs/developer/CODE_STYLE.md`

---

## Quick Reference Index

### Setup
- [Installing Xcode](#4-installing-xcode)
- [Setting Up JUCE](#5-setting-up-juce)
- [Project Configuration](#6-project-configuration)

### Building
- [Building in Xcode](#7-building-in-xcode)
- [Schemes Explained](#72-understanding-schemes)
- [Build Settings](#74-build-settings)

### Configuration
- [Projucer Settings](#62-critical-settings)
- [Code Signing](#9-code-signing)
- [App Icon](#64-adding-app-icon)

### Troubleshooting
- [Build Errors](#15-common-build-issues)
- [Installation Issues](#16-plugin-installation-issues)
- [Xcode Issues](#17-xcode-issues)

### Development
- [Architecture](#10-architecture-overview)
- [Code Style](#11-code-style-guidelines)
- [Threading](#13-threading-model)
- [Contributing](#14-contributing)

---

## Document History

This manual consolidates the following developer documentation:

- DEVELOPER_GUIDE.md
- SETUP_JUCE.md
- INSTALL_XCODE.md
- PROJUCER_CONFIGURATION.md
- BUILDING_IN_XCODE.md
- CODE_SIGNING_FIX.md
- FIX_EXTENDED_ATTRIBUTES.md
- FIX_VST3_PARAMETER_CONFLICT.md
- FIX_PROJUCER_AUV3_CONFIG.md
- AUV3_INSTALLATION_TROUBLESHOOTING.md
- FINDING_BUILD_OUTPUT.md
- ADD_COPY_FILES_PHASE.md
- ADDING_APP_ICON.md
- And other troubleshooting guides

For specific details, refer to the original individual documentation files in `docs/developer/`.

---

**End of Developer Manual**


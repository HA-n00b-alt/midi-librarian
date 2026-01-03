# JUCE/Projucer Setup Guide

## Overview

This guide will help you set up JUCE and Projucer on macOS to build and debug the MIDI Librarian plugin.

## Prerequisites

- macOS 10.13+ (for AUv3 support)
- Xcode 12+ (for building)
- Git (already installed if you have the repo)

## Step 1: Install JUCE

### Option A: Download from JUCE Website (Recommended)

1. **Download JUCE**
   - Go to [https://juce.com/get-juce](https://juce.com/get-juce)
   - Download the latest version (JUCE 7.x recommended)
   - Extract the ZIP file

2. **Move JUCE to Standard Location**
   ```bash
   # Extract to a permanent location
   mv ~/Downloads/JUCE ~/Development/JUCE
   # Or wherever you prefer to keep it
   ```

### Option B: Install via Homebrew (Alternative)

```bash
# Install Homebrew if you don't have it
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install JUCE
brew install --cask juce
```

**Note**: Homebrew version may not be latest. Manual download is recommended.

## Step 2: Install Projucer

Projucer is included with JUCE. You can either:

### Option A: Use Projucer from JUCE Folder

```bash
# Navigate to JUCE folder
cd ~/Development/JUCE  # or wherever you extracted it

# Open Projucer
open extras/Projucer/Builds/MacOSX/Projucer.xcodeproj
# Build in Xcode, or use pre-built if available
```

### Option B: Download Standalone Projucer

1. Go to [JUCE Downloads](https://juce.com/get-juce)
2. Download Projucer standalone (if available)
3. Move to Applications folder

### Option C: Build Projucer from Source

```bash
cd ~/Development/JUCE/extras/Projucer/Builds/MacOSX
xcodebuild -project Projucer.xcodeproj -scheme Projucer -configuration Release
# Binary will be in build/Release/Projucer.app
```

## Step 3: Create JUCE Project File

> **⚠️ Important**: 
> - See [PROJUCER_CONFIGURATION.md](PROJUCER_CONFIGURATION.md) for complete configuration guide with all settings explained.
> - See [ADDING_SOURCE_FILES.md](ADDING_SOURCE_FILES.md) for detailed guide on adding source files while maintaining folder structure.

Since we don't have a `.jucer` file yet, we need to create one:

### Using Projucer GUI

1. **Open Projucer**
   - Launch Projucer application

2. **Create New Project**
   - File → New Project → Audio Plug-In
   - Or: File → New Project → Basic → Blank Project

3. **Configure Project - Project Information Tab**

   **Basic Settings**:
   - **Project Name**: `MIDI Librarian`
   - **Project Version**: `1.0.0`
   - **Company Name**: Your company name (e.g., `delman`)
   - **Company Copyright**: (optional)
   - **Company Website**: (optional, e.g., `www.delman.it`)
   - **Company E-mail**: (optional)
   - **Bundle Identifier**: `com.yourcompany.MIDILibrarian` (e.g., `com.delman.MIDILibrarian`)
   - **Project Type**: Audio Plug-In

   **Advanced Settings**:
   - **Use Global AppConfig Header**: Disabled (default)
   - **Add "using namespace juce" to JuceHeader.h**: Disabled (default)
   - **Project Line Feed**: Default (\r\n)

4. **Configure Plugin Formats Tab**

   **Enable Formats**:
   - ✅ **AUv3** (required for Logic Pro on macOS)
   - ✅ **VST3** (optional, for other DAWs)
   - ❌ AU (legacy, not needed if using AUv3)
   - ❌ AAX (Pro Tools, optional)
   - ❌ Standalone (not needed for plugin)
   - ❌ LV2 (Linux, optional)
   - ❌ Unity (optional)
   - ❌ VST (Legacy) (optional)

5. **Configure Plugin Characteristics Tab**

   **Critical Settings**:
   - ✅ **MIDI Effect Plugin** (MUST be checked!)
   - ✅ **Plugin MIDI Input** (checked)
   - ✅ **Plugin MIDI Output** (checked)
   - ❌ Plugin is a Synth (unchecked)
   - ❌ Plugin Editor Requires Keyboard Focus (unchecked)
   - ❌ Disable AAX Bypass (unchecked)
   - ❌ Disable AAX Multi-Mono (unchecked)

   **Note**: If "MIDI Effect Plugin" is unchecked, the plugin won't appear in Logic Pro's MIDI Effects menu!

6. **Configure Plugin Identification Tab**

   **Plugin Details**:
   - **Plugin Name**: `MIDI Librarian`
   - **Plugin Description**: `MIDI Librarian for hardware synths`
   - **Plugin Manufacturer**: Your company name (e.g., `Delman`)
   - **Plugin Manufacturer Code**: 4-letter code (e.g., `DELM`)
   - **Plugin Code**: 4-letter code (e.g., `MLBR`)
   - **Plugin Channel Configurations**: (leave empty for MIDI effect)
   - **Plugin AAX Identifier**: `com.yourcompany.MIDILibrarian`
   - **Plugin AU Export Prefix**: `MIDILibrarianAU`

   **Plugin AU Main Type**:
   - ❌ kAudioUnitType_Effect (unchecked)
   - ❌ kAudioUnitType_FormatConverter (unchecked)
   - ❌ kAudioUnitType_Generator (unchecked)
   - ✅ **kAudioUnitType_MIDIProcessor** (CHECKED - this is critical!)
   - All others unchecked

7. **Configure Plugin VST/AU Specific Settings Tab**

   **AU Settings**:
   - **Plugin AU is sandbox safe**: Default (Disabled) - can enable if needed

   **VST Settings**:
   - **Plugin VST Num MIDI Inputs**: Default (16)
   - **Plugin VST Num MIDI Outputs**: Default (16)

8. **Configure Plugin Categories Tab**

   **VST3 Category**:
   - ✅ **Fx** (checked - MIDI effects are in Fx category)
   - ❌ Instrument (unchecked)
   - ❌ Analyzer (unchecked)
   - All others unchecked

   **AAX Category**:
   - Leave defaults (not critical if AAX is disabled)

   **VST (Legacy) Category**:
   - ✅ **kPlugCategEffect** (checked)
   - ❌ kPlugCategSynth (unchecked)
   - All others unchecked

9. **Configure Advanced Settings Tab**

   **C++ Settings**:
   - **C++ Language Standard**: **C++17** (important! Change from default if needed)
   - **Preprocessor Definitions**: (leave empty unless needed)
   - **Header Search Paths**: (leave empty unless needed)

   **Binary Data**:
   - **BinaryData.cpp Size Limit**: Default (10.0 MB)
   - **Include BinaryData in JuceHeader**: Default (Enabled)
   - **BinaryData Namespace**: `BinaryData`

   **LV2** (if using):
   - **LV2 URI**: `www.yourcompany.com/plugins/MIDILibrarian`

   **Post-Export Commands**: (optional, leave empty)

   **Notes**: (optional, for project documentation)

10. **Set Minimum macOS Version**
    - In Build Settings or Project Settings
    - **macOS Deployment Target**: 10.13 (for AUv3 support)

4. **Add Source Files** ⚠️ **IMPORTANT: Keep Folder Structure!**

   **Maintain your existing folder structure** - Projucer will preserve it:
   
   **Option A: Add Entire Source Directory** (Recommended)
   - In Projucer, go to "Files" tab
   - Click "Add Files" or drag and drop
   - Select the entire `Source/` directory
   - Projucer will add all files **maintaining the folder structure**:
     - `Source/Model/` (all .h and .cpp files)
     - `Source/View/` (all .h and .cpp files)
     - `Source/Controller/` (all .h and .cpp files)
     - `Source/PluginProcessor.h/cpp`
     - `Source/PluginEditor.h/cpp`
   
   **Option B: Add Folders Individually**
   - Add `Source/Model/` folder (all files inside)
   - Add `Source/View/` folder (all files inside)
   - Add `Source/Controller/` folder (all files inside)
   - Add `Source/PluginProcessor.h/cpp` files
   - Add `Source/PluginEditor.h/cpp` files
   
   **Why Keep Structure?**
   - Maintains MVC organization (Model/View/Controller)
   - Easier to navigate in Xcode
   - Matches your Git repository structure
   - Better code organization
   
   **What NOT to Do**:
   - ❌ Don't flatten everything into one directory
   - ❌ Don't create new folder structure in Projucer
   - ✅ Keep the existing `Source/Model/`, `Source/View/`, `Source/Controller/` structure

5. **Verify File Structure in Projucer**
   - After adding files, check the "Files" tab
   - You should see the folder structure preserved:
     ```
     Source/
     ├── Model/
     │   ├── PatchData.h/cpp
     │   ├── PatchBank.h/cpp
     │   ├── DeviceModel.h/cpp
     │   └── DeviceTemplate.h/cpp
     ├── View/
     │   ├── ValhallaLookAndFeel.h/cpp
     │   ├── DeviceSelectorPanel.h/cpp
     │   ├── PatchListPanel.h/cpp
     │   └── ... (all view files)
     ├── Controller/
     │   ├── PatchManager.h/cpp
     │   ├── MidiManager.h/cpp
     │   └── ... (all controller files)
     ├── PluginProcessor.h/cpp
     └── PluginEditor.h/cpp
     ```
   - If files are flattened, remove them and re-add using folder structure

6. **Configure Modules**
   - In "Modules" section, ensure these are included:
     - juce_audio_basics
     - juce_audio_devices
     - juce_audio_plugin_client
     - juce_core
     - juce_data_structures
     - juce_events
     - juce_graphics
     - juce_gui_basics
     - juce_gui_extra

7. **Set JUCE Path**
   - In Projucer settings, set JUCE path to your JUCE installation
   - Projucer → Global Paths → JUCE Path
   - Or: Projucer → Preferences → Global Paths → JUCE Path

8. **Save Project**
   - File → Save Project
   - Save as `MIDI Librarian.jucer` in project root (same level as `Source/` directory)
   - This keeps the project file with your source code

### Using Command Line (Alternative)

You can also create a basic `.jucer` file manually, but GUI is easier.

## Step 4: Generate Xcode Project

1. **Open Project in Projucer**
   - File → Open → Select `MIDI Librarian.jucer`

2. **Generate Project**
   - Click "Save and Open in IDE" button
   - Or: File → Save Project (generates Xcode project)

3. **Xcode Project Location**
   - Project will be generated in `Builds/MacOSX/`
   - File: `MIDI Librarian.xcodeproj` (this is a **bundle/folder**, not a single file)
   - Inside: `project.pbxproj` (the actual project file)
   
   **⚠️ Note**: `.xcodeproj` is a bundle (special folder) - this is normal! Just double-click it to open in Xcode.

4. **Open in Xcode**
   - Double-click `MIDI Librarian.xcodeproj` in Finder
   - Or: Xcode opens automatically if you clicked "Save and Open in IDE"
   
   > **📖 Next Steps**: See [BUILDING_IN_XCODE.md](BUILDING_IN_XCODE.md) for detailed build and testing instructions.

## Step 5: Configure Build Settings

### Critical Configuration Checklist

After creating the project, verify these critical settings:

1. **Plugin Characteristics** (MOST IMPORTANT!)
   - ✅ **MIDI Effect Plugin** MUST be checked
   - ✅ Plugin MIDI Input checked
   - ✅ Plugin MIDI Output checked

2. **Plugin AU Main Type**
   - ✅ **kAudioUnitType_MIDIProcessor** MUST be checked
   - All others unchecked

3. **C++ Language Standard**
   - Set to **C++17** (not C++14 or C++11)

4. **Plugin Formats**
   - ✅ AUv3 checked (for Logic Pro)
   - ✅ VST3 checked (optional, for other DAWs)

5. **Plugin Categories**
   - VST3: ✅ Fx category checked
   - VST Legacy: ✅ kPlugCategEffect checked

### Build Configurations

1. **Debug Configuration**
   - For development and debugging
   - Includes debug symbols
   - No code optimization

2. **Release Configuration**
   - For distribution
   - Optimized code
   - Code signing required

### Code Signing (for distribution)

1. **Development Signing**
   - Use "Sign to Run Locally" for testing
   - No certificate needed

2. **Distribution Signing**
   - Set Developer ID Application certificate
   - Required for distribution outside App Store
   - Set in Xcode after generating project

### In Xcode (After Opening)

1. **Select Scheme**
   - Scheme: `MIDI Librarian - AU`
   - Platform: macOS

2. **Build Settings**
   - C++ Language Dialect: C++17
   - C++ Standard Library: libc++
   - Deployment Target: macOS 10.13

3. **Code Signing** (if needed)
   - Development Team: Your team
   - Code Signing Identity: Developer ID Application

## Step 6: Build and Install

> **📖 Detailed Guide**: See [BUILDING_IN_XCODE.md](BUILDING_IN_XCODE.md) for complete step-by-step instructions.

### Quick Steps:

1. **Open Xcode Project**
   - Navigate to `Builds/MacOSX/`
   - Double-click `MIDI Librarian.xcodeproj` (it's a folder/bundle - this is normal!)
   - Xcode opens

2. **Select Scheme**
   - Top toolbar: Select `MIDI Librarian - AU` scheme
   - Platform: `My Mac`

3. **Build**
   - Product → Build (Cmd+B)
   - Or click Build button (hammer icon)

4. **Verify Build**
   - Green checkmark = Success
   - Red X = Check error messages

5. **Plugin Auto-Installs**
   - After successful build, plugin installs to:
   - `~/Library/Audio/Plug-Ins/Components/MIDI Librarian.component`

6. **Test in Logic Pro**
   - Launch Logic Pro
   - Create MIDI track
   - Insert plugin: MIDI Effects → MIDI Librarian
   - Test functionality

## Step 7: Test in Logic Pro

1. **Launch Logic Pro**
2. **Create New Project**
3. **Add MIDI Track**
4. **Insert Plugin**
   - Click on track header
   - Choose "MIDI Effects" → "MIDI Librarian"
5. **Test Plugin**
   - Verify UI opens
   - Test MIDI device selection
   - Test patch operations

## Troubleshooting

### Projucer Can't Find JUCE

**Problem**: Projucer shows "JUCE path not set"

**Solution**:
1. Projucer → Global Paths
2. Set JUCE Path to your JUCE installation
3. Restart Projucer

### Build Errors

**Problem**: Missing modules or includes

**Solution**:
1. Check all modules are added in Projucer
2. Verify JUCE path is correct
3. Clean build folder: Product → Clean Build Folder (Shift+Cmd+K)
4. Rebuild

### Plugin Not Appearing in Logic Pro

**Problem**: Plugin doesn't show in Logic Pro

**Solution**:
1. Check plugin is installed:
   ```bash
   ls ~/Library/Audio/Plug-Ins/Components/
   ```
2. Restart Logic Pro
3. Check Logic Pro → Preferences → Plug-in Manager
4. Verify plugin is enabled

### Code Signing Issues

**Problem**: Code signing errors

**Solution**:
1. For development: Use "Sign to Run Locally"
2. For distribution: Set proper Developer ID
3. Check Keychain Access for certificates

## Quick Setup Script

Save this as `setup_juce.sh`:

```bash
#!/bin/bash

# Check if JUCE is installed
if [ ! -d "$HOME/Development/JUCE" ]; then
    echo "JUCE not found. Please download from https://juce.com/get-juce"
    echo "Extract to ~/Development/JUCE"
    exit 1
fi

# Set JUCE path (if using Projucer from command line)
export JUCE_PATH="$HOME/Development/JUCE"

# Open Projucer
open "$HOME/Development/JUCE/extras/Projucer/Builds/MacOSX/Projucer.xcodeproj"

echo "Projucer opened. Build it in Xcode, then open MIDI Librarian.jucer"
```

## Next Steps

After setup:
1. Build plugin in Xcode
2. Test in Logic Pro
3. Start debugging in `development` branch
4. See [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md) for development workflow

## Resources

- [JUCE Documentation](https://juce.com/learn/documentation)
- [JUCE Forum](https://forum.juce.com/)
- [JUCE Tutorials](https://juce.com/learn/tutorials)

## Notes

- Keep JUCE updated (check for new versions)
- Projucer project file (`.jucer`) should be committed to git
- Xcode project files (`.xcodeproj`) are generated, don't commit
- Build artifacts go in `Builds/` directory (gitignored)


# Complete Projucer Configuration Guide

This guide covers ALL Projucer settings needed for MIDI Librarian plugin.

## Critical Settings (Must Configure)

### 1. Project Information Tab

**Basic Information**:
- **Project Name**: `MIDI Librarian`
- **Project Version**: `1.0.0`
- **Company Name**: Your company (e.g., `delman`)
- **Company Copyright**: (optional)
- **Company Website**: (optional, e.g., `www.delman.it`)
- **Company E-mail**: (optional, e.g., `delman@delman.it`)
- **Bundle Identifier**: `com.yourcompany.MIDILibrarian` (e.g., `com.delman.MIDILibrarian`)

**Advanced Options**:
- **Use Global AppConfig Header**: `Disabled` (default)
- **Add "using namespace juce" to JuceHeader.h**: `Disabled` (default)
- **Project Line Feed**: `Default (\r\n)`
- **Project Type**: `Audio Plug-in`

### 2. Plugin Formats Tab

**Enable These**:
- ✅ **AUv3** (REQUIRED for Logic Pro on macOS)
- ✅ **VST3** (recommended for other DAWs)

**Disable These**:
- ❌ AU (legacy, not needed with AUv3)
- ❌ AAX (Pro Tools, optional)
- ❌ Standalone (not needed)
- ❌ LV2 (Linux, optional)
- ❌ Unity (optional)
- ❌ VST (Legacy) (optional)
- ❌ Enable IAA (optional)
- ❌ Enable ARA (optional)

### 3. Plugin Characteristics Tab ⚠️ CRITICAL

**MUST Check These**:
- ✅ **MIDI Effect Plugin** (CRITICAL - plugin won't work without this!)
- ✅ **Plugin MIDI Input** (checked)
- ✅ **Plugin MIDI Output** (checked)

**Must Uncheck**:
- ❌ Plugin is a Synth
- ❌ Plugin Editor Requires Keyboard Focus
- ❌ Disable AAX Bypass
- ❌ Disable AAX Multi-Mono

**Why This Matters**: If "MIDI Effect Plugin" is unchecked, Logic Pro won't show the plugin in the MIDI Effects menu!

### 4. Plugin Identification Tab

**Plugin Details**:
- **Plugin Name**: `MIDI Librarian`
- **Plugin Description**: `MIDI Librarian for hardware synths` (or your description)
- **Plugin Manufacturer**: Your company name (e.g., `Delman`)
- **Plugin Manufacturer Code**: 4-letter code (e.g., `DELM`)
- **Plugin Code**: 4-letter code (e.g., `MLBR`)
- **Plugin Channel Configurations**: (leave empty for MIDI effect)
- **Plugin AAX Identifier**: `com.yourcompany.MIDILibrarian`
- **Plugin AU Export Prefix**: `MIDILibrarianAU`

**Plugin AU Main Type** ⚠️ CRITICAL:
- ❌ kAudioUnitType_Effect (unchecked)
- ❌ kAudioUnitType_FormatConverter (unchecked)
- ❌ kAudioUnitType_Generator (unchecked)
- ✅ **kAudioUnitType_MIDIProcessor** (MUST be checked!)
- ❌ All other types (unchecked)

**Why This Matters**: `kAudioUnitType_MIDIProcessor` is required for MIDI effects in Logic Pro.

### 5. Plugin VST/AU Specific Settings Tab

**AU Settings**:
- **Plugin AU is sandbox safe**: `Default (Disabled)` (can enable if needed for App Store)

**VST Settings**:
- **Plugin VST Num MIDI Inputs**: `Default (16)` (or set to 1 if only one input needed)
- **Plugin VST Num MIDI Outputs**: `Default (16)` (or set to 1 if only one output needed)

### 6. Plugin Categories Tab

**VST3 Category**:
- ✅ **Fx** (checked - MIDI effects go in Fx category)
- ❌ Instrument (unchecked)
- ❌ Analyzer (unchecked)
- ❌ All other categories (unchecked)

**AAX Category**:
- Leave defaults (not critical if AAX is disabled)

**VST (Legacy) Category**:
- ✅ **kPlugCategEffect** (checked)
- ❌ kPlugCategSynth (unchecked)
- ❌ kPlugCategAnalysis (unchecked)
- ❌ All other categories (unchecked)

### 7. Advanced Settings Tab

**C++ Configuration** ⚠️ IMPORTANT:
- **C++ Language Standard**: **C++17** (change from default if needed)
  - Our code uses C++17 features, so this is required

**Preprocessor Definitions**:
- Leave empty unless you need custom defines
- Example: `DEBUG=1` (not needed, use build configurations instead)

**Header Search Paths**:
- Leave empty unless you have external dependencies
- Example: `/path/to/external/library/include`

**Binary Data Settings**:
- **BinaryData.cpp Size Limit**: `Default (10.0 MB)` (increase if you have large assets)
- **Include BinaryData in JuceHeader**: `Default (Enabled)`
- **BinaryData Namespace**: `BinaryData` (default)

**LV2 Settings** (if using LV2):
- **LV2 URI**: `www.yourcompany.com/plugins/MIDILibrarian`
  - Format: `http://` or `https://` domain + path

**Post-Export Commands**:
- **Post-Export Shell Command (macOS, Linux)**: (optional)
  - Example: `cp plugin.component ~/Library/Audio/Plug-Ins/Components/`
- **Post-Export Shell Command (Windows)**: (optional)

**Notes**:
- Optional field for project documentation
- Example: "MIDI Librarian plugin for managing hardware synth patches"

## Build Settings

### macOS Deployment Target

**In Projucer** (after generating Xcode project):
- Set **macOS Deployment Target** to **10.13** (minimum for AUv3)
- Or set in Xcode: Build Settings → macOS Deployment Target

### Code Signing

**For Development**:
- Use "Sign to Run Locally" in Xcode
- No certificate needed

**For Distribution**:
- Set Developer ID Application certificate
- Required for distribution outside App Store
- Configure in Xcode: Signing & Capabilities

## Common Configuration Mistakes

### ❌ Wrong: MIDI Effect Plugin Unchecked
**Problem**: Plugin won't appear in Logic Pro's MIDI Effects menu
**Fix**: Check "MIDI Effect Plugin" in Plugin Characteristics

### ❌ Wrong: Wrong AU Main Type
**Problem**: Plugin won't work as MIDI effect
**Fix**: Check "kAudioUnitType_MIDIProcessor" in Plugin AU Main Type

### ❌ Wrong: C++ Standard Too Old
**Problem**: Code won't compile (uses C++17 features)
**Fix**: Set C++ Language Standard to C++17

### ❌ Wrong: AUv3 Not Enabled
**Problem**: Won't work in Logic Pro (requires AUv3)
**Fix**: Check AUv3 in Plugin Formats

## Verification Checklist

Before generating Xcode project, verify:

- [ ] Project Name: "MIDI Librarian"
- [ ] Bundle Identifier set correctly
- [ ] AUv3 format enabled
- [ ] **MIDI Effect Plugin checked** (CRITICAL)
- [ ] Plugin MIDI Input/Output checked
- [ ] **kAudioUnitType_MIDIProcessor checked** (CRITICAL)
- [ ] C++17 standard selected
- [ ] VST3 Fx category checked
- [ ] All source files added
- [ ] JUCE modules configured

## After Configuration

1. **Save Project**: File → Save Project (Cmd+S)
2. **Generate Xcode Project**: Click "Save and Open in IDE"
3. **Verify in Xcode**: Check build settings match Projucer settings
4. **Build**: Product → Build (Cmd+B)
5. **Test**: Open Logic Pro and verify plugin appears in MIDI Effects

## Troubleshooting

### Plugin Doesn't Appear in Logic Pro

**Check**:
1. MIDI Effect Plugin is checked
2. kAudioUnitType_MIDIProcessor is checked
3. AUv3 format is enabled
4. Plugin is built and installed
5. Logic Pro is restarted

### Build Errors

**Check**:
1. C++17 standard is set
2. All source files are added
3. JUCE modules are included
4. No missing dependencies

### Code Signing Errors

**Check**:
1. Developer certificate is valid
2. Bundle identifier matches certificate
3. Code signing identity is set in Xcode

## Additional Resources

- [JUCE Plugin Formats Documentation](https://juce.com/learn/documentation)
- [AUv3 Documentation](https://developer.apple.com/documentation/audiounit)
- [JUCE Forum](https://forum.juce.com/)


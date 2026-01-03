# Projucer Settings for Audio + MIDI Track Usage

## Your Requirements

You want the plugin to work on:
1. **Audio tracks** - to control external FX through I/O plugin
2. **MIDI tracks** - for HW synths, VIs, and to control HW synths

## Current Configuration Analysis

### ✅ Current Settings (from .jucer file)

**Plugin AU Main Type:**
- `pluginAUMainType="'aumi'"` = **kAudioUnitType_MIDIProcessor** ✅ CORRECT!

**Plugin Characteristics:**
- `pluginWantsMidiIn` = enabled ✅
- `pluginProducesMidiOut` = enabled ✅

### Why kAudioUnitType_MIDIProcessor is Correct

`kAudioUnitType_MIDIProcessor` (`'aumi'`) is the correct choice because:
- ✅ Works on **MIDI tracks** (primary use case)
- ✅ Works on **audio tracks** (can process MIDI data on audio tracks)
- ✅ Allows MIDI input and output
- ✅ Logic Pro recognizes it in MIDI Effects menu
- ✅ Can send MIDI to external devices (HW synths, external FX via I/O plugin)

**NOT kAudioUnitType_Effect** - that's for audio-processing plugins (EQ, reverb, etc.), not MIDI-only plugins.

## Complete Projucer Configuration Checklist

### 1. Plugin Formats Tab
- ✅ **AUv3** enabled (REQUIRED)
- ✅ **VST3** enabled (optional, for other DAWs)
- ❌ AU (legacy, not needed)
- ⚠️ **Standalone** - Check if needed for App container (see FIX_PROJUCER_AUV3_CONFIG.md)

### 2. Plugin Characteristics Tab ⚠️ CRITICAL

**MUST Enable:**
- ✅ **MIDI Effect Plugin** (CRITICAL!)
- ✅ **Plugin MIDI Input** (checked)
- ✅ **Plugin MIDI Output** (checked)

**MUST Disable:**
- ❌ Plugin is a Synth
- ❌ Plugin Editor Requires Keyboard Focus
- ❌ Disable AAX Bypass
- ❌ Disable AAX Multi-Mono

### 3. Plugin Identification Tab

**Plugin Details:**
- Plugin Name: `MIDI Librarian`
- Plugin Description: `Generic MIDI librarian`
- Plugin Manufacturer: `Delman`
- Plugin Manufacturer Code: `DELM`
- Plugin Code: `MLBR`

**Plugin AU Main Type** ⚠️ CRITICAL:
- ❌ kAudioUnitType_Effect (unchecked)
- ❌ kAudioUnitType_FormatConverter (unchecked)
- ❌ kAudioUnitType_Generator (unchecked)
- ✅ **kAudioUnitType_MIDIProcessor** (CHECKED - this is correct!)
- ❌ All other types (unchecked)

**Why kAudioUnitType_MIDIProcessor:**
- Works on both audio and MIDI tracks
- Processes MIDI data (not audio)
- Can send MIDI output to external devices
- Appears in Logic Pro's MIDI Effects menu

### 4. Plugin VST/AU Specific Settings Tab

**AU Settings:**
- Plugin AU is sandbox safe: `Default (Disabled)`

**VST Settings:**
- Plugin VST Num MIDI Inputs: `Default (16)` or `1`
- Plugin VST Num MIDI Outputs: `Default (16)` or `1`

### 5. Plugin Categories Tab

**VST3 Category:**
- ✅ **Fx** (checked)
- ❌ Instrument (unchecked)
- ❌ Analyzer (unchecked)

**VST (Legacy) Category:**
- ✅ **kPlugCategEffect** (checked)
- ❌ kPlugCategSynth (unchecked)

## Summary: Your Current Settings are Correct!

✅ **pluginAUMainType="'aumi'"** = kAudioUnitType_MIDIProcessor - CORRECT!
✅ **pluginWantsMidiIn** = enabled - CORRECT!
✅ **pluginProducesMidiOut** = enabled - CORRECT!

The only thing to check is whether **Standalone** needs to be enabled in Plugin Formats to generate the App container for AUv3.

## What to Verify in Projucer

1. Open Projucer
2. Open `MIDI Librarian/MIDI Librarian.jucer`
3. Check **Plugin Formats** tab:
   - ✅ AUv3 enabled
   - ⚠️ Check if Standalone needs to be enabled (for App container)
4. Check **Plugin Characteristics** tab:
   - ✅ MIDI Effect Plugin checked
   - ✅ Plugin MIDI Input checked
   - ✅ Plugin MIDI Output checked
5. Check **Plugin Identification** tab:
   - ✅ Plugin AU Main Type = **kAudioUnitType_MIDIProcessor** (should show 'aumi')
6. Save and regenerate Xcode project

## Testing After Configuration

1. Build the plugin
2. Install to `~/Library/Audio/Plug-Ins/Components/`
3. Test in Logic Pro:
   - **On MIDI track**: Should appear in MIDI Effects menu
   - **On audio track**: Should also be available (MIDI processors work on audio tracks)

## Notes

- `kAudioUnitType_MIDIProcessor` is the ONLY correct choice for MIDI-only plugins
- It works on both audio and MIDI tracks
- Do NOT use `kAudioUnitType_Effect` - that's for audio-processing plugins
- Your current configuration is correct for your use case!


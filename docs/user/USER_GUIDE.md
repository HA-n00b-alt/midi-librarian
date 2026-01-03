# MIDI Librarian - User Guide

## Table of Contents

1. [Introduction](#introduction)
2. [Getting Started](#getting-started)
3. [Basic Operations](#basic-operations)
4. [Advanced Features](#advanced-features)
5. [Device Templates](#device-templates)
6. [MIDI Learn](#midi-learn)
7. [Troubleshooting](#troubleshooting)

## Introduction

MIDI Librarian is a plugin for managing patches on hardware synthesizers and digital FX units. It provides a clean interface for organizing, renaming, and recalling patches via MIDI Program Change messages.

### What It Does

- Organizes patches in a 128-slot bank
- Sends MIDI Program Change messages to recall patches
- Stores patch names locally
- Supports device-specific templates
- Provides search and filtering

### What It Doesn't Do

- Does not store actual patch parameters (synth stores those)
- Does not process audio
- Does not create or edit patches (only manages names)

## Getting Started

### First Launch

1. **Select MIDI Output**
   - Open the plugin in Logic Pro
   - In the "MIDI Output" dropdown, select your hardware synth
   - The status indicator will show green when connected

2. **Set MIDI Channel**
   - Choose the MIDI channel (1-16) your synth is listening on
   - Most synths default to channel 1

3. **Select Device Template** (Optional)
   - Choose your synth from the "Device" dropdown
   - This enables device-specific features (patch ranges, bank select, etc.)
   - If your device isn't listed, use "Generic"

### Understanding the Interface

**Top Section - Device Selector**
- **MIDI Output**: Select your hardware synth
- **Channel**: MIDI channel (1-16)
- **Bank**: Bank selection (0-127) with MSB/LSB toggle
- **Device**: Device template selection
- **Status**: Connection indicator (green = connected, red = disconnected)

**Middle Section - Toolbar**
- **Undo/Redo**: Reverse or re-apply operations
- **Copy**: Copy patch to another slot
- **Clear Range**: Clear multiple patches to defaults

**Main Section - Patch List**
- **Search Bar**: Filter patches by name, slot, or tags
- **Favorites Filter**: Show only starred patches
- **Patch Rows**: Each row shows:
  - Slot number (001-128)
  - Patch name (click to edit)
  - ★ button (favorite)
  - Learn button (MIDI learn)
  - Recall button (send Program Change)

## Basic Operations

### Renaming a Patch

1. Click on the patch name in the list
2. Type the new name
3. Press Enter to save, or Escape to cancel
4. Changes are saved automatically

### Recalling a Patch

**Method 1: Recall Button**
1. Click the "Recall" button on the patch row
2. MIDI Program Change is sent immediately

**Method 2: MIDI Learn** (see Advanced Features)

### Marking Favorites

1. Click the ★ button on any patch
2. The star fills in when marked as favorite
3. Click "★ Favorites" filter to show only favorites

### Searching Patches

1. Type in the search bar at the top
2. The list filters in real-time
3. Search matches:
   - Patch names
   - Slot numbers
   - Tags (if added)

## Advanced Features

### Copying Patches

1. Click "Copy" in the toolbar
2. Select source slot (patch to copy from)
3. Select destination slot (patch to copy to)
4. Click OK
5. The patch name and metadata are copied

### Clearing a Range

1. Click "Clear Range" in the toolbar
2. Select start slot
3. Select end slot
4. Click OK
5. All patches in range reset to default names

### Undo/Redo

- **Undo**: Click "Undo" to reverse the last operation
- **Redo**: Click "Redo" to re-apply an undone operation
- Button text shows what action will be undone/redone
- All patch operations are undoable

### Export/Import

**Export** (for backup):
- Use `PersistenceManager::exportToFile()` in code
- Or manually copy `patches.json` from:
  `~/Library/Application Support/MidiLibrarian/`

**Import** (restore backup):
- Use `PersistenceManager::importFromFile()` in code
- Or replace `patches.json` manually

## Device Templates

Device templates provide device-specific features:

- **Patch Ranges**: Some synths have fewer than 128 patches
- **Bank Select**: Method (MSB/LSB) for multi-bank synths
- **Default Channel**: Suggested MIDI channel

### Available Templates

- **Generic**: Default template (0-127 patches, no bank select)
- **Roland JV-1080**: 0-127 patches, MSB bank select
- **Yamaha DX7**: 0-31 patches, no bank select
- **Korg M1**: 0-127 patches, MSB+LSB bank select

### Custom Templates

Custom templates can be added as JSON files in:
`~/Library/Application Support/MidiLibrarian/templates/`

See [Developer Guide](../developer/DEVELOPER_GUIDE.md) for template format.

## MIDI Learn

MIDI Learn allows you to map hardware controllers to patch recall.

### Learning a Mapping

1. Click the "Learn" button on any patch row
2. The row highlights (learning mode)
3. Send a MIDI message from your hardware:
   - Program Change (most common)
   - Control Change (CC)
   - Note On
4. The mapping is created automatically
5. Future messages of that type will recall the patch

### Using Learned Mappings

Once learned, sending the mapped MIDI message from your hardware will automatically recall the patch. This is useful for:
- Hardware controllers with buttons
- MIDI foot pedals
- External sequencers

### Managing Mappings

Mappings are stored in `midi_learn.json` and persist between sessions. To remove a mapping, you'll need to edit the file manually (future: UI for this).

## Troubleshooting

### MIDI Not Working

**Problem**: Program Change not reaching synth

**Solutions**:
1. Check MIDI output port is selected and shows green status
2. Verify MIDI channel matches synth's receive channel
3. Check synth is powered on and connected
4. Try a different MIDI channel
5. Use MIDI monitor to verify messages are sent

### Device Not Listed

**Problem**: Your synth doesn't appear in MIDI output list

**Solutions**:
1. Check synth is powered on
2. Verify USB/MIDI connection
3. Restart Logic Pro (refreshes MIDI device list)
4. Check macOS Audio MIDI Setup

### Patches Not Saving

**Problem**: Changes lost after restart

**Solutions**:
1. Check write permissions for:
   `~/Library/Application Support/MidiLibrarian/`
2. Verify disk space available
3. Check Console.app for errors

### Search Not Working

**Problem**: Search doesn't filter patches

**Solutions**:
1. Clear search bar and try again
2. Check for typos in search query
3. Verify patch names contain search text

## Data Storage

### File Locations

All data is stored in:
`~/Library/Application Support/MidiLibrarian/`

**Files**:
- `patches.json` - Patch bank data
- `config.json` - Device configuration
- `midi_learn.json` - MIDI learn mappings
- `templates/*.json` - Custom device templates

### Backup

To backup your data:
1. Copy the entire `MidiLibrarian` folder
2. Or export patches using export function (when implemented)

### Restore

To restore from backup:
1. Replace the `MidiLibrarian` folder
2. Or import patches using import function (when implemented)

## Keyboard Shortcuts

- **Enter**: Save patch name (when editing)
- **Escape**: Cancel editing
- **Click patch name**: Start editing
- **Click Recall**: Send Program Change

## Tips & Best Practices

1. **Use Templates**: Select your synth's template for best experience
2. **Name Consistently**: Use consistent naming conventions
3. **Use Favorites**: Mark your go-to patches as favorites
4. **Search Often**: Use search to quickly find patches
5. **Backup Regularly**: Export or copy your data folder periodically
6. **MIDI Learn**: Map hardware controllers for faster recall

## FAQ

**Q: Can I use this with multiple synths?**
A: Yes, but you'll need to switch the MIDI output port. Each synth would ideally have its own patch bank (future feature).

**Q: Does this store actual patch parameters?**
A: No, only patch names. The synth stores the actual parameters.

**Q: Can I import patches from other software?**
A: Currently only JSON import is supported. Other formats may be added in future.

**Q: How do I reset everything?**
A: Delete the `MidiLibrarian` folder in Application Support, or use "Clear Range" for all slots.

**Q: Can I use this standalone?**
A: Currently AUv3 only. Standalone app may be added in future.

## Support

For technical issues or feature requests, see the [Developer Guide](../developer/DEVELOPER_GUIDE.md) or open an issue in the repository.


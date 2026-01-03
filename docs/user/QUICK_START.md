# Quick Start Guide

## Installation

1. Build the plugin in Xcode (see [Developer Guide](../developer/DEVELOPER_GUIDE.md))
2. Plugin installs to: `~/Library/Audio/Plug-Ins/Components/`
3. Launch Logic Pro
4. Create new project
5. Add MIDI track
6. Insert "MIDI Librarian" plugin

## First Use

### 1. Select MIDI Device

1. In the plugin window, find "MIDI Output" dropdown
2. Select your hardware synth
3. Status indicator should turn green (connected)

### 2. Set MIDI Channel

1. In "Channel" dropdown, select channel your synth uses (usually 1)
2. Most synths default to channel 1

### 3. Select Device Template (Optional)

1. In "Device" dropdown, select your synth model
2. If not listed, use "Generic"
3. Template enables device-specific features

### 4. Start Organizing

- Click patch names to rename
- Click "Recall" to send Program Change
- Click ★ to mark favorites
- Use search to find patches quickly

## Basic Operations

### Rename Patch
1. Click on patch name
2. Type new name
3. Press Enter to save

### Recall Patch
1. Click "Recall" button on patch row
2. MIDI Program Change sent immediately

### Search Patches
1. Type in search bar at top
2. List filters in real-time
3. Clear search to show all

### Mark Favorite
1. Click ★ button
2. Click "★ Favorites" filter to show only favorites

## Advanced Features

### MIDI Learn
1. Click "Learn" on any patch
2. Row highlights (learning mode)
3. Send MIDI message from hardware
4. Mapping created automatically

### Copy Patch
1. Click "Copy" in toolbar
2. Select source and destination slots
3. Click OK

### Undo/Redo
- Click "Undo" to reverse last operation
- Click "Redo" to re-apply

See [User Guide](USER_GUIDE.md) for complete documentation.

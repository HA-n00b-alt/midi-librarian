# Installing Xcode for JUCE Development

## Quick Check: Do You Have Xcode?

The `.xcodeproj` appearing as a directory is **normal** - it IS a directory (bundle). But if you can't open it, you might not have Xcode installed.

## Check if Xcode is Installed

### Method 1: Check Applications Folder
```bash
ls /Applications/ | grep -i xcode
```

If you see `Xcode.app`, it's installed.

### Method 2: Check Command Line Tools
```bash
xcodebuild -version
```

If this works, Xcode is installed.

### Method 3: Check Finder
- Open Finder
- Go to Applications
- Look for "Xcode" app

## Installing Xcode

### Option 1: App Store (Recommended)

1. **Open App Store**
   - Click Apple menu → App Store
   - Or search for "App Store" in Spotlight

2. **Search for Xcode**
   - Type "Xcode" in search
   - Click "Get" or "Install"
   - **Note**: Xcode is large (~12GB), download takes time

3. **Wait for Download**
   - Download can take 30+ minutes depending on internet
   - You can check progress in App Store

4. **Launch Xcode**
   - After installation, open Xcode from Applications
   - First launch: Accept license agreement
   - Install additional components (prompted)

### Option 2: Developer Website

1. **Go to Apple Developer**
   - Visit: https://developer.apple.com/xcode/
   - Sign in with Apple ID (free account works)

2. **Download Xcode**
   - Download latest version
   - Install the `.xip` file

3. **Extract and Install**
   - Double-click `.xip` file
   - Wait for extraction
   - Drag Xcode to Applications folder

## After Installing Xcode

### 1. Accept License Agreement

```bash
sudo xcodebuild -license accept
```

Or launch Xcode and accept when prompted.

### 2. Install Command Line Tools

```bash
xcode-select --install
```

Or in Xcode:
- Xcode → Settings → Locations
- Command Line Tools: Select version

### 3. Verify Installation

```bash
xcodebuild -version
```

Should show something like:
```
Xcode 15.0
Build version 15A240d
```

## Opening the Project

### Once Xcode is Installed

**Method 1: Double-click**
- Navigate to: `MIDI Librarian/Builds/MacOSX/`
- Double-click `MIDI Librarian.xcodeproj`
- Xcode opens automatically

**Method 2: Open from Terminal**
```bash
cd "MIDI Librarian/Builds/MacOSX"
open "MIDI Librarian.xcodeproj"
```

**Method 3: Open from Xcode**
- Launch Xcode
- File → Open
- Navigate to `MIDI Librarian/Builds/MacOSX/MIDI Librarian.xcodeproj`
- Click Open

## Understanding .xcodeproj

### It IS a Directory (This is Normal!)

`.xcodeproj` is a **bundle** (special folder) in macOS:
- In Finder: Appears as a single file (with special icon)
- In Terminal: Shows as a directory
- Contains: `project.pbxproj` and other files

**This is correct!** Just open it with Xcode.

## System Requirements

- **macOS**: 13.0 (Ventura) or later for Xcode 15
- **Disk Space**: ~15GB for Xcode + build tools
- **RAM**: 8GB minimum, 16GB recommended

## Alternative: Use Xcode Command Line Tools Only

If you only want to build (not use Xcode GUI):

```bash
# Install command line tools only
xcode-select --install

# Build from command line
cd "MIDI Librarian/Builds/MacOSX"
xcodebuild -project "MIDI Librarian.xcodeproj" -scheme "MIDI Librarian - AU" -configuration Debug
```

But for development and debugging, full Xcode is recommended.

## Troubleshooting

### "Xcode can't be opened" Error

**Solution**:
1. Right-click Xcode.app
2. Select "Open"
3. Click "Open" in security dialog
4. This bypasses Gatekeeper for first launch

### "Command Line Tools Not Found"

**Solution**:
```bash
xcode-select --install
```

### "License Agreement Not Accepted"

**Solution**:
```bash
sudo xcodebuild -license accept
```

## Next Steps After Installing

1. ✅ Install Xcode from App Store
2. ✅ Accept license agreement
3. ✅ Install command line tools
4. ✅ Open project: `open "MIDI Librarian/Builds/MacOSX/MIDI Librarian.xcodeproj"`
5. ✅ Build: Press `Cmd+B` in Xcode
6. ✅ Test in Logic Pro

## Summary

- `.xcodeproj` IS a directory (bundle) - this is normal
- If you can't open it, install Xcode from App Store
- Xcode is free but large (~12GB download)
- After installing, double-click `.xcodeproj` to open
- Full Xcode needed for GUI development and debugging


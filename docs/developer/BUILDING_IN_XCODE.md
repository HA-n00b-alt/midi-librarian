# Building in Xcode - Step by Step Guide

## Understanding the Xcode Project Structure

### ✅ This is CORRECT!

When Projucer generates the Xcode project, you'll see:

```
Builds/MacOSX/
└── MIDI Librarian.xcodeproj/    ← This is a BUNDLE (folder), not a file!
    └── project.pbxproj          ← The actual project file
```

**This is normal!** In macOS, `.xcodeproj` is a **package/bundle** (a special folder that looks like a file in Finder). It contains:
- `project.pbxproj` - The main project file with all settings
- Other files (schemes, workspace data, etc.) may be added later

### Opening the Project

**Method 1: Double-click in Finder**
- Navigate to `Builds/MacOSX/`
- Double-click `MIDI Librarian.xcodeproj`
- Xcode will open

**Method 2: Open from Terminal**
```bash
cd "MIDI Librarian/Builds/MacOSX"
open "MIDI Librarian.xcodeproj"
```

**Method 3: Open from Projucer**
- Click "Save and Open in IDE" button
- Xcode opens automatically

## Step-by-Step: First Build

### 1. Open Xcode Project

1. Navigate to: `MIDI Librarian/Builds/MacOSX/`
2. Double-click `MIDI Librarian.xcodeproj`
3. Xcode opens with your project

**Expected**: You should see the project in the left sidebar (Project Navigator)

### 2. Select Scheme and Platform

**For AUv3 Plugins**: You'll see **"MIDI Librarian AUv3 AppExtension"** - this is correct!

**⚠️ If you don't see the scheme selector:**

1. **Show Toolbar**: View → Show Toolbar (or press `Cmd+Option+T`)
2. The scheme selector is in the **toolbar at the top** of the Xcode window

**Once toolbar is visible**, you'll see:

```
[Stop] [MIDI Librarian AUv3 AppExtension ▼] [My Mac ▼] [▶] [🔨]
```

- **Scheme**: Click dropdown, select **`MIDI Librarian AUv3 AppExtension`** ← This is the correct one!
  - For AUv3 plugins, you'll see "AppExtension" scheme (this is what you need)
  - Or `MIDI Librarian - VST3` if you enabled VST3
- **Platform**: Click dropdown, select `My Mac` (or your target Mac)
- **Architecture**: Usually auto-detected

> **📖 Note**: See [AUv3_SCHEME_EXPLANATION.md](AUv3_SCHEME_EXPLANATION.md) for why you see "AppExtension" scheme.

> **📖 Troubleshooting**: See [XCODE_SCHEME_SELECTOR.md](XCODE_SCHEME_SELECTOR.md) if you can't find the scheme selector.

### 3. Check Build Settings (Optional but Recommended)

1. Click on project name in left sidebar (top item)
2. Select the project (not target)
3. Go to "Build Settings" tab
4. **Make sure "All" is selected** (not "Basic")
5. **Search for "C++"** in the search box (top right)
6. Verify:
   - **C++ Language Dialect** (or "C++ Language Standard"): `C++17` (or `GNU++17`)
     - **Note**: If you only see "C Language Dialect", search for "C++" to find the C++ setting
   - **C++ Standard Library**: `libc++`
   - **macOS Deployment Target**: `10.13` (or higher)

> **📖 Can't find it?**: See [XCODE_CPP_SETTINGS.md](XCODE_CPP_SETTINGS.md) for detailed instructions, or set it in Projucer's Advanced Settings tab.

### 4. Build the Project

**Method 1: Menu**
- Product → Build (or press `Cmd+B`)

**Method 2: Toolbar**
- Click the Build button (hammer icon)

**Method 3: Keyboard**
- Press `Cmd+B`

### 5. Check for Errors

- **Build Succeeded**: Green checkmark in status bar
- **Build Failed**: Red X with error messages

**Common First-Time Issues**:
- Missing JUCE modules → Check modules in Projucer
- Missing source files → Verify all files added in Projucer
- Code signing errors → Use "Sign to Run Locally" for development

### 6. Install Plugin

After successful build, the plugin is automatically installed to:
```
~/Library/Audio/Plug-Ins/Components/MIDI Librarian.component
```

**Verify Installation**:
```bash
ls -la ~/Library/Audio/Plug-Ins/Components/ | grep -i midi
```

## Step-by-Step: Testing in Logic Pro

### 1. Launch Logic Pro

- Open Logic Pro
- Create new project or open existing

### 2. Create MIDI Track

1. Create new track (Cmd+Option+N)
2. Choose "Software Instrument" or "External MIDI"
3. Click track header

### 3. Insert Plugin

1. In track inspector, find "MIDI Effects" section
2. Click empty slot
3. Navigate to: **MIDI Effects → MIDI Librarian**
4. Plugin window opens

### 4. Test Plugin

- Verify UI appears correctly
- Test MIDI device selection
- Test patch operations
- Check for crashes or errors

## Troubleshooting

### Build Errors

**Problem**: "No such module 'juce_xxx'**

**Solution**:
1. Go back to Projucer
2. Check "Modules" tab
3. Ensure all required modules are checked
4. Save project
5. Regenerate Xcode project

**Problem**: "File not found" errors

**Solution**:
1. Check Projucer "Files" tab
2. Verify all source files are added
3. Check file paths are relative (not absolute)
4. Regenerate Xcode project

**Problem**: Code signing errors

**Solution**:
1. In Xcode: Project Settings → Signing & Capabilities
2. Select "Sign to Run Locally" (for development)
3. Or set proper Developer ID (for distribution)

### Plugin Not Appearing in Logic Pro

**Problem**: Plugin doesn't show in Logic Pro

**Solution**:
1. Verify plugin is installed:
   ```bash
   ls ~/Library/Audio/Plug-Ins/Components/MIDI\ Librarian.component
   ```
2. Restart Logic Pro
3. Check Logic Pro → Preferences → Plug-in Manager
4. Verify plugin is enabled
5. Check Projucer settings:
   - ✅ MIDI Effect Plugin checked
   - ✅ kAudioUnitType_MIDIProcessor checked
   - ✅ AUv3 format enabled

### Xcode Project Structure

**Question**: Why is `.xcodeproj` a folder?

**Answer**: This is normal! Xcode projects are bundles (special folders):
- `.xcodeproj` = Bundle containing project files
- `project.pbxproj` = Main project file
- Other files may be added (schemes, user data, etc.)

**Don't worry** - just double-click the `.xcodeproj` folder to open in Xcode.

## Development Workflow

### Making Changes

1. **Edit Source Code**
   - Edit files in `Source/` directory (outside Xcode)
   - Or edit in Xcode (if you prefer)

2. **Build**
   - Press `Cmd+B` in Xcode
   - Plugin rebuilds and reinstalls

3. **Test**
   - Open Logic Pro
   - Plugin updates automatically (may need to reload)

### Debugging

1. **Set Breakpoints**
   - Click left margin in Xcode editor
   - Red dot appears

2. **Run with Debugger**
   - Product → Run (Cmd+R)
   - Attach to Logic Pro process
   - Or: Product → Attach to Process → Logic Pro

3. **View Logs**
   - View → Debug Area → Show Debug Area (Cmd+Shift+Y)
   - Console shows output

### Updating Projucer Settings

1. **Change Settings in Projucer**
   - Open `MIDI Librarian.jucer` in Projucer
   - Make changes
   - Save project

2. **Regenerate Xcode Project**
   - File → Save Project
   - Or: Click "Save and Open in IDE"
   - Xcode project updates

3. **Rebuild in Xcode**
   - Clean build folder: Product → Clean Build Folder (Shift+Cmd+K)
   - Build: Product → Build (Cmd+B)

## Quick Reference

### Essential Commands
- **Build**: `Cmd+B`
- **Clean**: `Shift+Cmd+K`
- **Run**: `Cmd+R`
- **Stop**: `Cmd+.`

### Project Locations
- **Xcode Project**: `Builds/MacOSX/MIDI Librarian.xcodeproj/`
- **Plugin Output**: `~/Library/Audio/Plug-Ins/Components/MIDI Librarian.component`
- **Source Code**: `Source/` (in project root)
- **Projucer File**: `MIDI Librarian/MIDI Librarian.jucer` (or root)

### Next Steps After First Build

1. ✅ Verify build succeeds
2. ✅ Test plugin in Logic Pro
3. ✅ Check UI appears correctly
4. ✅ Test basic functionality
5. ✅ Start debugging any issues

## Summary

**What you have is correct!**
- `MIDI Librarian.xcodeproj/` is a bundle (folder)
- `project.pbxproj` inside is the project file
- Double-click `.xcodeproj` to open in Xcode
- Build with `Cmd+B`
- Plugin installs automatically
- Test in Logic Pro

You're ready to build and debug! 🚀


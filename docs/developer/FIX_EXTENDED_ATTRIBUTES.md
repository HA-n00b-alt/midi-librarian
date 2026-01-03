# Fixing "Resource Fork, Finder Information, or Similar Detritus" Error

## Problem

When building AUv3 plugins, you may see this error:

```
resource fork, Finder information, or similar detritus not allowed
Command CodeSign failed with a nonzero exit code
```

This happens when files have **extended attributes** (metadata added by macOS, cloud storage, or Finder).

## Common Causes

1. **Cloud Storage**: Dropbox, iCloud, Google Drive add extended attributes
2. **Finder Metadata**: Files copied from network drives or external storage
3. **Resource Forks**: Legacy macOS resource forks (rare in modern macOS)

## Solution: Remove Extended Attributes

### Method 1: Clean Build Folder (Recommended)

1. **In Xcode**:
   - Product → Clean Build Folder (Shift+Cmd+K)
   - This removes the build folder entirely

2. **Rebuild**:
   - Product → Build (Cmd+B)

### Method 2: Remove Extended Attributes from Build Folder

**In Terminal**:

```bash
cd "/path/to/midi-librarian/MIDI Librarian/Builds/MacOSX"
xattr -rc build
```

This removes all extended attributes recursively from the build folder.

### Method 3: Remove from Entire Project (If Method 1 & 2 Don't Work)

**In Terminal**:

```bash
cd "/path/to/midi-librarian"
xattr -rc "MIDI Librarian/Builds"
```

### Method 4: Remove from Specific File

If you know the exact file causing issues:

```bash
xattr -c "/path/to/file.appex"
```

## Prevention

### Option 1: Exclude Build Folders from Cloud Sync

**For Dropbox**:
1. Open Dropbox preferences
2. Go to "Sync" tab
3. Add `Builds/` folder to exclusions
4. Or move project outside Dropbox for development

**For iCloud**:
1. Move project to local folder (not iCloud Drive)
2. Or exclude `Builds/` from iCloud sync

### Option 2: Use .gitignore (Already Done)

The `.gitignore` already excludes `Builds/` folder, so Git won't track these files.

### Option 3: Build Script (Advanced)

Add a build phase script in Xcode to clean extended attributes before building:

1. Xcode → Project → Target → Build Phases
2. Click "+" → "New Run Script Phase"
3. Add script:
   ```bash
   find "${BUILT_PRODUCTS_DIR}" -type f -exec xattr -c {} \;
   ```

## Quick Fix Script

Create a script to clean extended attributes:

```bash
#!/bin/bash
# clean_xattr.sh

PROJECT_DIR="/path/to/midi-librarian"
cd "$PROJECT_DIR"

echo "Cleaning extended attributes from build folder..."
xattr -rc "MIDI Librarian/Builds" 2>/dev/null
echo "Done! Now rebuild in Xcode."
```

Make it executable:
```bash
chmod +x clean_xattr.sh
```

## Verification

Check if extended attributes are removed:

```bash
xattr -l "/path/to/file.appex"
```

Should return nothing (no attributes).

## If Problem Persists

1. **Move project outside cloud storage**:
   - Copy project to `~/Documents/` or `~/Projects/`
   - Build from there
   - Only sync source code, not build artifacts

2. **Check for other metadata**:
   ```bash
   ls -l@ "/path/to/file.appex"
   ```
   The `@` shows extended attributes

3. **Clean DerivedData**:
   ```bash
   rm -rf ~/Library/Developer/Xcode/DerivedData/MIDI_Librarian-*
   ```

## Summary

**Quick Fix**:
1. Product → Clean Build Folder (Shift+Cmd+K) in Xcode
2. Product → Build (Cmd+B)

**If that doesn't work**:
```bash
cd "MIDI Librarian/Builds/MacOSX"
xattr -rc build
```

Then rebuild in Xcode.


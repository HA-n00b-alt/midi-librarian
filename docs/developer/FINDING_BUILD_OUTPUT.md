# Finding and Installing AUv3 Plugin Build Output

## Problem: Plugin Component File Not Found

After a successful build, you cannot find the `.component` file. This is a common issue with AUv3 plugins.

## Understanding AUv3 Build Structure

AUv3 plugins require **two targets** to be built:
1. **App Container** (the wrapper app)
2. **App Extension** (the actual plugin - `.appex` file)

The `.appex` file must be bundled into a `.component` bundle for installation.

## Finding the Build Output

### Method 1: Check Xcode's Build Log

1. In Xcode, open the **Report Navigator** (⌘9 or View → Navigators → Show Report Navigator)
2. Click on your most recent build
3. Look for lines containing:
   - `BUILT_PRODUCTS_DIR`
   - `Copying` or `Installing`
   - Paths ending in `.appex` or `.component`

### Method 2: Check Build Settings

1. In Xcode, select your project in the navigator
2. Select the **"MIDI Librarian AUv3 AppExtension"** target
3. Go to **Build Settings** tab
4. Search for: **`INSTALL_PATH`** or **`BUILT_PRODUCTS_DIR`**
5. Note the path - this is where the plugin should be built

### Method 3: Manual Search

Check these locations:

```bash
# DerivedData Products (most common)
~/Library/Developer/Xcode/DerivedData/MIDI_Librarian-*/Build/Products/

# Local build folder
MIDI Librarian/Builds/MacOSX/build/Debug/
MIDI Librarian/Builds/MacOSX/build/Release/

# Check for .appex files (AUv3 extensions)
find ~/Library/Developer/Xcode/DerivedData -name "*.appex" -type d 2>/dev/null
```

## Manual Installation (If Auto-Install Failed)

If the plugin didn't auto-install, you can manually install it:

### Step 1: Find the .appex File

1. In Xcode: Product → Build For → Running (⌘R) or just Build (⌘B)
2. In the build log (Report Navigator), find the path to the `.appex` file
3. Or search manually:
   ```bash
   find ~/Library/Developer/Xcode/DerivedData -name "*.appex" -type d 2>/dev/null
   ```

### Step 2: Create the Component Bundle

AUv3 plugins need to be in a `.component` bundle structure:

```bash
# Create the component bundle directory
mkdir -p ~/Library/Audio/Plug-Ins/Components/"MIDI Librarian.component"/Contents

# Copy the .appex file into the component
# Replace /path/to/MIDI Librarian.appex with the actual path from Step 1
cp -R "/path/to/MIDI Librarian.appex" \
  ~/Library/Audio/Plug-Ins/Components/"MIDI Librarian.component"/Contents/MIDI\ Librarian.appex

# Create Info.plist (if needed - JUCE usually generates this)
```

### Step 3: Verify Installation

```bash
ls -la ~/Library/Audio/Plug-Ins/Components/ | grep -i midi
```

## Common Issues

### Issue: Build Succeeds But No Output

**Cause**: Only the AppExtension target was built, but the installation build phase didn't run.

**Solution**: 
1. Check if there's a "Copy Files" build phase in the target
2. Verify the installation path is set correctly
3. Try building the **main app target** as well (not just the extension)

### Issue: .appex File Found But Not in Components Folder

**Cause**: Auto-install step failed or isn't configured.

**Solution**: Manually copy as described in "Manual Installation" above.

### Issue: Plugin Built But Logic Pro Doesn't See It

**Solutions**:
1. Restart Logic Pro
2. Check Logic Pro → Preferences → Plug-in Manager
3. Verify the plugin is properly signed (even "Sign to Run Locally" should work)
4. Check Console.app for plugin loading errors

## Recommended: Check Xcode Build Phases

1. Select the **"MIDI Librarian AUv3 AppExtension"** target
2. Go to **Build Phases** tab
3. Look for:
   - **"Copy Files"** phase (should copy to Components folder)
   - **"Run Script"** phase (might handle installation)

If these phases are missing, JUCE's build system should have added them. You may need to:
1. Regenerate the Xcode project from Projucer
2. Or add them manually (advanced)

## Quick Diagnostic Script

Run this to search for build outputs:

```bash
#!/bin/bash
echo "Searching for MIDI Librarian build outputs..."
echo ""
echo "=== DerivedData Products ==="
find ~/Library/Developer/Xcode/DerivedData -name "*MIDI*Librarian*" -type d 2>/dev/null | head -10
echo ""
echo "=== .appex files ==="
find ~/Library/Developer/Xcode/DerivedData -name "*.appex" -type d 2>/dev/null | head -5
echo ""
echo "=== Components folder ==="
ls -la ~/Library/Audio/Plug-Ins/Components/ 2>/dev/null
echo ""
echo "=== Local build folder ==="
find "MIDI Librarian/Builds/MacOSX/build" -name "*.appex" -o -name "*.component" 2>/dev/null
```

## Next Steps

1. **First**: Check Xcode's Build Report Navigator to see where files were actually built
2. **Then**: Use the path from the build log to manually install if needed
3. **Finally**: If still not working, check if both targets (app + extension) need to be built


# AUv3 Plugin Installation Troubleshooting

## Problem: Plugin Built Successfully But Doesn't Appear in Logic Pro

### Current Status

The plugin has been built and the `.appex` file exists at:
```
MIDI Librarian/Builds/MacOSX/build/Debug/MIDI Librarian.appex
```

The plugin has been manually installed to:
```
~/Library/Audio/Plug-Ins/Components/MIDI Librarian.app
```

However, Logic Pro doesn't recognize it.

## Possible Issues

### Issue 1: Missing App Container Executable

For AUv3 plugins, JUCE typically builds:
1. **Main App Container** (executable app)
2. **App Extension** (the `.appex` file)

We may only have the extension, not the full app container.

**Solution**: Check if you need to build the main app target as well.

### Issue 2: Check Xcode Build Log

The build log will show exactly what was built and where.

**Steps**:
1. Open Xcode
2. Press `⌘9` (or View → Navigators → Show Report Navigator)
3. Click on your most recent build
4. Search for:
   - `BUILT_PRODUCTS_DIR` - shows where files were built
   - `Copying` or `Installing` - shows installation steps
   - `.app` or `.component` - shows the actual output files

### Issue 3: Check Build Settings

1. In Xcode, select the project
2. Select **"MIDI Librarian AUv3 AppExtension"** target
3. Go to **Build Settings** tab
4. Search for:
   - `INSTALL_PATH` - where the plugin should be installed
   - `PRODUCT_BUNDLE_IDENTIFIER` - should match Info.plist

### Issue 4: Missing Build Phase

JUCE should add a "Copy Files" build phase that installs the plugin.

**Check**:
1. Select the **"MIDI Librarian AUv3 AppExtension"** target
2. Go to **Build Phases** tab
3. Look for "Copy Files" phase
4. It should copy to `$(HOME)/Library/Audio/Plug-Ins/Components/`

If missing, the plugin won't auto-install.

### Issue 5: Plugin Structure

For AUv3, the structure should be:
```
MIDI Librarian.app/
  └── Contents/
      ├── Info.plist
      ├── MacOS/
      │   └── MIDI Librarian (executable)
      └── PlugIns/
          └── MIDI Librarian.appex/
              └── Contents/
                  ├── Info.plist
                  ├── MacOS/
                  └── ...
```

We currently have the `.appex` but may be missing the main executable.

## Solutions to Try

### Solution 1: Build Main App Target

1. In Xcode, check what schemes are available
2. You might see:
   - "MIDI Librarian" (main app)
   - "MIDI Librarian AUv3 AppExtension" (extension)
3. Try building the main app target first, then the extension
4. Or build both together

### Solution 2: Check JUCE Documentation

JUCE's AUv3 build process should create the proper structure automatically. Check:
- [JUCE Audio Plugins Tutorial](https://juce.com/learn/tutorials)
- JUCE Forum for AUv3 installation issues

### Solution 3: Use Install Script

A script is available at:
```
install_plugin.sh
```

Run it after each build to manually install the plugin.

### Solution 4: Clear Audio Unit Cache

If the plugin structure is wrong, Logic Pro may have cached the error:

```bash
rm ~/Library/Caches/AudioUnitCache/com.apple.audiounits.cache
```

Then restart Logic Pro.

### Solution 5: Check Plugin Validation

1. Open Logic Pro → Preferences → Plug-in Manager
2. Look for "MIDI Librarian" or "Delman: MIDI Librarian"
3. Check validation status
4. If it shows an error, click it to see details

### Solution 6: Check Console for Errors

1. Open Console.app (Applications → Utilities)
2. Filter for "MIDI Librarian" or "audiounit"
3. Look for error messages when Logic Pro scans plugins

## Recommended Next Steps

1. **First**: Check Xcode's build log to see what was actually built
2. **Second**: Check if there's a main app target that needs to be built
3. **Third**: Verify the Build Phases include a "Copy Files" phase
4. **Fourth**: If structure is wrong, check JUCE documentation for correct AUv3 structure
5. **Fifth**: Clear Audio Unit cache and restart Logic Pro

## Alternative: Check JUCE Example Projects

Look at JUCE's example AUv3 plugin projects to see:
- How the build is configured
- What the output structure looks like
- How installation is handled

Example location (if JUCE is installed):
```
~/Development/JUCE/examples/Plugins/
```

## Quick Diagnostic Command

Run this to check current installation:

```bash
# Check if plugin exists
ls -la ~/Library/Audio/Plug-Ins/Components/ | grep -i midi

# Check code signing
codesign -dv --verbose=4 ~/Library/Audio/Plug-Ins/Components/MIDI\ Librarian.app

# Check plugin structure
find ~/Library/Audio/Plug-Ins/Components/MIDI\ Librarian.app -type f | head -20

# Check for validation errors
pluginkit -m -A | grep -i midi
```


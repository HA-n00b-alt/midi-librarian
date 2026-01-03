# How to Find the .app File in Xcode Build Log

## Steps

1. **In Xcode, you're already in the build log** (you see the VST3 warning)

2. **Scroll to the END of the build log**:
   - Look for the last build step
   - The final steps usually show where files were copied or created

3. **Search for these keywords** (⌘F to search in the build log):
   - `BUILT_PRODUCTS_DIR` - Shows where products were built
   - `Copy Files` - Shows installation/copy steps
   - `.app` - Shows app bundle paths
   - `MIDI Librarian.app` - Direct search for your app
   - `CodeSign` - Code signing step (happens after building, shows the file path)

4. **Look for paths like**:
   - `~/Library/Developer/Xcode/DerivedData/MIDI_Librarian-*/Build/Products/Debug/MIDI Librarian.app`
   - Or: `/Users/andreadelmiglio/Documents/Git local/midi-librarian/MIDI Librarian/Builds/MacOSX/build/Debug/MIDI Librarian.app`

5. **Alternative: Check the "Copy Files" phase execution**:
   - Search for "Copy Files" in the build log
   - It should show what file was copied and where

## If You Still Can't Find It

The .app might not have been built if:
- Only the AppExtension scheme was built (not the main App scheme)
- The build failed silently
- The output is in a non-standard location

**Check which scheme you built:**
- Did you build "MIDI Librarian - All"?
- Or just "MIDI Librarian AUv3 AppExtension"?

You might need to build the **"MIDI Librarian"** scheme (the main App container) separately.

## Quick Check

After searching the build log, if you find a path like:
```
/Users/.../Build/Products/Debug/MIDI Librarian.app
```

Copy that path and check if it exists:
```bash
ls -la "/path/you/found/MIDI Librarian.app"
```


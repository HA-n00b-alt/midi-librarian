# Adding Copy Files Build Phase for AUv3 Plugin

## Problem

The AUv3 AppExtension target is missing a "Copy Files" build phase, so the plugin doesn't auto-install after building. The VST3 target has one, but AUv3 doesn't.

## Solution: Add Copy Files Build Phase Manually

### Step 1: Open Build Phases

1. In Xcode, select your project (top item in left sidebar)
2. Select the **"MIDI Librarian AUv3 AppExtension"** target
3. Click the **"Build Phases"** tab

### Step 2: Add Copy Files Phase

1. Click the **"+"** button at the top of the Build Phases section
2. Select **"New Copy Files Phase"**
3. A new "Copy Files" phase will appear

### Step 3: Configure Copy Files Phase

1. Click the disclosure triangle to expand the "Copy Files" phase
2. Set the following:
   - **Destination**: Select **"Absolute Path"**
   - **Path**: Enter: `$(HOME)/Library/Audio/Plug-Ins/Components`
   - **Copy only when installing**: Leave **UNCHECKED** (so it copies on every build)
   - **Code Sign On Copy**: Leave **CHECKED**

### Step 4: Add the Plugin to Copy

1. Under "Copy Files", click the **"+"** button
2. Click **"Add Other..."** → **"Add Files..."**
3. Navigate to your build output folder:
   ```
   MIDI Librarian/Builds/MacOSX/build/Debug/MIDI Librarian.appex
   ```
   OR use a build variable:
   - Click **"Add Other..."** → **"Add Files..."**
   - Press `Cmd+Shift+G` to Go to Folder
   - Type: `$(BUILT_PRODUCTS_DIR)` and press Enter
   - Select: `MIDI Librarian.appex` (if it exists there)

**Alternative (using build variables):**

Since the .appex might be in a different location, you can:
1. In the Copy Files phase, click "+"
2. Look for a variable like `$(TARGET_BUILD_DIR)/MIDI Librarian.appex`
3. Or manually add the path after checking where it's built

### Step 5: Verify

After adding, the Copy Files phase should show:
- Destination: Absolute Path
- Path: $(HOME)/Library/Audio/Plug-Ins/Components
- Files: MIDI Librarian.appex (or the app bundle)

### Step 6: Test

1. Clean Build Folder (Shift+Cmd+K)
2. Build (Cmd+B)
3. Check if plugin appears in: `~/Library/Audio/Plug-Ins/Components/`

## Important Note: AUv3 Structure

For AUv3 plugins, you might need to copy the **app bundle** (not just the .appex), or create the proper structure. JUCE typically builds:
- A main app bundle that contains the .appex

Check your build output to see what structure JUCE creates. If it's just the .appex file, you may need to wrap it in an app bundle (which our install script does).

## Alternative: Use Install Script

If adding the build phase is complex, you can continue using the `install_plugin.sh` script after each build. Just run it manually after building.

## Why This Happened

JUCE's build system should have added this automatically, but it didn't. This can happen if:
- The Projucer project wasn't configured correctly
- JUCE version differences
- The project was manually modified

You may want to regenerate the Xcode project from Projucer to see if it adds it automatically.


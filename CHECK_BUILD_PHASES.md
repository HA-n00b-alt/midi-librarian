# How to Check Xcode Build Phases and Find Installation Steps

## Step 1: Check Build Phases

1. In Xcode, select your project (top item in left sidebar)
2. Select the **"MIDI Librarian AUv3 AppExtension"** target
3. Click the **"Build Phases"** tab (at the top)
4. Look for a **"Copy Files"** phase
   - If it exists, check:
     - Destination: Should be "Absolute Path" or "Products Directory"
     - Path: Should be `$(HOME)/Library/Audio/Plug-Ins/Components/`
     - Files: Should include the `.appex` or `.app` file
   - If it doesn't exist, that's why the plugin isn't auto-installing!

## Step 2: Scroll Down in Build Log

In the build log you showed me, you need to scroll down to find:

1. **Look for "Copy Files" phase execution**:
   - Search for "Copy Files" in the build log
   - This shows what files are being copied and where

2. **Look for "BUILT_PRODUCTS_DIR"**:
   - Search for "BUILT_PRODUCTS_DIR" in the build log
   - This shows where Xcode built the final products

3. **Look for paths ending in ".app" or ".appex"**:
   - Search for ".app" or ".appex" in the build log
   - These show the actual build outputs

4. **Look at the very end of the build**:
   - After all compilation, there should be linking and copying steps
   - The last few lines often show where files ended up

## Step 3: Check Available Schemes

1. Click on the scheme selector (top toolbar, next to the play/stop buttons)
2. See what schemes are listed:
   - "MIDI Librarian AUv3 AppExtension" (what you're building)
   - "MIDI Librarian" (might be the main app container)
   - Others?
3. If there's a "MIDI Librarian" scheme, try building that one too

## Step 4: Check Build Settings for INSTALL_PATH

1. Select the "MIDI Librarian AUv3 AppExtension" target
2. Go to "Build Settings" tab
3. Make sure "All" is selected (not "Basic")
4. Search for "INSTALL_PATH"
5. See what path is set (if any)

## Quick Test

After checking the above, please tell me:
1. Is there a "Copy Files" build phase? (Yes/No)
2. What schemes are available? (list them)
3. Did you scroll to the end of the build log? What's the last line?
4. What does INSTALL_PATH show in Build Settings?


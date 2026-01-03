# Fixing Projucer Configuration for AUv3

## Problem

The Projucer configuration wasn't set up correctly for AUv3. JUCE needs to generate both:
1. **App Container** (the main app bundle)
2. **App Extension** (the .appex plugin)

If only the AppExtension is generated, the plugin structure is incomplete.

## Solution: Check and Fix Projucer Settings

### Step 1: Open Projucer

1. Launch **Projucer**
2. Open your project: `MIDI Librarian/MIDI Librarian.jucer`

### Step 2: Check Plugin Formats Tab

1. Click the **"Plugin Formats"** tab (or "Exporters" → macOS → Plugin Formats)
2. Verify:
   - ✅ **AUv3** is checked (enabled)
   - The other formats (VST3, etc.) can be enabled as needed

### Step 3: Check Exporters Tab (Important!)

1. Click the **"Exporters"** tab in the left sidebar
2. Select **"Xcode (macOS)"**
3. Look for settings related to:
   - **Target types** or **Build configurations**
   - **Plugin formats to export**
   - Make sure AUv3 is selected

### Step 4: Check if Standalone Needs to be Enabled

For AUv3 plugins, some JUCE versions require:
- ✅ **AUv3** enabled (you have this)
- Sometimes also enable **Standalone** to get the App container

However, this varies by JUCE version. Modern JUCE should generate the App container automatically when AUv3 is enabled.

### Step 5: Regenerate Xcode Project

1. In Projucer, click **"Save and Open in IDE"**
   - Or: File → Save Project
   - Then manually open the .xcodeproj in Xcode

2. This will regenerate the Xcode project with the correct structure

### Step 6: Verify in Xcode

After regenerating, check the scheme selector in Xcode. You should see:
- "MIDI Librarian" (or similar - the main app container)
- "MIDI Librarian AUv3 AppExtension" (the plugin extension)

If you see both, the configuration is correct!

## Alternative: Check JUCE Version

Some older JUCE versions handle AUv3 differently. If the above doesn't work:

1. Check your JUCE version
2. Update to the latest JUCE if possible
3. Modern JUCE (7.0+) should handle AUv3 App container generation automatically

## What to Look For in Projucer

In the Projucer interface, look for:

### Plugin Formats Tab:
- ✅ AUv3 checkbox (should be checked)
- Other formats as needed (VST3, etc.)

### Exporters → Xcode (macOS):
- Check if there are any settings about "target types" or "build targets"
- Some versions have options to explicitly enable App container generation

### Advanced Settings:
- Check if there are any AUv3-specific settings
- Some versions have options for "Generate App Container" or similar

## After Fixing

1. **Regenerate Xcode project** from Projucer
2. **Clean build folder** in Xcode (Shift+Cmd+K)
3. **Rebuild** (Cmd+B)
4. Check if both schemes appear (App and AppExtension)
5. Build the App scheme first, then the AppExtension
6. The plugin should now install correctly

## Note

If after regenerating you still only see the AppExtension scheme, this might be normal for your JUCE version. In that case:
- The manual installation script should work
- Or you may need to add the Copy Files build phase manually
- Or check JUCE documentation for your specific version


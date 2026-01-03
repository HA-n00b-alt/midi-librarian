# AUv3 Scheme Explanation

## What You're Seeing

**"MIDI Librarian AUv3 AppExtension"** - This is **CORRECT** and what you should use!

## Understanding AUv3 Schemes

For AUv3 plugins, Projucer generates **two schemes**:

1. **Main App Scheme** (usually not needed for plugin development)
2. **AUv3 AppExtension Scheme** ← **This is what you need!**

The **AppExtension** is the actual AUv3 plugin that Logic Pro loads.

## Which Scheme to Use

### ✅ Use: "MIDI Librarian AUv3 AppExtension"

This is the correct scheme for:
- Building the AUv3 plugin
- Testing in Logic Pro
- Development and debugging

### ❌ Don't Use: Main App Scheme

The main app scheme is for standalone apps, not plugins.

## Building with AppExtension Scheme

### Steps:

1. **Select Scheme**
   - In toolbar: Click scheme dropdown
   - Select: **"MIDI Librarian AUv3 AppExtension"**

2. **Select Platform**
   - Next to scheme: Select **"My Mac"**

3. **Build**
   - Click Build button (🔨) or press `Cmd+B`
   - Wait for build to complete

4. **Result**
   - Plugin installs to: `~/Library/Audio/Plug-Ins/Components/MIDI Librarian.component`
   - This is the AUv3 plugin Logic Pro will use

## Why Two Schemes?

AUv3 plugins are structured as:
- **App Container**: Wrapper app (not used in DAWs)
- **App Extension**: The actual plugin (what DAWs load)

When you build the AppExtension scheme, it:
1. Builds the plugin code
2. Packages it as an AUv3 extension
3. Installs it to the Components folder
4. Makes it available to Logic Pro

## Visual Guide

### Scheme Selector Should Show:

```
[MIDI Librarian AUv3 AppExtension ▼] [My Mac ▼] [▶] [🔨]
```

Or if you have multiple schemes:

```
[MIDI Librarian AUv3 AppExtension ▼]
  ├─ MIDI Librarian AUv3 AppExtension  ← Use this!
  ├─ MIDI Librarian (if exists)
  └─ MIDI Librarian VST3 (if VST3 enabled)
```

## Building the Plugin

### Quick Steps:

1. ✅ Scheme: **MIDI Librarian AUv3 AppExtension**
2. ✅ Platform: **My Mac**
3. ✅ Build: Press `Cmd+B` or click 🔨
4. ✅ Wait for "Build Succeeded"
5. ✅ Test in Logic Pro

## Testing in Logic Pro

After successful build:

1. **Launch Logic Pro**
2. **Create MIDI Track**
3. **Insert Plugin**
   - Track inspector → MIDI Effects
   - Select: **MIDI Librarian**
4. **Plugin Opens**
   - Should see your plugin UI
   - Test functionality

## Troubleshooting

### "Build Failed" Error

**Check**:
1. All source files added in Projucer?
2. JUCE modules enabled?
3. C++17 standard set?
4. Check error messages in Xcode

### Plugin Not Appearing in Logic Pro

**Check**:
1. Build succeeded (green checkmark)?
2. Plugin installed: `ls ~/Library/Audio/Plug-Ins/Components/ | grep MIDI`
3. Restart Logic Pro
4. Check Logic Pro → Preferences → Plug-in Manager

### Wrong Scheme Selected

**Problem**: Building wrong scheme

**Solution**:
- Always use **"MIDI Librarian AUv3 AppExtension"**
- Not the main app scheme

## Summary

- ✅ **"MIDI Librarian AUv3 AppExtension"** is the correct scheme
- ✅ This is what you should build
- ✅ This creates the AUv3 plugin for Logic Pro
- ✅ Build with `Cmd+B` after selecting this scheme

You're all set! Select that scheme and build. 🚀


# Adding App Icon - Quick Instructions

## Where to Place the Icon File

Place your 1024x1024 PNG icon file in the project directory:

```
midi-librarian/
└── MIDI Librarian/
    └── icon.png (or MIDI_Librarian_Icon.png)
```

**Recommended location**: `MIDI Librarian/icon.png`

## How to Add Icon in Projucer

Projucer doesn't have a direct icon setting in all versions. Use one of these methods:

### Method 1: Add to Resources (If Available)

1. **Open Projucer**
2. **Open project**: `MIDI Librarian/MIDI Librarian.jucer`
3. **Look for Resources folder** in the file tree
4. **Right-click Resources** → Add Existing Files
5. **Select your icon.png file**
6. **Save project**
7. **Regenerate Xcode project**: "Save and Open in IDE"

### Method 2: Add in Xcode (Recommended)

Since Projucer may not have icon support, add it directly in Xcode:

1. **Place icon file** in `MIDI Librarian/icon.png`
2. **Open Xcode project**
3. **Select your project** (top item in navigator)
4. **Select target**: "MIDI Librarian" (the App container target)
5. **Go to "General" tab**
6. **Find "App Icons and Launch Screen"** section
7. **Drag your icon.png file** into the App Icon slot (1024x1024)
8. **Xcode will automatically create the .icns file**
9. **Build** (Cmd+B)

**Important**: Make sure you add the icon to the **App container target** (not just the AppExtension target).

## Quick Steps Summary

1. ✅ Place `icon.png` (1024x1024) in `MIDI Librarian/` folder
2. ✅ Open Xcode
3. ✅ Select project → "MIDI Librarian" target → General tab
4. ✅ Drag icon.png to "App Icons" section
5. ✅ Build and test

The icon will appear in Finder when the app is built!


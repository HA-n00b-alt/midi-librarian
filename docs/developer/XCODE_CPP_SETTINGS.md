# Finding C++ Settings in Xcode

## The Issue

You see "C Language Dialect" but not "C++ Language Dialect" in Xcode build settings.

## Where to Find C++ Settings

### Method 1: Search in Build Settings

1. **Open Build Settings**
   - Click project name in left sidebar
   - Select the project (not target)
   - Click "Build Settings" tab

2. **Search for C++**
   - In the search box at top right, type: `C++`
   - This filters to show only C++ related settings

3. **Look for These Settings**:
   - **C++ Language Dialect** (might be called "C++ Language Standard" or "C++ Standard")
   - **C++ Standard Library** (libc++)

### Method 2: Show All Settings

1. **In Build Settings tab**
   - Make sure "All" is selected (not "Basic")
   - Click "All" button at top

2. **Scroll to "Apple Clang - Language - C++" section**
   - Look for: **C++ Language Dialect**
   - Or: **C++ Language Standard**

### Method 3: Check Target Settings

Sometimes settings are at the **target** level, not project level:

1. **Select Target**
   - Click project name in left sidebar
   - Under "TARGETS", select **"MIDI Librarian AUv3 AppExtension"**
   - Click "Build Settings" tab
   - Search for "C++"

## Setting Names in Xcode

Xcode might show these names:
- **C++ Language Dialect** ← Most common
- **C++ Language Standard** ← Alternative name
- **C++ Standard** ← Short name
- **C++ Dialect** ← Another variant

All refer to the same setting!

## What to Set

### C++ Language Dialect
- **Value**: `C++17` or `GNU++17`
- **Not**: `C++14`, `C++11`, or `Default`

### C++ Standard Library
- **Value**: `libc++` (LLVM C++ standard library)
- **Not**: `libstdc++`

## Visual Guide

### In Build Settings (All Settings View)

```
┌─────────────────────────────────────────────────┐
│ Build Settings                                  │
│ [All] [Basic] [Customized]                      │
│                                                 │
│ Search: [C++                    ]              │
│                                                 │
│ Apple Clang - Language - C++                    │
│ ├─ C++ Language Dialect: [C++17 ▼]             │ ← This one!
│ ├─ C++ Standard Library: [libc++ ▼]            │
│ └─ ...                                         │
└─────────────────────────────────────────────────┘
```

## If You Still Can't Find It

### Check Projucer Settings

The C++ standard might be set in Projucer:

1. **Open Projucer**
2. **Open your `.jucer` file**
3. **Go to "Advanced Settings" tab**
4. **Check "C++ Language Standard"**
   - Should be: **C++17**
5. **Save project**
6. **Regenerate Xcode project**
   - File → Save Project
   - This updates Xcode project with correct settings

### Alternative: Set via Build Settings Search

1. **In Xcode Build Settings**
2. **Type in search box**: `std`
3. **Look for**: "C++ Language Dialect" or "C++ Standard"
4. **Double-click value** to change it

## Quick Fix: Set in Projucer

**Easiest method** - Set it in Projucer and regenerate:

1. **Open Projucer**
2. **Open `MIDI Librarian.jucer`**
3. **Go to "Advanced Settings" tab**
4. **Find "C++ Language Standard"**
5. **Set to**: `C++17` (or `GNU++17`)
6. **Save Project** (File → Save Project)
7. **Reopen Xcode project**

This ensures the setting is correct in the generated Xcode project.

## Verify Setting is Correct

After setting, verify:

1. **In Xcode Build Settings**
2. **Search for**: `C++`
3. **Check value shows**: `C++17` or `GNU++17`
4. **Not**: `Default`, `C++14`, or `C++11`

## Troubleshooting

### Setting Shows "Default"

**Problem**: C++ Language Dialect shows "Default"

**Solution**:
1. Double-click the value
2. Select "C++17" from dropdown
3. Or set in Projucer and regenerate

### Setting Not Visible

**Problem**: Can't find C++ settings at all

**Solution**:
1. Make sure "All" is selected (not "Basic")
2. Use search box: type `C++`
3. Check both Project and Target settings
4. Set in Projucer and regenerate project

### Build Still Uses Wrong Standard

**Problem**: Changed setting but build still fails

**Solution**:
1. Clean build folder: Product → Clean Build Folder (Shift+Cmd+K)
2. Set in Projucer and regenerate
3. Rebuild: Product → Build (Cmd+B)

## Summary

- **Look for**: "C++ Language Dialect" or "C++ Language Standard"
- **Set to**: `C++17` or `GNU++17`
- **Location**: Build Settings → Search "C++" → Apple Clang - Language - C++
- **Easiest**: Set in Projucer → Advanced Settings → C++ Language Standard → C++17
- **Then**: Save project in Projucer to regenerate Xcode project

If you still can't find it, set it in Projucer's Advanced Settings tab - that's the most reliable method!


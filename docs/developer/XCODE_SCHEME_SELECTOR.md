# Finding the Scheme Selector in Xcode

## The Scheme Selector Location

The scheme selector appears in the **toolbar** at the top of the Xcode window. If you don't see it, the toolbar might be hidden.

## Show the Toolbar

### Method 1: Menu
- **View → Show Toolbar** (or press `Cmd+Option+T`)

### Method 2: Right-click
- Right-click in the top area
- Select "Show Toolbar"

## After Showing Toolbar

You should see something like this at the top:

```
[Stop] [Scheme Selector ▼] [Platform Selector ▼] [Run/Stop Button]
```

Or if collapsed:
```
[▶] [MIDI Librarian - AU ▼] [My Mac ▼] [▶]
```

## Finding the Scheme Selector

### Location in Toolbar

The scheme selector is usually on the **left side** of the toolbar, next to the Stop button.

It looks like:
```
[MIDI Librarian - AU ▼]
```

Click the dropdown arrow (▼) to see available schemes.

## Available Schemes

After opening the project, you should see schemes like:
- **MIDI Librarian - AU** (for AUv3 plugin)
- **MIDI Librarian - VST3** (if VST3 is enabled)
- **MIDI Librarian - All** (builds all formats)

## If Scheme Selector is Missing

### Check 1: Is Project Loaded?

Look at the left sidebar (Project Navigator):
- You should see the project name at the top
- Source files should be visible
- If empty or shows errors, project didn't load correctly

### Check 2: Is Toolbar Visible?

- View → Show Toolbar
- Or: `Cmd+Option+T`

### Check 3: Select Scheme Manually

1. **Product → Scheme → Manage Schemes...**
2. You should see list of schemes
3. Check the box next to schemes you want visible
4. Click "Close"

### Check 4: Check Scheme Location

Schemes might be in:
- **xcshareddata/xcschemes/** (shared, committed to git)
- **xcuserdata/*/xcschemes/** (user-specific, not committed)

If schemes are missing, regenerate project in Projucer.

## Platform Selector

Next to the scheme selector, you should see platform selector:

```
[My Mac ▼]
```

Options:
- **My Mac** (current Mac)
- **Any Mac (Apple Silicon, Intel)** (universal binary)
- **Any Mac (Apple Silicon)** (Apple Silicon only)
- **Any Mac (Intel)** (Intel only)

## Complete Toolbar Layout

When everything is visible, toolbar looks like:

```
[Stop] [MIDI Librarian - AU ▼] [My Mac ▼] [▶ Run] [⏸ Stop] [Build]
```

From left to right:
1. **Stop button** (if running)
2. **Scheme selector** (what to build)
3. **Platform selector** (where to run)
4. **Run button** (▶)
5. **Stop button** (⏸)
6. **Build button** (hammer icon)

## Troubleshooting

### No Schemes Available

**Problem**: Scheme dropdown is empty

**Solution**:
1. Go back to Projucer
2. Verify plugin formats are enabled (AUv3, VST3)
3. Save project
4. Regenerate Xcode project (File → Save Project)
5. Reopen in Xcode

### Toolbar Still Not Visible

**Problem**: Toolbar won't show

**Solution**:
1. View → Show Toolbar
2. Check if window is in fullscreen (exit fullscreen: `Ctrl+Cmd+F`)
3. Try: Window → Zoom (to reset window size)
4. Restart Xcode

### Wrong Scheme Selected

**Problem**: Different scheme is selected

**Solution**:
1. Click scheme dropdown
2. Select "MIDI Librarian - AU"
3. This is the scheme for Logic Pro (AUv3)

### Can't Find Platform Selector

**Problem**: Platform selector not visible

**Solution**:
1. It's right next to scheme selector
2. If missing, check Product → Destination
3. Or: Product → Scheme → Edit Scheme → Destination

## Quick Reference

### Keyboard Shortcuts
- **Show/Hide Toolbar**: `Cmd+Option+T`
- **Show/Hide Navigator**: `Cmd+0`
- **Show/Hide Utilities**: `Cmd+Option+0`
- **Build**: `Cmd+B`
- **Run**: `Cmd+R`

### Menu Locations
- **View → Show Toolbar**
- **Product → Scheme → [Scheme Name]**
- **Product → Destination → [Platform]**

## Visual Guide

### Normal Xcode Window (Toolbar Visible)

```
┌─────────────────────────────────────────────────────────┐
│ [Stop] [MIDI Librarian - AU ▼] [My Mac ▼] [▶] [🔨]     │ ← Toolbar
├─────────────────────────────────────────────────────────┤
│                                                         │
│  [Project Navigator]    [Editor Area]    [Utilities]   │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### If Toolbar is Hidden

```
┌─────────────────────────────────────────────────────────┐
│                                                         │
│  [Project Navigator]    [Editor Area]    [Utilities]   │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

**Solution**: View → Show Toolbar

## Next Steps

Once you see the scheme selector:

1. ✅ Select scheme: **MIDI Librarian - AU**
2. ✅ Select platform: **My Mac**
3. ✅ Click Build button (🔨) or press `Cmd+B`
4. ✅ Wait for build to complete
5. ✅ Check for errors (red X) or success (green checkmark)

## Summary

- **Toolbar might be hidden** → View → Show Toolbar
- **Scheme selector** is in the toolbar (left side)
- **Select**: "MIDI Librarian - AU" scheme
- **Select**: "My Mac" platform
- **Build**: Click hammer icon or `Cmd+B`

If you still can't find it, describe what you see in the Xcode window and I can help further!


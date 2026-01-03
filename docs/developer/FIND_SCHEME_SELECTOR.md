# How to Find the Scheme Selector in Xcode

## Location

The scheme selector is in the **toolbar at the top** of the Xcode window.

## Step-by-Step

1. **Make sure the toolbar is visible**
   - If you don't see a toolbar at the top: View → Show Toolbar (or press `Cmd+Option+T`)
   - The toolbar appears at the very top of the Xcode window

2. **Look for the scheme dropdown**
   - It's on the **left side** of the toolbar
   - You'll see something like:
     ```
     [▶] [⏸] [🛑] [MIDI Librarian AUv3 AppExtension ▼] [My Mac ▼] [▶] [🔨]
     ```
   - The scheme selector is the dropdown that says something like:
     - "MIDI Librarian AUv3 AppExtension"
     - Or "MIDI Librarian"
     - Or just "MIDI Librarian"

3. **Click the dropdown**
   - Click on the scheme name (the part that says "MIDI Librarian...")
   - A menu will drop down showing all available schemes

## Visual Guide

The toolbar layout looks like this:

```
[▶ Run] [⏸] [🛑]  [MIDI Librarian AUv3 AppExtension ▼]  [My Mac ▼]  [▶]  [🔨 Build]
      ^                                          ^            ^
   Run button                            Scheme selector   Platform
```

The **Scheme Selector** is the dropdown that shows the current scheme name.

## What to Look For

When you click the scheme dropdown, you should see a list like:

- MIDI Librarian AUv3 AppExtension ← (what you're currently using)
- MIDI Librarian (might be the main app container)
- MIDI Librarian VST3 (if VST3 is enabled)
- Other schemes...

## If You Don't See the Toolbar

1. Go to: **View → Show Toolbar** (or press `Cmd+Option+T`)
2. The toolbar should appear at the top

## If You Still Don't See It

The scheme selector might be hidden if the window is too narrow. Try:
- Making the Xcode window wider
- Or go to: **View → Show Toolbar** again

## Quick Keyboard Shortcut

- You can also access schemes via: **Product → Scheme → [Scheme Name]**
- This shows the same list of available schemes


#!/bin/bash
# Script to find the built MIDI Librarian plugin

echo "=== Searching for MIDI Librarian plugin build outputs ==="
echo ""

echo "1. Local build folder:"
find "/Users/andreadelmiglio/Documents/Git local/midi-librarian/MIDI Librarian/Builds/MacOSX/build" -name "*.app" -o -name "*.appex" 2>/dev/null | head -10
echo ""

echo "2. DerivedData Products:"
find ~/Library/Developer/Xcode/DerivedData/MIDI_Librarian-*/Build/Products -name "*.app" -o -name "*.appex" 2>/dev/null 2>&1 | head -10
echo ""

echo "3. All DerivedData (recursive):"
find ~/Library/Developer/Xcode/DerivedData -name "*MIDI*Librarian*.app" -type d 2>/dev/null | head -10
echo ""

echo "4. Components folder (installed plugins):"
ls -la ~/Library/Audio/Plug-Ins/Components/ 2>/dev/null | grep -i midi
echo ""

echo "5. Recent build outputs (by modification time):"
find "/Users/andreadelmiglio/Documents/Git local/midi-librarian/MIDI Librarian/Builds/MacOSX/build" -type d \( -name "*.app" -o -name "*.appex" \) -exec ls -ld {} \; 2>/dev/null | head -5
echo ""

echo "=== To check Xcode build log ==="
echo "1. Open Xcode"
echo "2. Press ⌘9 (Report Navigator)"
echo "3. Click your most recent build"
echo "4. Search for: BUILT_PRODUCTS_DIR or Copying"
echo ""


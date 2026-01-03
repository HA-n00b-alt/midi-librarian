#!/bin/bash

# JUCE Setup Helper Script
# This script helps set up JUCE and Projucer for MIDI Librarian development

set -e

echo "=== MIDI Librarian - JUCE Setup ==="
echo ""

# Check if JUCE is installed
JUCE_PATH="/Users/andreadelmiglio/Library/CloudStorage/Dropbox-Family/Andrea Del Miglio/Documents/Delman/Git local/JUCE"
if [ ! -d "$JUCE_PATH" ]; then
    echo "❌ JUCE not found at $JUCE_PATH"
    echo ""
    echo "Please download JUCE from: https://juce.com/get-juce"
    echo "Extract to: $JUCE_PATH"
    echo ""
    read -p "Press Enter after you've installed JUCE, or Ctrl+C to cancel..."
fi

# Check if JUCE exists now
if [ ! -d "$JUCE_PATH" ]; then
    echo "❌ JUCE still not found. Exiting."
    exit 1
fi

echo "✅ JUCE found at: $JUCE_PATH"
echo ""

# Check for Projucer
PROJUCER_PATH="$JUCE_PATH/extras/Projucer/Builds/MacOSX"
if [ ! -d "$PROJUCER_PATH" ]; then
    echo "⚠️  Projucer source not found. You may need to build it."
    echo "   Path: $PROJUCER_PATH"
    echo ""
    echo "To build Projucer:"
    echo "  cd $PROJUCER_PATH"
    echo "  xcodebuild -project Projucer.xcodeproj -scheme Projucer -configuration Release"
    echo ""
    read -p "Press Enter to continue anyway, or Ctrl+C to cancel..."
else
    echo "✅ Projucer found at: $PROJUCER_PATH"
fi

# Check if .jucer file exists
if [ -f "MIDI Librarian.jucer" ]; then
    echo "✅ Project file found: MIDI Librarian.jucer"
    echo ""
    echo "To open in Projucer:"
    echo "  open MIDI Librarian.jucer"
    echo ""
    echo "Or build Projucer and open it, then File → Open → MIDI Librarian.jucer"
else
    echo "⚠️  Project file not found: MIDI Librarian.jucer"
    echo ""
    echo "You need to create the project file in Projucer:"
    echo "  1. Open Projucer"
    echo "  2. File → New Project → Audio Plug-In"
    echo "  3. Configure as MIDI Effect Plugin"
    echo "  4. Add all source files from Source/ directory"
    echo "  5. Save as MIDI Librarian.jucer"
    echo ""
    echo "See docs/developer/SETUP_JUCE.md for detailed instructions"
fi

echo ""
echo "=== Setup Complete ==="
echo ""
echo "Next steps:"
echo "  1. Open Projucer"
echo "  2. Open/create MIDI Librarian.jucer"
echo "  3. Generate Xcode project"
echo "  4. Build in Xcode"
echo "  5. Test in Logic Pro"
echo ""
echo "For detailed instructions, see: docs/developer/SETUP_JUCE.md"


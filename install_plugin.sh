#!/bin/bash
# Script to install MIDI Librarian AUv3 plugin manually

APPEX_PATH="/Users/andreadelmiglio/Documents/Git local/midi-librarian/MIDI Librarian/Builds/MacOSX/build/Debug/MIDI Librarian.appex"
INSTALL_DIR="$HOME/Library/Audio/Plug-Ins/Components"

if [ ! -d "$APPEX_PATH" ]; then
    echo "Error: .appex file not found at: $APPEX_PATH"
    echo "Please build the project in Xcode first."
    exit 1
fi

echo "Installing MIDI Librarian AUv3 plugin..."
echo ""

# Remove old installation
if [ -d "$INSTALL_DIR/MIDI Librarian.app" ]; then
    echo "Removing old installation..."
    rm -rf "$INSTALL_DIR/MIDI Librarian.app"
fi

if [ -d "$INSTALL_DIR/MIDI Librarian.component" ]; then
    echo "Removing old component..."
    rm -rf "$INSTALL_DIR/MIDI Librarian.component"
fi

# Create app bundle structure (AUv3 style)
echo "Creating app bundle..."
mkdir -p "$INSTALL_DIR/MIDI Librarian.app/Contents/PlugIns"
cp -R "$APPEX_PATH" "$INSTALL_DIR/MIDI Librarian.app/Contents/PlugIns/"

# Create minimal Info.plist for app bundle
cat > "$INSTALL_DIR/MIDI Librarian.app/Contents/Info.plist" << 'EOF'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleDevelopmentRegion</key>
    <string>en</string>
    <key>CFBundleExecutable</key>
    <string>MIDI Librarian</string>
    <key>CFBundleIdentifier</key>
    <string>com.delman.MIDILibrarian</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>MIDI Librarian</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>1.0.0</string>
    <key>CFBundleVersion</key>
    <string>1.0.0</string>
    <key>LSMinimumSystemVersion</key>
    <string>10.13</string>
</dict>
</plist>
EOF

# Sign the plugin (ad-hoc signing for local use)
echo "Signing plugin..."
codesign --force --deep --sign - "$INSTALL_DIR/MIDI Librarian.app" 2>&1

echo ""
echo "Installation complete!"
echo "Plugin installed to: $INSTALL_DIR/MIDI Librarian.app"
echo ""
echo "Next steps:"
echo "1. Restart Logic Pro completely"
echo "2. Check Logic Pro → Preferences → Plug-in Manager"
echo "3. If plugin appears but is not validated, click 'Reset & Rescan Selection'"
echo "4. Clear Audio Unit cache if needed:"
echo "   rm ~/Library/Caches/AudioUnitCache/com.apple.audiounits.cache"


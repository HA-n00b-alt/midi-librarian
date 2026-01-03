# Fixing Code Signing Errors

## Quick Fix for Development

When you see **"Command CodeSign failed with a nonzero exit code"**, follow these steps:

### Step 1: Open Signing & Capabilities

1. In Xcode, click on the **project name** in the left sidebar (top item)
2. Select the **project** (blue icon, not the target)
3. Click on the **"MIDI Librarian AUv3 AppExtension"** target in the TARGETS list
4. Click the **"Signing & Capabilities"** tab

### Step 2: Enable Automatic Signing

1. **Check "Automatically manage signing"** checkbox
2. **Team**: Select your Apple ID (or "Sign to Run Locally" if available)
   - If you don't have a developer account, Xcode will use "Sign to Run Locally" automatically
3. **Bundle Identifier**: Should be something like `com.yourcompany.MIDILibrarian.AUv3`

### Step 3: For Development (No Certificate Needed)

If you see errors or don't have a developer account:

1. **Uncheck "Automatically manage signing"** (temporarily)
2. **Code Signing Identity**: Select **"Sign to Run Locally"**
   - This allows the plugin to run on your Mac without a certificate
3. **Provisioning Profile**: Leave empty or set to "None"

### Step 4: Clean and Rebuild

1. **Clean Build Folder**: Product → Clean Build Folder (Shift+Cmd+K)
2. **Build**: Product → Build (Cmd+B)

## Alternative: Disable Code Signing (Development Only)

⚠️ **Warning**: This is for development only. The plugin won't work in Logic Pro without proper signing.

1. Go to **Build Settings** tab
2. Search for **"Code Signing"**
3. Set **"Code Signing Identity"** to **"Don't Code Sign"**
4. Clean and rebuild

**Note**: This may cause issues with Logic Pro. Use "Sign to Run Locally" instead if possible.

## For Distribution

When you're ready to distribute:

1. Get a **Developer ID Application** certificate from Apple Developer Program
2. Set **Code Signing Identity** to your Developer ID certificate
3. Enable **"Automatically manage signing"** with your team
4. Build in **Release** configuration

## Troubleshooting

### Error: "No signing certificate found"

**Solution**: Use "Sign to Run Locally" for development (see Step 3 above)

### Error: "Bundle identifier is already in use"

**Solution**: Change the bundle identifier in Projucer:
1. Open Projucer
2. Project Information tab
3. Change Bundle Identifier to something unique (e.g., `com.yourname.MIDILibrarian`)
4. Save and regenerate Xcode project

### Error: "Provisioning profile not found"

**Solution**: 
- For development: Use "Sign to Run Locally" (no provisioning profile needed)
- For distribution: Create provisioning profile in Apple Developer portal

### Plugin Still Won't Load in Logic Pro

**Check**:
1. Plugin is properly signed (even "Sign to Run Locally" should work)
2. Plugin is installed to: `~/Library/Audio/Plug-Ins/Components/`
3. Logic Pro is restarted after building
4. Check Logic Pro → Preferences → Plug-in Manager for errors

## Summary

**For Development**:
- ✅ Use "Sign to Run Locally" (no certificate needed)
- ✅ Or enable "Automatically manage signing" with your Apple ID

**For Distribution**:
- ✅ Get Developer ID Application certificate
- ✅ Set proper code signing identity
- ✅ Enable automatic signing with your team


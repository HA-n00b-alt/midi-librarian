# Fixing Build Errors in Xcode

## When Xcode Stops Building

If Xcode stops the build with an error:

1. **Look at the error message** (usually in red)
   - It will tell you what went wrong
   - Common issues: missing files, compilation errors, code signing issues

2. **Check the build log**
   - Open Report Navigator (⌘9)
   - Click the failed build
   - Scroll to the END
   - The last error message is usually the actual problem

3. **Common Build Errors**:

### Code Signing Errors
- **Error**: "CodeSign failed" or "signing certificate not found"
- **Fix**: 
  - Select target → Signing & Capabilities
  - Set Code Signing Identity to "Sign to Run Locally"
  - Or enable "Automatically manage signing"

### Missing Files
- **Error**: "File not found" or "No such file or directory"
- **Fix**: 
  - Check if source files are added in Projucer
  - Regenerate Xcode project from Projucer
  - Check file paths are correct

### Compilation Errors
- **Error**: Syntax errors, undefined symbols, etc.
- **Fix**: 
  - Read the error message - it tells you which file and line
  - Fix the code issue
  - Common: missing includes, typos, wrong types

### Warnings Treated as Errors
- **Error**: Warning appears but build fails
- **Fix**: 
  - Check Build Settings → "Treat Warnings as Errors"
  - Turn it off, or fix the warning

## Getting Help

When asking for help with build errors, provide:
1. The exact error message (copy/paste)
2. Which target/scheme you're building
3. The last few lines of the build log
4. Any relevant build settings


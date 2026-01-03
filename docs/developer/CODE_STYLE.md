# Code Style Guide

This document defines the coding standards for the MIDI Librarian project.

## General Principles

1. **Clarity over Cleverness**: Code should be easy to read and understand
2. **Consistency**: Follow existing patterns in the codebase
3. **Modern C++**: Use C++17 features where helpful, but prioritize clarity
4. **JUCE Conventions**: Follow JUCE's coding style where applicable

## Naming Conventions

### Classes
- **PascalCase**: `PatchManager`, `MidiManager`, `ValhallaLookAndFeel`
- **Descriptive**: Names should clearly indicate purpose
- **Suffixes**: Use appropriate suffixes (`Manager`, `Panel`, `Item`, etc.)

### Functions and Methods
- **camelCase**: `renamePatch()`, `sendProgramChange()`, `getPatchName()`
- **Verbs**: Function names should be verbs (actions)
- **Getters**: Prefix with `get` (e.g., `getPatchName()`)
- **Setters**: Prefix with `set` (e.g., `setPatchName()`)
- **Predicates**: Prefix with `is` or `has` (e.g., `isPortOpen()`, `hasTemplate()`)

### Variables
- **camelCase**: `patchName`, `midiChannel`, `currentPortName`
- **Descriptive**: Avoid abbreviations unless widely understood
- **Member Variables**: No prefix (unlike some JUCE code)
- **Constants**: `UPPER_SNAKE_CASE` for compile-time constants

### Files
- **Match Class Name**: `PatchManager.h` contains `class PatchManager`
- **One Class Per File**: Each class gets its own .h/.cpp pair
- **Directory Structure**: Group related files in subdirectories

## File Organization

### Header Files (.h)

```cpp
#pragma once

#include <JuceHeader.h>
#include "../OtherHeader.h"  // Project headers

/**
 * Brief class description.
 * 
 * Longer description explaining purpose and usage.
 */
class MyClass : public juce::Component
{
public:
    MyClass();
    ~MyClass() override;
    
    // Public methods
    
private:
    // Private members
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyClass)
};
```

### Include Order

1. Corresponding header (in .cpp files)
2. JUCE headers (`<JuceHeader.h>`)
3. Project headers (Model → View → Controller order)
4. Standard library headers

### Forward Declarations

Use forward declarations in headers when possible:
```cpp
class PatchManager;  // Forward declare
// Instead of: #include "PatchManager.h"
```

## Formatting

### Indentation
- **4 spaces** (no tabs)
- Consistent indentation throughout

### Braces
- **Opening brace on same line** for functions, classes
- **Opening brace on new line** for namespaces
- **Always use braces** even for single-line if/for

```cpp
// Good
void myFunction() {
    if (condition) {
        doSomething();
    }
}

// Also acceptable (JUCE style)
void myFunction()
{
    if (condition)
    {
        doSomething();
    }
}
```

### Line Length
- **Soft limit**: 100 characters
- **Hard limit**: 120 characters
- Break long lines at logical points

### Spacing
- **One blank line** between methods
- **Two blank lines** between sections (public/private)
- **No trailing whitespace**

## Comments

### Documentation Comments
Use Doxygen-style comments for public APIs:

```cpp
/**
 * Sends a MIDI Program Change message.
 * 
 * @param programNumber Program number (0-127)
 * @return Result indicating success or failure
 * @note This method is thread-safe
 */
juce::Result sendProgramChange(int programNumber);
```

### Inline Comments
- Explain **why**, not **what**
- Use for non-obvious logic
- Keep comments up-to-date with code

```cpp
// Good: Explains why
// Convert 1-16 to 0-15 for MIDI protocol
midiChannel = channel - 1;

// Bad: States the obvious
// Subtract 1 from channel
midiChannel = channel - 1;
```

## C++ Features

### Modern C++17 Usage

**Use**:
- `auto` for iterators and long type names
- `constexpr` for compile-time constants
- `noexcept` for functions that don't throw
- `override` for virtual function overrides
- Range-based for loops
- Smart pointers (`std::unique_ptr`, `std::shared_ptr`)

**Avoid**:
- Raw `new`/`delete` (use smart pointers)
- C-style casts (use `static_cast`, etc.)
- `using namespace` in headers

### Const Correctness

- Mark methods `const` if they don't modify state
- Use `const` references for parameters
- Prefer `const` by default

```cpp
// Good
const PatchData& getPatch(int index) const;
void setPatch(int index, const PatchData& patch);

// Bad
PatchData& getPatch(int index);  // Should be const
void setPatch(int index, PatchData patch);  // Unnecessary copy
```

### RAII

Always use RAII for resource management:

```cpp
// Good
std::unique_ptr<juce::MidiOutput> midiOutput;
juce::ScopedLock sl(lock);

// Bad
juce::MidiOutput* midiOutput;  // Manual memory management
```

## JUCE-Specific

### Component Lifecycle
- Always call parent constructors
- Use `addAndMakeVisible()` for child components
- Remove listeners in destructor
- Use `JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR`

### Thread Safety
- Use `CriticalSection` for shared data
- Use `MessageManager::callAsync()` for UI updates from other threads
- Never access UI from audio thread

### Memory Management
- Use `OwnedArray` for arrays of components
- Use `std::unique_ptr` for single objects
- Avoid raw pointers

## Error Handling

### Result-Based API
Return `juce::Result` for operations that can fail:

```cpp
juce::Result sendProgramChange(int programNumber);
```

### Validation
Validate inputs at API boundaries:

```cpp
if (programNumber < 0 || programNumber > 127)
{
    return juce::Result::fail("Program number must be 0-127");
}
```

### Logging
Use JUCE's logger for errors:

```cpp
juce::Logger::writeToLog("Failed to open MIDI port: " + errorMessage);
```

## Examples

### Good Code

```cpp
class PatchManager : public juce::ChangeBroadcaster
{
public:
    PatchManager();
    ~PatchManager() override = default;
    
    void renamePatch(int slotIndex, const juce::String& newName);
    const PatchBank& getPatchBank() const noexcept { return patchBank; }
    
private:
    PatchBank patchBank;
    void saveAll();
};
```

### Bad Code

```cpp
class patch_manager  // Wrong naming
{
public:
    patch_manager() {}  // Missing override, no initialization
    ~patch_manager() {}  // Should be = default
    
    void RenamePatch(int slot, String name);  // Wrong naming, missing const ref
    PatchBank& GetPatchBank() { return patchBank; }  // Should be const
    
private:
    PatchBank patchBank;  // OK, but missing documentation
};
```

## Code Review Checklist

Before submitting code, ensure:

- [ ] Follows naming conventions
- [ ] Proper const correctness
- [ ] No memory leaks (use smart pointers)
- [ ] Thread-safe (if accessing shared data)
- [ ] Error handling for failure cases
- [ ] Comments for non-obvious logic
- [ ] No compiler warnings
- [ ] Matches existing code style

## Tools

### Formatting
- Use Xcode's "Re-indent" (Ctrl+I)
- Consider clang-format (future)

### Linting
- Xcode's built-in analyzer
- Enable all warnings
- Fix warnings before committing

## Questions?

If unsure about style, look at existing code in the project for examples, or ask in code review.


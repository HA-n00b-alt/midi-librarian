# ADR-001: MVC Architecture Pattern

**Status**: Accepted  
**Date**: 2024  
**Deciders**: Development Team

## Context

We needed a clear way to organize the codebase that would:
- Separate concerns (data, UI, business logic)
- Make code testable
- Allow easy extension
- Follow common software patterns

## Decision

We adopted the **Model-View-Controller (MVC)** pattern:

- **Model**: Data structures (`PatchData`, `PatchBank`, `DeviceModel`) - no UI dependencies
- **View**: UI components (all `*Panel`, `*Item` classes) - minimal logic
- **Controller**: Business logic (`PatchManager`, `MidiManager`, etc.) - coordinates Model and View

## Consequences

### Positive
- Clear separation of concerns
- Models can be tested independently
- Views can be swapped without changing business logic
- Easy to understand code organization
- Follows common industry patterns

### Negative
- Slightly more files than monolithic approach
- Requires discipline to maintain separation
- Some boilerplate for change notifications

### Neutral
- Learning curve for developers new to MVC
- More files to navigate (but better organized)

## Alternatives Considered

1. **Monolithic**: Single large file - rejected (hard to maintain)
2. **MVVM**: Model-View-ViewModel - considered but MVC simpler for this use case
3. **Component-Based**: Everything as components - rejected (mixes concerns)

## Notes

This pattern has proven effective for the plugin's needs. The clear separation makes it easy to add features without touching unrelated code.


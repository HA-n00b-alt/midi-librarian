# ADR-004: Custom LookAndFeel for UI Styling

**Status**: Accepted  
**Date**: 2024  
**Deciders**: Development Team

## Context

We wanted a consistent, minimalist UI design inspired by Valhalla DSP plugins. We needed a way to:
- Apply consistent styling across all components
- Easily change the entire theme
- Avoid duplicating styling code
- Follow JUCE best practices

## Decision

We created a custom `ValhallaLookAndFeel` class that inherits from `JUCE::LookAndFeel_V4` and overrides drawing methods for:
- Buttons
- ComboBoxes
- Text editors
- Scrollbars
- Labels

All components use standard JUCE controls, but their appearance is customized through the LookAndFeel.

## Consequences

### Positive
- Single source of truth for styling
- Easy to change entire theme (modify one class)
- Consistent appearance across all components
- Follows JUCE standard approach
- No code duplication

### Negative
- Requires understanding of LookAndFeel system
- Some JUCE components may need custom drawing code
- Can't easily mix different styles

### Neutral
- All components must use the same LookAndFeel instance
- Theme changes require code changes (no runtime theme switching)

## Alternatives Considered

1. **Individual Component Styling**: Rejected - code duplication, inconsistent
2. **CSS-like Styling**: Not available in JUCE
3. **Theme System**: Considered but LookAndFeel is simpler for our needs

## Notes

This approach has worked well. The Valhalla-inspired design is consistent throughout, and changing colors/fonts is as simple as modifying constants in one file.


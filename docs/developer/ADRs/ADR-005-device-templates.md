# ADR-005: Device Template System

**Status**: Accepted  
**Date**: 2024  
**Deciders**: Development Team

## Context

Different hardware synths have different capabilities:
- Patch ranges (some have 32, some 128, some more)
- Bank select methods (MSB, LSB, both, or none)
- Default MIDI channels
- Future: SysEx formats, parameter maps

We needed a way to support device-specific features without hardcoding everything.

## Decision

We implemented a **Device Template System**:

1. `DeviceTemplate` class defines device properties
2. `DeviceTemplateManager` manages available templates
3. Templates stored as JSON files (easy to share)
4. Factory templates included (common synths)
5. Custom templates can be added by users

Templates define:
- Device name and manufacturer
- Valid patch number range
- Bank select method (MSB/LSB)
- Default MIDI channel

## Consequences

### Positive
- Extensible (easy to add new devices)
- Shareable (JSON files can be shared)
- Device-specific validation
- Foundation for future features (SysEx, parameters)
- User-friendly (select from dropdown)

### Negative
- Requires maintaining template library
- Users need to create templates for unsupported devices
- Template format needs to be documented

### Neutral
- Templates are optional (Generic template works for all)
- Can be extended without breaking existing code

## Alternatives Considered

1. **Hardcoded Device Support**: Rejected - not extensible
2. **Plugin Configuration**: Considered but templates are more flexible
3. **Online Template Database**: Future consideration

## Notes

This system provides a good foundation. As we add more device-specific features (SysEx, parameter maps), the template system can be extended without major refactoring.


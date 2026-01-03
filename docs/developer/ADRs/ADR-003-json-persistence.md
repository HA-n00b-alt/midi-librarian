# ADR-003: JSON Persistence Format

**Status**: Accepted  
**Date**: 2024  
**Deciders**: Development Team

## Context

We needed a persistence format for patch data that would:
- Be human-readable (for debugging)
- Be easy to parse and generate
- Support versioning/migration
- Be easy to edit manually if needed
- Work well with JUCE

## Decision

We chose **JSON** as the persistence format using JUCE's built-in JSON support:
- `JSON::toString()` for serialization
- `JSON::parse()` for deserialization
- Human-readable text files
- Easy to extend (just add properties)

## Consequences

### Positive
- Human-readable (easy debugging)
- Easy to edit manually
- Version control friendly
- JUCE has built-in support
- Easy to extend (add properties)
- Can be validated with JSON validators

### Negative
- Larger file size than binary (negligible for our use case)
- Slightly slower parsing (acceptable for 128 patches)
- No built-in schema validation (we validate manually)

### Neutral
- JSON is widely understood
- Easy to migrate to other formats if needed

## Alternatives Considered

1. **Binary Format**: Rejected - not human-readable, harder to debug
2. **XML**: Considered but JSON is simpler and more modern
3. **SQLite**: Overkill for our simple data structure
4. **JUCE ValueTree**: Considered but JSON is more flexible for our needs

## Notes

JSON has proven to be the right choice. The human-readable format makes debugging much easier, and the file size is negligible (patches.json is typically < 10KB).


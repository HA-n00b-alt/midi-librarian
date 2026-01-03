# Architecture Decision Records (ADRs)

This directory contains Architecture Decision Records documenting significant architectural decisions made in this project.

## What are ADRs?

ADRs are documents that capture important architectural decisions, the context of those decisions, and the consequences. They help future developers understand why certain choices were made.

## ADR Format

Each ADR follows this structure:

1. **Title**: Short descriptive title
2. **Status**: Proposed, Accepted, Deprecated, Superseded
3. **Context**: The issue motivating this decision
4. **Decision**: The change we're proposing or have made
5. **Consequences**: What becomes easier or harder

## ADR Index

### ADR-001: MVC Architecture Pattern
**Status**: Accepted  
**Date**: 2024  
**Summary**: Decision to use Model-View-Controller pattern for code organization.

### ADR-002: Threading Model for MIDI I/O
**Status**: Accepted  
**Date**: 2024  
**Summary**: Decision to use FIFO-based queue for audio thread MIDI processing.

### ADR-003: JSON Persistence Format
**Status**: Accepted  
**Date**: 2024  
**Summary**: Decision to use JSON for data persistence instead of binary format.

### ADR-004: Custom LookAndFeel for UI Styling
**Status**: Accepted  
**Date**: 2024  
**Summary**: Decision to use JUCE's LookAndFeel class for consistent UI styling.

### ADR-005: Device Template System
**Status**: Accepted  
**Date**: 2024  
**Summary**: Decision to implement device-specific templates for synth profiles.

## Creating New ADRs

When making a significant architectural decision:

1. Create new ADR file: `ADR-XXX-title.md`
2. Use the template below
3. Update this README with the new ADR
4. Commit with message: `docs: add ADR-XXX for [decision]`

## ADR Template

```markdown
# ADR-XXX: [Title]

**Status**: Proposed/Accepted/Deprecated/Superseded  
**Date**: YYYY-MM-DD  
**Deciders**: [Names]

## Context

[Describe the issue that is motivating this decision]

## Decision

[Describe the change that we're proposing or have made]

## Consequences

### Positive
- [Consequence 1]
- [Consequence 2]

### Negative
- [Consequence 1]
- [Consequence 2]

### Neutral
- [Consequence 1]
```


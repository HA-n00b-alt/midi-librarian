# Branch Strategy

## Overview

This project uses a branching strategy optimized for:
- Stable main branch
- Active development in feature branches
- Clear separation between MVP1 and MVP2

## Branch Structure

### `main`
- **Purpose**: Production-ready, stable code
- **Protection**: Requires review before merge
- **Status**: Should always build and work
- **Merges from**: `development` (after testing)

### `development` (MVP1)
- **Purpose**: Active development for MVP1
- **Status**: Working towards stable MVP1
- **Merges from**: Feature branches
- **Merges to**: `main` (when MVP1 is complete)

### `mvp2`
- **Purpose**: Future features and enhancements
- **Status**: Starting point for MVP2 development
- **Based on**: `main` (after MVP1 is stable)
- **Merges from**: Feature branches for MVP2 features

### `feature/*`
- **Purpose**: Individual features or fixes
- **Naming**: `feature/description` or `fix/description`
- **Merges to**: `development` or `mvp2`
- **Lifecycle**: Delete after merge

## Workflow

### Starting New Feature

```bash
# For MVP1 features
git checkout development
git pull origin development
git checkout -b feature/my-feature

# For MVP2 features
git checkout mvp2
git pull origin mvp2
git checkout -b feature/my-feature
```

### Completing Feature

```bash
# Commit and push
git add .
git commit -m "feat: description"
git push origin feature/my-feature

# Create pull request
# After review and merge, delete branch
git checkout development
git branch -d feature/my-feature
```

### Releasing MVP1

```bash
# When MVP1 is stable
git checkout development
git checkout -b release/mvp1
# Tag release
git tag -a v1.0.0 -m "MVP1 Release"
git push origin v1.0.0

# Merge to main
git checkout main
git merge development
git push origin main

# Create mvp2 branch from main
git checkout -b mvp2
git push origin mvp2
```

## Branch Protection Rules

### `main`
- Require pull request reviews
- Require status checks to pass
- No direct pushes (must go through PR)

### `development`
- Require pull request reviews
- Allow force push (for rebasing)
- Auto-delete merged branches

## Versioning

We use [Semantic Versioning](https://semver.org/):
- **Major**: Breaking changes
- **Minor**: New features (backward compatible)
- **Patch**: Bug fixes

Examples:
- `v1.0.0` - MVP1 initial release
- `v1.1.0` - MVP1 with new features
- `v1.1.1` - MVP1 bug fix
- `v2.0.0` - MVP2 (may have breaking changes)

## Current Status

- **`main`**: ✅ Clean, single commit (MVP1 Release v1.0.0)
- **`development`**: ✅ Active MVP1 development (full history)
- **`mvp2`**: ❌ Not created yet (will branch from `main` when ready)

## Branch Purpose

See [BRANCH_PURPOSE.md](BRANCH_PURPOSE.md) for detailed explanation of what goes in each branch.

**Quick Summary**:
- **`main`**: Production releases only (clean, stable)
- **`development`**: Active MVP1 work (bug fixes, improvements)
- **`mvp2`**: Future features (create from `main` when ready)

## Cleaning Main Branch for First Release

✅ **Completed**: Main branch has been cleaned. See [CLEAN_MAIN_BRANCH.md](CLEAN_MAIN_BRANCH.md) for details.

## Migration Plan

### From Current State to Organized Structure

1. **Create Development Branch**
   ```bash
   git checkout -b development
   git push origin development
   ```

2. **Organize Documentation** (current work)
   - Move docs to `docs/` directory
   - Clean up root directory

3. **Create MVP2 Branch** (after MVP1 is stable)
   ```bash
   git checkout main
   git checkout -b mvp2
   git push origin mvp2
   ```

4. **Continue Development**
   - Work on MVP1 in `development`
   - Future work on MVP2 in `mvp2`

## Best Practices

1. **Keep Branches Small**: One feature per branch
2. **Regular Merges**: Merge `development` into feature branches regularly
3. **Clear Names**: Use descriptive branch names
4. **Clean History**: Squash commits when merging (if appropriate)
5. **Document Changes**: Update docs with significant changes


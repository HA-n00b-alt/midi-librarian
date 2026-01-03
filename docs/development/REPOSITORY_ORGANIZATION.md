# Repository Organization

## Overview

This document describes the repository organization and branch strategy for the MIDI Librarian project.

## Directory Structure

### Source Code
- `Source/` - All source code organized by layer (Model/View/Controller)

### Documentation
- `docs/user/` - User-facing documentation
- `docs/developer/` - Developer documentation
- `docs/development/` - Development notes and roadmaps

## Branch Strategy

### Main Branches

1. **`main`**
   - Production-ready, stable code
   - Protected (requires PR review)
   - Only merged from `development` after testing

2. **`development`** (MVP1)
   - Active development branch
   - Working towards stable MVP1
   - Feature branches merge here

3. **`mvp2`**
   - Future features branch
   - Created from `main` after MVP1 is stable
   - Starting point for MVP2 development

### Feature Branches

- `feature/*` - New features
- `fix/*` - Bug fixes
- Merged into `development` or `mvp2`
- Deleted after merge

## Migration to Organized Structure

### Step 1: Create Development Branch

```bash
git checkout -b development
git push origin development
```

### Step 2: Organize Documentation (Current)

Files have been moved to:
- User docs → `docs/user/`
- Developer docs → `docs/developer/`
- Development notes → `docs/development/`

### Step 3: Commit Organization

```bash
git add .
git commit -m "docs: reorganize documentation structure"
git push origin development
```

### Step 4: Create MVP2 Branch (After MVP1 Stable)

```bash
git checkout main
git checkout -b mvp2
git push origin mvp2
```

## File Organization

### Root Directory
- `README.md` - Project overview
- `.gitignore` - Git ignore rules
- `Source/` - Source code

### Documentation
- User-facing: `docs/user/`
- Developer: `docs/developer/`
- Development notes: `docs/development/`

## Cleanup

### Files Moved
- Implementation notes → `docs/development/`
- Roadmap → `docs/development/`
- Phase summaries → `docs/development/`
- Architecture docs → `docs/developer/`
- User guides → `docs/user/`

### Files Remaining in Root
- `README.md` - Main project readme
- `.gitignore` - Git configuration

## Next Steps

1. **Test Build**: Ensure project still builds after reorganization
2. **Update References**: Update any hardcoded paths in code/docs
3. **Create Branches**: Set up `development` and `mvp2` branches
4. **Continue Development**: Work on MVP1 in `development` branch


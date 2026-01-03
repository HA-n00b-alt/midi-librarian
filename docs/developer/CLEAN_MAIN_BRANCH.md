# Cleaning Main Branch for MVP1 Release

## Overview

Yes, cleaning the main branch before the first release is a **common and recommended practice**. This creates a clean starting point for the project's production history.

## Why Clean Main Branch?

### Benefits
1. **Clean History**: Main branch shows only releases, not development noise
2. **Professional**: Clean git history looks more professional
3. **Easier Navigation**: Easier to see release points
4. **Standard Practice**: Many projects do this for first release

### Common Approaches

There are three common approaches:

#### Option 1: Squash All Commits (Recommended for First Release)
- Squash all development commits into one "MVP1 Release" commit
- Keeps a single, clean commit on main
- Development history preserved in `development` branch

#### Option 2: Reset to Clean State
- Reset main to a clean state with organized code
- Single initial commit
- Development history only in `development`

#### Option 3: Keep Linear History
- Keep main as-is but only merge stable releases
- Less clean but preserves all history
- More common for established projects

## Recommended Approach for MVP1

For the first release, we recommend **Option 1 or 2**:

1. Complete all development in `development` branch
2. When MVP1 is ready, create a clean main branch
3. Future releases merge from `development` to `main`

## Implementation Steps

### Step 1: Ensure Development Branch is Ready

```bash
# Make sure all changes are committed
git checkout development
git status

# Ensure everything is organized
git add .
git commit -m "docs: finalize MVP1 organization"
```

### Step 2: Create Clean Main Branch

**Option A: Squash Approach (Preserves History)**

```bash
# Create orphan branch (no history)
git checkout --orphan main-clean

# Add all files
git add .

# Create single initial commit
git commit -m "feat: MVP1 initial release

Complete MIDI Librarian plugin with:
- Patch management (128 slots)
- MIDI device selection
- Search and filtering
- Undo/redo system
- Device templates
- MIDI Learn
- Batch operations
- Clean, modern UI

See docs/ for complete documentation."

# Replace old main
git branch -D main  # Delete old main locally
git branch -m main  # Rename current branch to main
git push -f origin main  # Force push (careful!)
```

**Option B: Reset Approach (Cleaner)**

```bash
# On development branch, create clean main
git checkout development

# Create orphan branch
git checkout --orphan main

# Remove all files (they'll be re-added)
git rm -rf .

# Add organized files
git add .

# Create single initial commit
git commit -m "feat: MVP1 initial release

Complete MIDI Librarian plugin with:
- Patch management (128 slots)
- MIDI device selection
- Search and filtering
- Undo/redo system
- Device templates
- MIDI Learn
- Batch operations
- Clean, modern UI

See docs/ for complete documentation."

# Push clean main
git push -f origin main
```

### Step 3: Tag the Release

```bash
# Tag the release
git tag -a v1.0.0 -m "MVP1 Release"
git push origin v1.0.0
```

### Step 4: Protect Main Branch

After cleaning, protect main branch:
- Require pull request reviews
- No direct pushes
- Only merge from `development` after testing

## Development Workflow After Clean Main

1. **Work in `development` branch**
   - All feature development
   - Bug fixes
   - Documentation updates

2. **Release Process**
   - Test thoroughly in `development`
   - Create release branch: `git checkout -b release/v1.0.1`
   - Final testing
   - Merge to `main`: `git checkout main && git merge release/v1.0.1`
   - Tag release: `git tag -a v1.0.1`

3. **Continue Development**
   - Keep working in `development`
   - Merge bug fixes to `main` as needed
   - Major features go to `mvp2` branch

## Important Notes

### ⚠️ Force Push Warning
- Force pushing to main rewrites history
- Only do this before first release
- After first release, never force push to main
- Coordinate with team if working with others

### 📝 Preserve Development History
- Development history is preserved in `development` branch
- All commits remain accessible
- Only main branch is cleaned

### 🔒 After First Release
- Never force push to main again
- Use normal merge workflow
- Keep main stable and production-ready

## Alternative: Keep Development History

If you prefer to keep all history on main:

```bash
# Just ensure main is clean (organized files)
git checkout main
git merge development
# Resolve any conflicts
git push origin main
```

This keeps all commits but ensures main has the organized structure.

## Recommendation

For MVP1, we recommend **Option B (Reset Approach)**:
- Cleanest starting point
- Professional appearance
- Development history preserved in `development`
- Easy to understand project structure

After MVP1, use normal merge workflow (no force push).

## Checklist

Before cleaning main:
- [ ] All code is complete and tested
- [ ] Documentation is organized
- [ ] All files are in correct locations
- [ ] Development branch is up to date
- [ ] Team is aware (if working with others)
- [ ] Backup is made (just in case)

After cleaning main:
- [ ] Main branch is clean
- [ ] Release is tagged
- [ ] Branch protection is set up
- [ ] Development continues in `development`
- [ ] MVP2 branch created from clean main


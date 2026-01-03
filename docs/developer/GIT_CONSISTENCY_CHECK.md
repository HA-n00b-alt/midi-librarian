# Git Repository Consistency Check

## Summary

This document tracks the consistency check of the local repository with Git.

## Current Status

**Date**: $(date)  
**Branch**: development  
**Status**: See details below

## Repository State

### Branches
- **Local Branches**: `development`, `main`, `mvp2`
- **Remote Branches**: `origin/development`, `origin/main`, `origin/mvp2`
- **Current Branch**: `development`

### Uncommitted Changes
Check with: `git status`

### Untracked Files
Check with: `git ls-files --others --exclude-standard`

### Modified Files
Check with: `git diff --name-only`

### Staged Files
Check with: `git diff --cached --name-only`

## Common Issues to Check

### 1. Uncommitted Changes
- Modified source files
- Modified documentation
- New files not added

### 2. Untracked Files
- `.jucer` file (should be committed or gitignored)
- Build artifacts (should be gitignored)
- Temporary files

### 3. Branch Sync
- Local vs remote branches
- Diverged branches
- Unpushed commits

### 4. Gitignore Issues
- Files that should be ignored but aren't
- Files that shouldn't be ignored but are

## Quick Check Commands

```bash
# Full status
git status

# Check branch sync
git fetch origin
git branch -vv

# Check for untracked files
git ls-files --others --exclude-standard

# Check for modified files
git diff --name-only

# Check gitignore
git check-ignore -v <file>
```

## Expected State

### Should Be Committed
- All source files in `Source/`
- All documentation in `docs/`
- `README.md`
- `.gitignore`
- `setup_juce.sh`

### Should Be Ignored
- `Builds/` directory
- `*.xcodeproj/` directories
- `.DS_Store` files
- `*.jucer` (optional - some teams commit it)

### Should Be Clean
- No uncommitted changes to source files
- No build artifacts
- Branches in sync with remote

## Fixing Issues

### Uncommitted Changes
```bash
# Review changes
git diff

# Stage and commit
git add <files>
git commit -m "message"

# Or discard changes
git checkout -- <file>
```

### Untracked Files
```bash
# Add to gitignore if should be ignored
echo "filename" >> .gitignore

# Or add and commit if should be tracked
git add <file>
git commit -m "message"
```

### Branch Sync Issues
```bash
# Pull remote changes
git fetch origin
git pull origin <branch>

# Push local changes
git push origin <branch>
```

## Regular Maintenance

Run these checks regularly:
1. `git status` - Check for uncommitted changes
2. `git fetch origin` - Update remote refs
3. `git branch -vv` - Check branch sync
4. Review untracked files


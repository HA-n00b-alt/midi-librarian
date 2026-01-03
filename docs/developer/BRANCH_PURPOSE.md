# Branch Purpose and Current State

## Branch Overview

### `main` - Production/Release Branch
**Purpose**: Stable, production-ready code. Only releases go here.

**Current State**:
- ✅ Clean, single commit: "feat: MVP1 initial release"
- ✅ Tagged as `v1.0.0`
- ✅ Contains complete MVP1 codebase
- ✅ Organized documentation structure

**What Goes Here**:
- Only tested, stable releases
- Merged from `development` after thorough testing
- Never force push after first release
- Protected (requires PR review)

**Workflow**:
```
development (tested) → main (release)
```

---

### `development` - Active Development Branch (MVP1)
**Purpose**: Active development for MVP1. Bug fixes, improvements, testing.

**Current State**:
- ✅ Contains full development history
- ✅ Has all MVP1 features
- ✅ Organized documentation
- ✅ Where all MVP1 work continues

**What Goes Here**:
- MVP1 bug fixes
- MVP1 improvements
- MVP1 testing
- Feature branches merge here
- Documentation updates

**Workflow**:
```
feature/* → development → (test) → main
```

**After MVP1 Release**:
- Continue MVP1 bug fixes here
- Merge stable fixes to `main`
- Keep as MVP1 maintenance branch

---

### `mvp2` - Future Features Branch
**Purpose**: Starting point for MVP2 development. Future features and enhancements.

**Current State**:
- ❌ **Not created yet**
- Will be created from `main` after MVP1 is stable
- Clean starting point for MVP2 work

**When to Create**:
- After MVP1 is stable and released
- When ready to start MVP2 features
- Created from clean `main` branch

**What Goes Here**:
- MVP2 feature development
- New major features
- Breaking changes (if any)
- Experimental features

**Workflow**:
```
main (MVP1 stable) → mvp2 (new branch)
feature/* → mvp2 → (test) → main (when ready)
```

---

## Visual Branch Structure

```
main (MVP1 Release)
├── v1.0.0 tag
└── Single clean commit

development (MVP1 Active)
├── Full development history
├── Current MVP1 work
└── Bug fixes & improvements

mvp2 (Future - Not Created Yet)
└── Will branch from main when ready
    └── MVP2 features
```

## Current Workflow

### For MVP1 Work (Now)
1. **Work in `development` branch**
   ```bash
   git checkout development
   git checkout -b feature/my-feature
   # ... make changes ...
   git commit -m "feat: description"
   git push origin feature/my-feature
   # Create PR to development
   ```

2. **Merge to `development`**
   - After PR review
   - Test in development
   - Continue iterating

3. **Release to `main`** (when stable)
   ```bash
   git checkout development
   git checkout -b release/v1.0.1
   # Final testing
   git checkout main
   git merge release/v1.0.1
   git tag -a v1.0.1 -m "Release v1.0.1"
   git push origin main
   ```

### For MVP2 Work (Future)
1. **Create `mvp2` branch** (one time)
   ```bash
   git checkout main
   git checkout -b mvp2
   git push -u origin mvp2
   ```

2. **Work in `mvp2` branch**
   ```bash
   git checkout mvp2
   git checkout -b feature/new-mvp2-feature
   # ... make changes ...
   ```

3. **Merge to `main`** (when MVP2 features are ready)
   - After thorough testing
   - May require version bump (v2.0.0)

## Branch Comparison

| Branch | Purpose | History | Status | When to Use |
|--------|---------|---------|--------|-------------|
| `main` | Releases | Clean (1 commit) | ✅ Ready | Production releases |
| `development` | MVP1 Dev | Full history | ✅ Active | MVP1 work, bug fixes |
| `mvp2` | MVP2 Dev | Will be clean | ❌ Not created | Future features |

## Important Rules

### ✅ DO
- Work in `development` for MVP1
- Merge tested code to `main` for releases
- Create `mvp2` from `main` when ready
- Keep `main` stable and clean
- Tag releases on `main`

### ❌ DON'T
- Never force push to `main` (after first release)
- Don't commit directly to `main` (use PRs)
- Don't mix MVP1 and MVP2 work
- Don't delete `development` (preserves history)

## Example Scenarios

### Scenario 1: MVP1 Bug Fix
```bash
git checkout development
git checkout -b fix/midi-channel-bug
# Fix bug
git commit -m "fix: correct MIDI channel conversion"
git push origin fix/midi-channel-bug
# PR to development → merge → test → PR to main
```

### Scenario 2: MVP1 Feature Addition
```bash
git checkout development
git checkout -b feature/new-ui-improvement
# Add feature
git commit -m "feat: improve patch list UI"
git push origin feature/new-ui-improvement
# PR to development → merge → test → PR to main
```

### Scenario 3: Start MVP2
```bash
# After MVP1 is stable
git checkout main
git checkout -b mvp2
git push -u origin mvp2
# Now work on MVP2 features
```

### Scenario 4: MVP2 Feature
```bash
git checkout mvp2
git checkout -b feature/sysex-backup
# Add feature
git commit -m "feat: add SysEx backup/restore"
git push origin feature/sysex-backup
# PR to mvp2 → merge → test → eventually PR to main
```

## Summary

- **`main`**: Clean release branch (MVP1 v1.0.0)
- **`development`**: Active MVP1 work (full history)
- **`mvp2`**: Future features (create from main when ready)

All MVP1 work continues in `development`. `main` is for releases only. `mvp2` will be created later for future features.


# Contributing Guidelines

Thank you for your interest in contributing to MIDI Librarian!

## Getting Started

1. **Fork the Repository**
2. **Clone Your Fork**
   ```bash
   git clone [your-fork-url]
   cd midi-librarian
   ```

3. **Set Up Development Environment**
   - Install JUCE and Projucer
   - Open project in Projucer
   - Generate Xcode project
   - Build and test

4. **Create a Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

## Development Workflow

### Branch Strategy

- **`main`**: Production-ready, stable code
- **`development`**: Active development (MVP1)
- **`mvp2`**: Future features branch
- **`feature/*`**: Feature branches
- **`fix/*`**: Bug fix branches

### Making Changes

1. **Plan Your Changes**
   - Check [Improvement Roadmap](../development/IMPROVEMENT_ROADMAP.md)
   - Discuss major changes in issues first
   - Follow existing architecture patterns

2. **Write Code**
   - Follow [Code Style Guide](CODE_STYLE.md)
   - Write clear, self-documenting code
   - Add comments for non-obvious logic
   - Keep functions focused and small

3. **Test Your Changes**
   - Test manually in Logic Pro
   - Verify no regressions
   - Test edge cases
   - Check for memory leaks

4. **Update Documentation**
   - Update user docs if UI changes
   - Update developer docs if architecture changes
   - Add ADR for significant decisions

5. **Commit**
   - Use [conventional commits](https://www.conventionalcommits.org/)
   - Write clear commit messages
   - Keep commits focused (one logical change per commit)

### Commit Message Format

```
<type>: <subject>

<body>

<footer>
```

**Types**:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `style`: Code style (formatting, no logic change)
- `refactor`: Code refactoring
- `test`: Tests
- `chore`: Maintenance

**Examples**:
```
feat: add MIDI learn support for Control Change messages

Implements MIDI learn for CC messages, allowing hardware
controllers to trigger patch recall. Includes visual feedback
during learning mode.

Closes #42
```

```
fix: correct MIDI channel conversion in DeviceModel

Channel was being stored as 1-16 but should be 0-15 internally.
This caused incorrect Program Change messages.

Fixes #38
```

## Pull Request Process

### Before Submitting

1. **Ensure Code Quality**
   - Follows code style guide
   - No compiler warnings
   - No linter errors
   - Properly tested

2. **Update Documentation**
   - User guide (if UI changes)
   - Developer guide (if architecture changes)
   - README (if needed)

3. **Write Clear PR Description**
   - What changed and why
   - How to test
   - Screenshots (if UI changes)
   - Related issues

### PR Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Tested in Logic Pro
- [ ] Tested with hardware synth
- [ ] No regressions

## Checklist
- [ ] Code follows style guide
- [ ] Documentation updated
- [ ] No compiler warnings
- [ ] Tested manually
```

### Review Process

1. **Automated Checks** (future)
   - Code style validation
   - Build verification
   - Test execution

2. **Code Review**
   - At least one approval required
   - Address all review comments
   - Keep discussion constructive

3. **Merge**
   - Squash and merge (preferred)
   - Delete feature branch after merge

## Code Review Guidelines

### For Authors

- **Be Responsive**: Respond to review comments promptly
- **Be Open**: Accept constructive criticism
- **Be Thorough**: Test your changes before requesting review
- **Be Clear**: Explain complex changes in PR description

### For Reviewers

- **Be Constructive**: Provide helpful feedback
- **Be Specific**: Point to exact lines and suggest improvements
- **Be Respectful**: Remember we're all learning
- **Be Timely**: Review PRs within a few days

## Areas for Contribution

### High Priority

- Bug fixes
- Performance improvements
- Documentation improvements
- Additional device templates
- Unit tests

### Medium Priority

- UI/UX improvements
- New features from roadmap
- Code refactoring
- Accessibility improvements

### Low Priority

- Code style cleanup
- Documentation polish
- Example projects
- Tutorial content

## Questions?

- Open an issue for questions
- Check existing documentation
- Review [Architecture Decision Records](ADRs/)
- Ask in PR comments

## Code of Conduct

- Be respectful and inclusive
- Welcome newcomers
- Focus on constructive feedback
- Maintain professional communication

Thank you for contributing! 🎉


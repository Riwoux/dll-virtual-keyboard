# Contributing to Virtual Keyboard DLL

First off, thank you for considering contributing to Virtual Keyboard DLL! It's people like you that make this project better for everyone.

## 🤝 How Can I Contribute?

### Reporting Bugs

Before creating bug reports, please check the existing issues to avoid duplicates. When you create a bug report, include as many details as possible:

**Bug Report Template:**
- **Description**: Clear and concise description of the bug
- **Steps to Reproduce**: 
  1. Step 1
  2. Step 2
  3. ...
- **Expected Behavior**: What you expected to happen
- **Actual Behavior**: What actually happened
- **Environment**:
  - OS: [e.g., Windows 10, Windows 11]
  - C++ Builder Version: [e.g., C++ Builder 13]
  - Platform: [e.g., Win32, Win64]
- **Screenshots**: If applicable
- **Additional Context**: Any other relevant information

### Suggesting Enhancements

Enhancement suggestions are tracked as GitHub issues. When creating an enhancement suggestion, please include:

- **Clear Title**: Use a descriptive title
- **Description**: Detailed description of the suggested enhancement
- **Use Case**: Explain why this enhancement would be useful
- **Possible Implementation**: If you have ideas on how to implement it
- **Alternatives**: Any alternative solutions you've considered

### Pull Requests

We actively welcome your pull requests! Here's the process:

1. **Fork the Repository**
   ```bash
   # Fork via GitHub UI, then clone your fork
   git clone https://github.com/YOUR-USERNAME/testclaviervirtuel.git
   cd testclaviervirtuel
   ```

2. **Create a Branch**
   ```bash
   git checkout -b feature/your-feature-name
   # or
   git checkout -b bugfix/your-bugfix-name
   ```

3. **Make Your Changes**
   - Follow the existing code style
   - Add comments where necessary
   - Update documentation if needed
   - Test your changes thoroughly

4. **Commit Your Changes**
   ```bash
   git add .
   git commit -m "Add: Brief description of your changes"
   ```
   
   Use clear commit messages:
   - `Add:` for new features
   - `Fix:` for bug fixes
   - `Update:` for updates to existing features
   - `Refactor:` for code refactoring
   - `Docs:` for documentation changes

5. **Push to Your Fork**
   ```bash
   git push origin feature/your-feature-name
   ```

6. **Create a Pull Request**
   - Go to the original repository on GitHub
   - Click "New Pull Request"
   - Select your fork and branch
   - Provide a clear title and description
   - Reference any related issues

## 📋 Development Guidelines

### Code Style

- **Indentation**: Use tabs or 4 spaces consistently
- **Naming Conventions**:
  - Classes: `TFormKeyboard`, `TMainForm` (Pascal case with T prefix for VCL)
  - Functions: `ShowKeyboard`, `CreateButton` (Pascal case)
  - Variables: `btnShift`, `numPadActive` (camelCase)
  - Constants: `AZERTY`, `QWERTY` (UPPER_CASE)
- **Comments**: Use clear, concise comments to explain complex logic
- **Formatting**: Keep lines under 100 characters when possible

### C++ Builder Specific

- Use VCL components appropriately
- Ensure compatibility with C++ Builder 13
- Test both Win32 and Win64 builds if possible
- Follow C++ Builder naming conventions for VCL components

### Testing

Before submitting a pull request:

1. **Build the DLL**: Ensure it compiles without errors
   ```
   Project → Build VirtualKeyboardDLL
   ```

2. **Build TestApp**: Ensure the test application compiles
   ```
   Project → Build TestApp
   ```

3. **Manual Testing**: Run the TestApp and verify:
   - Keyboard displays correctly
   - All keys work as expected
   - Layout switching works
   - NumPad toggle works
   - Arrow keys function properly
   - No memory leaks or crashes

4. **Cross-Platform**: If possible, test on both Win32 and Win64

### Documentation

- Update the README.md if you add new features
- Add inline code comments for complex logic
- Document any new API functions
- Update code examples if the API changes

## 🎯 Priority Areas

We're especially interested in contributions in these areas:

1. **New Keyboard Layouts**: Additional language layouts (QWERTZ, Dvorak, etc.)
2. **Accessibility**: Features for users with disabilities
3. **Customization**: More options for visual customization
4. **Performance**: Optimizations and memory improvements
5. **Documentation**: Better examples and tutorials
6. **Testing**: Automated tests and test coverage

## 🔧 Setting Up Development Environment

1. **Install C++ Builder 13** (RAD Studio 12 Athens or compatible)
2. **Clone the Repository**
   ```bash
   git clone https://github.com/Riwoux/testclaviervirtuel.git
   cd testclaviervirtuel
   ```
3. **Open Projects**
   - Open `VirtualKeyboardDLL/VirtualKeyboardDLL.cbproj`
   - Open `TestApp/TestApp.cbproj`
4. **Build and Test**
   - Build the DLL first
   - Copy DLL to TestApp directory
   - Build and run TestApp

## 📜 Code of Conduct

### Our Standards

- Be respectful and inclusive
- Welcome newcomers and help them get started
- Accept constructive criticism gracefully
- Focus on what's best for the community
- Show empathy towards others

### Unacceptable Behavior

- Harassment, discrimination, or offensive comments
- Trolling, insulting, or derogatory remarks
- Public or private harassment
- Publishing others' private information
- Any conduct inappropriate in a professional setting

## ❓ Questions?

If you have questions about contributing:

- Open an issue with the label "question"
- Check existing issues and discussions
- Review the README.md for project details

## 🙏 Recognition

Contributors will be:
- Listed in the project's contributors page
- Mentioned in release notes for significant contributions
- Credited in commit history

Thank you for contributing to Virtual Keyboard DLL! 🎉

---

**Note**: By contributing to this project, you agree that your contributions will be licensed under the MIT License.

# Changelog

All notable changes to the Virtual Keyboard DLL project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Comprehensive documentation in README.md
- Administrative files (.gitignore, .gitattributes, LICENSE, etc.)
- Contributing guidelines
- This changelog

## [2.1.0] - 2026-02-17

### Added
- Enhanced documentation with detailed usage examples
- Complete API reference with integration examples
- Troubleshooting section in documentation
- Customization guide for developers

### Changed
- Improved README structure with emojis and better organization
- Updated keyboard layout diagrams to show all layouts
- Enhanced project description

### Documentation
- Added comprehensive integration examples for VCL and Win32
- Added technical details section
- Added compatibility information
- Added development guidelines

## [2.0.0] - 2026

### Added
- AZERTY keyboard layout (French)
- QWERTY keyboard layout (International)
- Language switching button
- Numeric keypad (NumPad) with toggle functionality
- Arrow keys (Up, Down, Left, Right) for cursor navigation
- Full calculator-style NumPad with operators (+, -, *, /)
- Shift key for uppercase/lowercase toggle

### Features
- Numbers: 0-9 and equals sign (=)
- Full alphabet: A-Z
- Special characters: +, /, *, -, . (period)
- Control keys: Space, Backspace (Delete), Enter
- Always-on-top window behavior
- Clean, button-based interface

### DLL API
- `ShowKeyboard(HWND targetHandle)` - Show virtual keyboard
- `HideKeyboard()` - Hide virtual keyboard
- `IsKeyboardVisible()` - Check keyboard visibility status

### Technical
- Windows messaging support (WM_CHAR, WM_KEYDOWN, WM_KEYUP)
- Compatible with TEdit, TMemo, TRichEdit, and standard Windows controls
- Thread-safe for single-threaded usage per process
- VCL Framework integration

### Project Structure
- VirtualKeyboardDLL - Core library implementation
- TestApp - Demonstration application
- Proper separation of concerns

## [1.0.0] - Initial Release

### Added
- Basic virtual keyboard implementation
- Simple DLL structure
- Test application

---

## Version History Summary

- **2.1.0** - Enhanced documentation and administrative files
- **2.0.0** - Feature-complete version with multiple layouts and NumPad
- **1.0.0** - Initial release with basic functionality

## Future Roadmap

### Planned Features
- [ ] Additional keyboard layouts (QWERTZ, Dvorak, etc.)
- [ ] Customizable themes and colors
- [ ] Sound effects on key press (optional)
- [ ] Keyboard shortcuts support
- [ ] Multi-language UI
- [ ] Accessibility features
- [ ] Configuration file support
- [ ] Auto-hide functionality
- [ ] Resizable keyboard window
- [ ] Custom key mapping

### Under Consideration
- [ ] Touch screen optimization
- [ ] Gesture support
- [ ] Speech-to-text integration
- [ ] Plugin system for custom layouts
- [ ] Network keyboard (remote input)

---

For more information, see [README.md](README.md) and [CONTRIBUTING.md](CONTRIBUTING.md).

# Virtual Keyboard DLL - C++ Builder 13

Simple virtual keyboard implementation as a DLL for C++ Builder 13 with a test application.

## Description

This project provides a simple virtual keyboard DLL that can be integrated into any C++ Builder or Win32 application. The keyboard features a basic AZERTY layout with essential keys.

## Features

- AZERTY keyboard layout (French)
- Numbers 0-9
- Letters A-Z
- Shift key for uppercase
- Special keys: Space, Backspace, Enter
- Stays on top of other windows
- Easy integration via DLL

## Project Structure

```
testclaviervirtuel/
├── VirtualKeyboardDLL/          # DLL Project
│   ├── VirtualKeyboard.h        # Export declarations
│   ├── VirtualKeyboard.cpp      # DLL implementation
│   ├── KeyboardForm.h           # Form header
│   ├── KeyboardForm.cpp         # Keyboard implementation
│   ├── KeyboardForm.dfm         # VCL design
│   └── VirtualKeyboardDLL.cbproj # C++ Builder project
│
├── TestApp/                     # Test Application
│   ├── TestApp.cpp              # Entry point
│   ├── MainForm.h               # Form header
│   ├── MainForm.cpp             # Implementation
│   ├── MainForm.dfm             # VCL design
│   └── TestApp.cbproj           # C++ Builder project
│
└── README.md                    # This file
```

## Requirements

- C++ Builder 13 (RAD Studio 12 Athens) or compatible version
- VCL Framework (included with C++ Builder)
- Windows SDK (included with RAD Studio)
- Windows 32-bit or 64-bit

## Building

### 1. Build the DLL

```bash
cd VirtualKeyboardDLL
# Open VirtualKeyboardDLL.cbproj in C++ Builder
# Menu: Project → Build VirtualKeyboardDLL
```

The DLL will be generated in `VirtualKeyboardDLL/Win32/Debug/` or `Win32/Release/`

### 2. Build the Test Application

```bash
cd TestApp
# Open TestApp.cbproj in C++ Builder
# Menu: Project → Build TestApp
```

The executable will be generated in `TestApp/Win32/Debug/` or `Win32/Release/`

### 3. Deployment

Copy `VirtualKeyboardDLL.dll` to the same directory as `TestApp.exe` or to the system PATH.

## Usage

### Testing

1. Launch `TestApp.exe`
2. Click **"Show Keyboard"**
3. The virtual keyboard appears
4. Click keys to type in the memo
5. Click **"Hide Keyboard"** to close it

### DLL Integration

#### Exported Functions

```cpp
// Show the keyboard
extern "C" __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle);

// Hide the keyboard
extern "C" __declspec(dllexport) void __stdcall HideKeyboard();

// Check if keyboard is visible
extern "C" __declspec(dllexport) bool __stdcall IsKeyboardVisible();
```

#### Integration Example

```cpp
#include <windows.h>

// Function types
typedef void (__stdcall *TShowKeyboardProc)(HWND targetHandle);
typedef void (__stdcall *THideKeyboardProc)();

// Load the DLL
HINSTANCE hDll = LoadLibrary(L"VirtualKeyboardDLL.dll");
if (hDll) {
    auto ShowKeyboard = (TShowKeyboardProc)GetProcAddress(hDll, "ShowKeyboard");
    auto HideKeyboard = (THideKeyboardProc)GetProcAddress(hDll, "HideKeyboard");
    
    // Show the keyboard
    if (ShowKeyboard) {
        ShowKeyboard(MyEdit->Handle);
    }
    
    // Hide the keyboard
    if (HideKeyboard) {
        HideKeyboard();
    }
    
    // Unload the DLL
    FreeLibrary(hDll);
}
```

## Keyboard Layout

```
[1] [2] [3] [4] [5] [6] [7] [8] [9] [0]
[A] [Z] [E] [R] [T] [Y] [U] [I] [O] [P]
  [Q] [S] [D] [F] [G] [H] [J] [K] [L] [M]
    [W] [X] [C] [V] [B] [N]
[Maj] [     Space     ] [←] [Enter]
```

## Technical Notes

- The keyboard sends characters using Windows messages (WM_CHAR, WM_KEYDOWN, WM_KEYUP)
- Compatible with TEdit, TMemo, TRichEdit and all standard Windows controls
- Thread-safe for single-threaded usage per process
- Requires VCL runtimes from C++ Builder

## License

This project is a demonstration example for C++ Builder 13.
Free to use for personal and commercial projects.

---

**Version**: 2.0 (Simplified)  
**Date**: 2026  
**Compatible with**: C++ Builder 13 (RAD Studio 12 Athens)

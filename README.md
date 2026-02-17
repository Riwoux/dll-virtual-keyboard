# Virtual Keyboard DLL - C++ Builder 13

A comprehensive and flexible virtual keyboard implementation as a DLL for C++ Builder 13, featuring multiple keyboard layouts, a numeric keypad, and easy integration into any Win32 application.

## 📋 Description

This project provides a fully-featured virtual keyboard DLL that can be seamlessly integrated into any C++ Builder or Win32 application. The keyboard is designed to be lightweight, customizable, and user-friendly, with support for multiple keyboard layouts and an optional numeric keypad.

## ✨ Features

### Keyboard Layouts
- **AZERTY layout** (French keyboard)
- **QWERTY layout** (International keyboard)
- **Easy layout switching** with Language button

### Input Keys
- **Numbers**: 0-9 and equals sign (=)
- **Letters**: A-Z (full alphabet)
- **Special characters**: +, /, *, -, . (period)
- **Control keys**: 
  - Shift (uppercase/lowercase toggle)
  - Space
  - Backspace (Delete)
  - Enter
  - Arrow keys (Up, Down, Left, Right)

### Numeric Keypad (NumPad)
- **Toggle NumPad** - Show/hide numeric keypad
- **Full calculator layout**:
  - Numbers: 0-9
  - Operators: +, -, *, /
  - Decimal point (.)
  - Enter key

### User Experience
- **Always on top** - Stays visible above other windows
- **Responsive design** - Clean, button-based interface
- **Thread-safe** - Safe for single-threaded usage per process
- **Easy integration** - Simple DLL API with just 3 exported functions

## 📁 Project Structure

```
testclaviervirtuel/
├── VirtualKeyboardDLL/          # DLL Project (Core Library)
│   ├── VirtualKeyboard.h        # DLL export declarations
│   ├── VirtualKeyboard.cpp      # DLL entry point and exports
│   ├── KeyboardForm.h           # Keyboard form interface
│   ├── KeyboardForm.cpp         # Keyboard UI and logic implementation
│   ├── KeyboardForm.dfm         # VCL form design (visual layout)
│   └── VirtualKeyboardDLL.cbproj # C++ Builder project file
│
├── TestApp/                     # Demo/Test Application
│   ├── TestApp.cpp              # Application entry point
│   ├── MainForm.h               # Main form header
│   ├── MainForm.cpp             # DLL integration example
│   ├── MainForm.dfm             # VCL form design
│   └── TestApp.cbproj           # C++ Builder project file
│
├── .gitignore                   # Git ignore rules
└── README.md                    # This documentation file
```

## 🔧 Requirements

- **IDE**: C++ Builder 13 (RAD Studio 12 Athens) or compatible version
- **Framework**: VCL Framework (included with C++ Builder)
- **SDK**: Windows SDK (included with RAD Studio)
- **Platform**: Windows (32-bit or 64-bit)
- **Runtime**: VCL runtime libraries from C++ Builder

## 🏗️ Building the Project

### Step 1: Build the DLL

1. Navigate to the DLL project directory:
   ```bash
   cd VirtualKeyboardDLL
   ```

2. Open `VirtualKeyboardDLL.cbproj` in C++ Builder 13

3. Build the project:
   - Menu: **Project → Build VirtualKeyboardDLL**
   - Or press: `Shift + F9`

4. Output location:
   - Debug build: `VirtualKeyboardDLL/Win32/Debug/VirtualKeyboardDLL.dll`
   - Release build: `VirtualKeyboardDLL/Win32/Release/VirtualKeyboardDLL.dll`

### Step 2: Build the Test Application

1. Navigate to the test app directory:
   ```bash
   cd TestApp
   ```

2. Open `TestApp.cbproj` in C++ Builder 13

3. Build the project:
   - Menu: **Project → Build TestApp**
   - Or press: `Shift + F9`

4. Output location:
   - Debug build: `TestApp/Win32/Debug/TestApp.exe`
   - Release build: `TestApp/Win32/Release/TestApp.exe`

### Step 3: Deployment

For the test application to run properly, **copy** the `VirtualKeyboardDLL.dll` file to:

**Option A** (Recommended for testing):
```bash
# Copy to the same directory as TestApp.exe
cp VirtualKeyboardDLL/Win32/Debug/VirtualKeyboardDLL.dll TestApp/Win32/Debug/
```

**Option B** (System-wide installation):
- Add the DLL directory to your system PATH
- Or copy the DLL to `C:\Windows\System32` (requires administrator rights)

## 🚀 Usage

### Running the Test Application

1. **Launch** the application:
   ```
   TestApp/Win32/Debug/TestApp.exe
   ```

2. **Show the keyboard**:
   - Click the **"Show Keyboard"** button
   - The virtual keyboard window will appear on top of all windows

3. **Type with the keyboard**:
   - Click on any key to type in the memo field
   - Use **Shift** to toggle uppercase/lowercase
   - Click **Language** to switch between AZERTY and QWERTY layouts
   - Click **NumPad** to show/hide the numeric keypad
   - Use **arrow keys** for cursor navigation

4. **Hide the keyboard**:
   - Click the **"Hide Keyboard"** button
   - Or close the keyboard window directly

### Integrating into Your Application

#### DLL API Reference

The DLL exports three simple functions:

```cpp
// Show the virtual keyboard and attach it to a target control
extern "C" __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle);

// Hide the virtual keyboard
extern "C" __declspec(dllexport) void __stdcall HideKeyboard();

// Check if the keyboard is currently visible
extern "C" __declspec(dllexport) bool __stdcall IsKeyboardVisible();
```

#### Integration Example

```cpp
#include <windows.h>

// Define function pointer types
typedef void (__stdcall *TShowKeyboardProc)(HWND targetHandle);
typedef void (__stdcall *THideKeyboardProc)();
typedef bool (__stdcall *TIsKeyboardVisibleProc)();

class MyApplication {
private:
    HINSTANCE hDll;
    TShowKeyboardProc ShowKeyboard;
    THideKeyboardProc HideKeyboard;
    TIsKeyboardVisibleProc IsKeyboardVisible;

public:
    // Load the DLL
    bool LoadKeyboardDLL() {
        hDll = LoadLibrary(L"VirtualKeyboardDLL.dll");
        if (!hDll) {
            return false;
        }
        
        // Get function pointers
        ShowKeyboard = (TShowKeyboardProc)GetProcAddress(hDll, "ShowKeyboard");
        HideKeyboard = (THideKeyboardProc)GetProcAddress(hDll, "HideKeyboard");
        IsKeyboardVisible = (TIsKeyboardVisibleProc)GetProcAddress(hDll, "IsKeyboardVisible");
        
        return (ShowKeyboard && HideKeyboard && IsKeyboardVisible);
    }
    
    // Show keyboard for a text control
    void ShowVirtualKeyboard(HWND editControl) {
        if (ShowKeyboard) {
            ShowKeyboard(editControl);
        }
    }
    
    // Hide the keyboard
    void HideVirtualKeyboard() {
        if (HideKeyboard) {
            HideKeyboard();
        }
    }
    
    // Check visibility
    bool IsVirtualKeyboardVisible() {
        if (IsKeyboardVisible) {
            return IsKeyboardVisible();
        }
        return false;
    }
    
    // Cleanup
    ~MyApplication() {
        if (hDll) {
            FreeLibrary(hDll);
        }
    }
};

// Example usage in a form/window
void OnButtonClick() {
    MyApplication app;
    
    if (app.LoadKeyboardDLL()) {
        // Show keyboard attached to an edit control
        app.ShowVirtualKeyboard(MyEditControl->Handle);
        
        // Later, hide it
        // app.HideVirtualKeyboard();
    }
}
```

#### Integration with VCL Components

For C++ Builder VCL applications:

```cpp
// In your form's header (.h file)
class TForm1 : public TForm
{
private:
    HINSTANCE FDllHandle;
    TShowKeyboardProc FShowKeyboard;
    THideKeyboardProc FHideKeyboard;
    
    bool LoadKeyboardDLL();
    void UnloadKeyboardDLL();
    
public:
    __fastcall TForm1(TComponent* Owner);
    __fastcall ~TForm1();
};

// In your form's implementation (.cpp file)
bool TForm1::LoadKeyboardDLL()
{
    String dllPath = ExtractFilePath(Application->ExeName) + "VirtualKeyboardDLL.dll";
    FDllHandle = LoadLibraryW(dllPath.c_str());
    
    if (FDllHandle) {
        FShowKeyboard = (TShowKeyboardProc)GetProcAddress(FDllHandle, "ShowKeyboard");
        FHideKeyboard = (THideKeyboardProc)GetProcAddress(FDllHandle, "HideKeyboard");
        return (FShowKeyboard != NULL && FHideKeyboard != NULL);
    }
    
    return false;
}

void TForm1::UnloadKeyboardDLL()
{
    if (FDllHandle) {
        FreeLibrary(FDllHandle);
        FDllHandle = NULL;
    }
}

// Button click handler to show keyboard
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    if (FShowKeyboard) {
        FShowKeyboard(Edit1->Handle);  // Attach to Edit1 control
    }
}

// Button click handler to hide keyboard
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    if (FHideKeyboard) {
        FHideKeyboard();
    }
}
```

## 🎹 Keyboard Layouts

### AZERTY Layout (French)
```
┌─────────────────────────────────────────────────────────┐
│ [1] [2] [3] [4] [5] [6] [7] [8] [9] [0] [=]  [Delete]  │
│ [A] [Z] [E] [R] [T] [Y] [U] [I] [O] [P]                │
│   [Q] [S] [D] [F] [G] [H] [J] [K] [L] [M]              │
│     [W] [X] [C] [V] [B] [N]                            │
│                                                         │
│ [Shift] [      Space      ] [Enter]  [↑]               │
│                                      [←][↓][→]         │
│                                                         │
│ [Language] [NumPad]                                    │
└─────────────────────────────────────────────────────────┘
```

### QWERTY Layout (International)
```
┌─────────────────────────────────────────────────────────┐
│ [1] [2] [3] [4] [5] [6] [7] [8] [9] [0] [=]  [Delete]  │
│ [Q] [W] [E] [R] [T] [Y] [U] [I] [O] [P]                │
│   [A] [S] [D] [F] [G] [H] [J] [K] [L]                  │
│     [Z] [X] [C] [V] [B] [N] [M]                        │
│                                                         │
│ [Shift] [      Space      ] [Enter]  [↑]               │
│                                      [←][↓][→]         │
│                                                         │
│ [Language] [NumPad]                                    │
└─────────────────────────────────────────────────────────┘
```

### Numeric Keypad (Optional)
```
┌───────────────────┐
│ [/] [*] [-]       │
│ [7] [8] [9]  [+]  │
│ [4] [5] [6]       │
│ [1] [2] [3] [Ent] │
│ [0] [.]           │
└───────────────────┘
```

The NumPad can be toggled on/off using the "NumPad" button on the main keyboard.

## 🔍 Technical Details

### How It Works

The virtual keyboard sends input to the target control using Windows messaging:

- **WM_CHAR**: For character input (letters, numbers, symbols)
- **WM_KEYDOWN / WM_KEYUP**: For special keys (Enter, Backspace, arrows)

This approach ensures compatibility with all standard Windows controls.

### Compatibility

The keyboard works with all standard Windows edit controls:
- ✅ `TEdit` (VCL single-line edit)
- ✅ `TMemo` (VCL multi-line edit)
- ✅ `TRichEdit` (VCL rich text edit)
- ✅ Windows `EDIT` control (Win32 API)
- ✅ Any control that responds to WM_CHAR messages

### Thread Safety

- The keyboard is **safe for single-threaded usage** per process
- Multiple processes can each have their own keyboard instance
- Not designed for concurrent access from multiple threads

### Window Behavior

- **Always on Top**: The keyboard window uses `fsStayOnTop` form style
- **Tool Window**: Uses `bsToolWindow` border style for a compact title bar
- **Centered**: Initially appears at the center of the screen

## 🐛 Troubleshooting

### DLL Not Found Error

**Problem**: "Cannot load VirtualKeyboardDLL.dll"

**Solutions**:
1. Ensure the DLL is in the same directory as your .exe
2. Check that you built the DLL for the correct platform (Win32 vs Win64)
3. Verify that the DLL filename is exactly `VirtualKeyboardDLL.dll`
4. Make sure all required VCL runtime DLLs are available

### Keyboard Not Responding

**Problem**: Keyboard shows but keys don't work

**Solutions**:
1. Verify you're passing a valid window handle to `ShowKeyboard()`
2. Check that the target control accepts keyboard input
3. Ensure the target window is not disabled or read-only
4. Try clicking on the target control to give it focus first

### Build Errors

**Problem**: Project won't compile

**Solutions**:
1. Ensure you're using C++ Builder 13 (RAD Studio 12 Athens)
2. Check that VCL is properly installed
3. Verify all source files are in the correct directories
4. Clean and rebuild the project (Project → Clean, then Build)

### Missing Characters

**Problem**: Some keys don't appear in the target control

**Solutions**:
1. Check if the target control has a character limit
2. Verify the control's `MaxLength` property (for VCL)
3. Ensure the control supports the character set you're using

## 📝 Customization

### Modifying the Keyboard Layout

To customize the keyboard layout, edit `KeyboardForm.cpp`:

1. **Add new keys**: Create buttons in the constructor
2. **Change layout**: Modify the key positions and labels
3. **Add new languages**: Extend the language switching logic

Example - Adding a new key:
```cpp
TButton* btnNewKey = CreateButton("@", xPosition, yPosition, width, height);
btnNewKey->Tag = (NativeInt)(wchar_t)'@';
btnNewKey->OnMouseDown = OnKeyButtonMouseDown;
```

### Changing Keyboard Size

In `KeyboardForm.cpp` constructor:
```cpp
ClientWidth = 700;   // Change width
ClientHeight = 270;  // Change height
```

### Customizing Button Appearance

In `KeyboardForm.cpp`, modify the `CreateButton()` function or set properties after creation:
```cpp
btn->Font->Size = 12;      // Change font size
btn->Color = clBtnFace;    // Change button color
btn->Font->Name = "Arial"; // Change font
```

## 🤝 Contributing

Contributions are welcome! Here are some ways you can contribute:

1. **Bug Reports**: Open an issue describing the bug and steps to reproduce
2. **Feature Requests**: Suggest new features or improvements
3. **Code Contributions**: 
   - Fork the repository
   - Create a feature branch
   - Make your changes
   - Submit a pull request

### Development Guidelines

- Follow the existing code style and structure
- Test your changes with the TestApp
- Ensure compatibility with C++ Builder 13
- Document any new features or API changes

## 📄 License

This project is provided as a demonstration example for C++ Builder 13.

**Free to use** for personal and commercial projects.

No warranty is provided. Use at your own risk.

## 📚 Additional Resources

- [C++ Builder Documentation](https://docwiki.embarcadero.com/RADStudio/en/Main_Page)
- [VCL Framework Guide](https://docwiki.embarcadero.com/RADStudio/en/VCL_Framework)
- [Windows API Reference](https://docs.microsoft.com/en-us/windows/win32/api/)

## 📧 Support

For questions, issues, or suggestions:
- Open an issue on GitHub
- Check existing issues for similar problems
- Refer to the troubleshooting section above

---

**Project Information**
- **Version**: 2.1 (Enhanced)
- **Last Updated**: 2026
- **Compatible with**: C++ Builder 13 (RAD Studio 12 Athens)
- **Platform**: Windows (32-bit and 64-bit)

---

Made with ❤️ for the C++ Builder community

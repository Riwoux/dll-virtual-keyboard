//---------------------------------------------------------------------------
// VirtualKeyboard.h - DLL Export Functions
//---------------------------------------------------------------------------
#ifndef VirtualKeyboardH
#define VirtualKeyboardH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

// DLL Exports
extern "C" {
    __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle);
    __declspec(dllexport) void __stdcall HideKeyboard();
    __declspec(dllexport) bool __stdcall IsKeyboardVisible();
}

//---------------------------------------------------------------------------
#endif

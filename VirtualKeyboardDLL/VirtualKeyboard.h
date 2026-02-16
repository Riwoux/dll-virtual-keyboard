//---------------------------------------------------------------------------
// VirtualKeyboard.h - En-têtes des fonctions exportées de la DLL
//---------------------------------------------------------------------------
#ifndef VirtualKeyboardH
#define VirtualKeyboardH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

// Exports de la DLL
extern "C" {
    __declspec(dllexport) void __stdcall ShowKeyboard(int mode, HWND targetHandle);
    __declspec(dllexport) void __stdcall HideKeyboard();
    __declspec(dllexport) bool __stdcall IsKeyboardVisible();
    __declspec(dllexport) void __stdcall SetKeyboardMode(int mode);
}

//---------------------------------------------------------------------------
#endif

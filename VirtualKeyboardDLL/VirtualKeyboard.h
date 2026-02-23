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
    __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle, int etat); // etat : '0': clavier classique, '1': pavé numérique seulement
    __declspec(dllexport) void __stdcall HideKeyboard();
    __declspec(dllexport) bool __stdcall IsKeyboardVisible();
}

//---------------------------------------------------------------------------
#endif

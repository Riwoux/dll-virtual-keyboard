#ifndef touchkeyboardH
#define touchkeyboardH


#include <vcl.h>
#include <tchar.h>

extern "C" {
    __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle, int etat=-1);
    __declspec(dllexport) void __stdcall HideKeyboard();
    __declspec(dllexport) void __stdcall AttachKeyboardToForm(HWND formHandle, bool autoHide = true);
    __declspec(dllexport) void __stdcall DetachKeyboardFromForm(HWND formHandle);
}

#endif touchkeyboardH

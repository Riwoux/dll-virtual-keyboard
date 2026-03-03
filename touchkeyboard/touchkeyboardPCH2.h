#ifndef touchkeyboardH
#define touchkeyboardH

#include <tchar.h>
#include <vcl.h>
#include <windows.h>
#include <commctrl.h>
#include <map>
#include "clavier.h"

extern "C" {
    __declspec(dllexport) void __stdcall KeyboardShow(HWND targetHandle, int etat=-1);
    __declspec(dllexport) void __stdcall KeyboardHide();
    __declspec(dllexport) void __stdcall KeyboardToFormAttach(HWND formHandle, bool autoHide = true);
    __declspec(dllexport) void __stdcall KeyboardFromFormDetach(HWND formHandle);
    __declspec(dllexport) void __stdcall KeyboardAutoShow(HWND hwnd);
}

#endif

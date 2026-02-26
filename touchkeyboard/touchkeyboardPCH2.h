#ifndef touchkeyboardH
#define touchkeyboardH


#include <vcl.h>
#include <tchar.h>

extern "C" {
    __declspec(dllexport) void __stdcall KeyboardShow(HWND targetHandle, int etat=-1);
    __declspec(dllexport) void __stdcall KeyboardHide();
    __declspec(dllexport) void __stdcall KeyboardToFormAttach(HWND formHandle, bool autoHide = true);
    __declspec(dllexport) void __stdcall KeyboardFromFormDetach(HWND formHandle);
    __declspec(dllexport) void __stdcall KeyboardAutoShow(TObject *Sender);
}

#endif

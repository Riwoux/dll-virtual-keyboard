//---------------------------------------------------------------------------
// MainForm.cpp - Simple Test Application Implementation
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;


// Début modif 023 CL
typedef void* (*FuncKeyboardShow)(HWND targetHandle, int etat);
typedef void* (*FuncKeyboardHide)();
typedef void* (*FuncKeyboardToFormAttach)(HWND formHandle, bool autoHide);
typedef void* (*FuncKeyboardFromFormDetach)(HWND formHandle);
typedef void* (*FuncKeyboardAutoShow)(HWND hwnd);
//Fin modif 023 CL

//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner):
	TForm(Owner)
{
}

//---------------------------------------------------------------------------
// Form creation event
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    Edit1->OnEnter = TextControlEnter;
    Edit2->OnEnter = TextControlEnter;
    if (KeyboardAttachToForm) {
        KeyboardAttachToForm(Handle, true);
    }
}

//---------------------------------------------------------------------------
// Form destruction event
//---------------------------------------------------------------------------
void __fastcall TFormMain::TextControlEnter(TObject* Sender)
{
    TWinControl *ctrl = dynamic_cast<TWinControl*>(Sender);  // Safe - same module
    if (ctrl) {
        KeyboardAutoShow(ctrl->Handle);
    }
}

//Début modif 023 CL
int KeyboardShow(HWND targetHandle, int etat)
{
	HINSTANCE load;
	wchar_t Ch[500], Ch1[500];
	LPCSTR functionName = "KeyboardShow";

	Wstrcpy(Ch, Application->ExeName.c_str());
	Wstrcpy(Ch1, dirClavierVirtuel.c_str());
	Ch1[0] = Ch[0];
	load = LoadLibrary(Ch1);
	if (load)
	{
        // GetProcAddress returns a pointer to the loaded method
    	FuncKeyboardShow myFunc = FuncKeyboardShow(GetProcAddress(load, functionName));

        if (myFunc != nullptr) {
            try {
                myFunc(targetHandle, etat);
                return 0;
            } catch (...) {
                ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")\nPlease update this DLL");
				return -1;
            }
        }
        else
		 {
			 ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")");
			 return -1;
		 }
    }
    else
    {
        return -1;
    }
}

int KeyboardHide()
{
	HINSTANCE load;
	wchar_t Ch[500], Ch1[500];
	LPCSTR functionName = "KeyboardHide";

	Wstrcpy(Ch, Application->ExeName.c_str());
	Wstrcpy(Ch1, dirClavierVirtuel.c_str());
	Ch1[0] = Ch[0];
	load = LoadLibrary(Ch1);
	if (load)
	{
        // GetProcAddress returns a pointer to the loaded method
    	FuncKeyboardHide myFunc = FuncKeyboardHide(GetProcAddress(load, functionName));

        if (myFunc != nullptr) {
            try {
                myFunc();
                return 0;
            } catch (...) {
                ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")\nPlease update this DLL");
				return -1;
            }
        }
        else
		 {
			 ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")");
			 return -1;
		 }
    }
    else
    {
        return -1;
    }
}

int KeyboardAttachToForm(HWND formHandle, bool autoHide)
{
	HINSTANCE load;
	wchar_t Ch[500], Ch1[500];
	LPCSTR functionName = "KeyboardAttachToForm";

	Wstrcpy(Ch, Application->ExeName.c_str());
	Wstrcpy(Ch1, dirClavierVirtuel.c_str());
	Ch1[0] = Ch[0];
	load = LoadLibrary(Ch1);
	if (load)
	{
        // GetProcAddress returns a pointer to the loaded method
    	FuncKeyboardToFormAttach myFunc = FuncKeyboardToFormAttach(GetProcAddress(load, functionName));

        if (myFunc != nullptr) {
            try {
                myFunc(formHandle, autoHide);
                return 0;
            } catch (...) {
                ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")\nPlease update this DLL");
				return -1;
            }
        }
        else
		 {
			 ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")");
			 return -1;
		 }
    }
    else
    {
        return -1;
    }
}

int KeyboardDetachFromForm(HWND formHandle)
{
	HINSTANCE load;
	wchar_t Ch[500], Ch1[500];
	LPCSTR functionName = "KeyboardDetachFromForm";

	Wstrcpy(Ch, Application->ExeName.c_str());
	Wstrcpy(Ch1, dirClavierVirtuel.c_str());
	Ch1[0] = Ch[0];
	load = LoadLibrary(Ch1);
	if (load)
	{
        // GetProcAddress returns a pointer to the loaded method
    	FuncKeyboardFromFormDetach myFunc = FuncKeyboardFromFormDetach(GetProcAddress(load, functionName));

        if (myFunc != nullptr) {
            try {
                myFunc(formHandle);
                return 0;
            } catch (...) {
                ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")\nPlease update this DLL");
				return -1;
            }
        }
        else
		 {
			 ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")");
			 return -1;
		 }
    }
    else
    {
        return -1;
    }
}

int KeyboardAutoShow(HWND hwnd)
{
	HINSTANCE load;
	wchar_t Ch[500], Ch1[500];
	LPCSTR functionName = "KeyboardAutoShow";

	Wstrcpy(Ch, Application->ExeName.c_str());
	Wstrcpy(Ch1, dirClavierVirtuel.c_str());
	Ch1[0] = Ch[0];
	load = LoadLibrary(Ch1);
	if (load)
	{
        // GetProcAddress returns a pointer to the loaded method
    	FuncKeyboardAutoShow myFunc = FuncKeyboardAutoShow(GetProcAddress(load, functionName));

        if (myFunc != nullptr) {
            try {
                myFunc(hwnd);
                return 0;
            } catch (...) {
                ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")\nPlease update this DLL");
				return -1;
            }
        }
        else
		 {
			 ShowMessage("Function (" + UnicodeString(functionName) + ") not found in the DLL (" + dirClavierVirtuel + ")");
			 return -1;
		 }
    }
    else
    {
        return -1;
    }
}

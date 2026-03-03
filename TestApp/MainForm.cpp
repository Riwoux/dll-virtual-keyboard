//---------------------------------------------------------------------------
// MainForm.cpp - Simple Test Application Implementation
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Edit_Int"
#pragma resource "*.dfm"
TFormMain *FormMain;


// Début modif 023 CL
typedef void* (*FuncKeyboardShow)(TObject* Sender);
typedef void* (*FuncKeyboardHide)();
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
    Edit1->OnEnter = AutoShow;
    Edit1->OnExit = AutoHide;
    Edit2->OnEnter = AutoShow;
    Edit2->OnExit = AutoHide;
    Edit_Int1->OnEnter = AutoShow;
    Edit_Int1->OnExit = AutoHide;
    Memo1->OnEnter = AutoShow;
    Memo1->OnExit = AutoHide;
}

void __fastcall TFormMain::AutoShow(TObject *Sender)
{
    KeyboardShow(Sender);
}

void __fastcall TFormMain::AutoHide(TObject *Sender)
{
    KeyboardHide();
}

int KeyboardShow(TObject* Sender)
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
                myFunc(Sender);
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

int KeyboardHide(void)
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


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

//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner):
	TForm(Owner), FDllHandle(NULL), FShowKeyboard(NULL), FHideKeyboard(NULL),
    FAttachKeyboardToForm(NULL), FDetachKeyboardFromForm(NULL)
{
}

//---------------------------------------------------------------------------
// Form creation event
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    if (!LoadKeyboardDLL()) {
        ShowMessage("Error: Cannot load touchkeyboard.dll\n");
    }
    Edit1->OnEnter = TextControlEnter;
    Edit2->OnEnter = TextControlEnter;
    if (FAttachKeyboardToForm) {
        FAttachKeyboardToForm(Handle, true);
    }
}

//---------------------------------------------------------------------------
// Form destruction event
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    if (FDetachKeyboardFromForm) {
        FDetachKeyboardFromForm(Handle);
    }
    UnloadKeyboardDLL();
}

///---------------------------------------------------------------------------
// Load the virtual keyboard DLL
//---------------------------------------------------------------------------
bool TFormMain::LoadKeyboardDLL()
{
    // First try to load from application directory
    String dllPath = ExtractFilePath(Application->ExeName) + "touchkeyboard.dll";
    FDllHandle = LoadLibraryW(dllPath.w_str());

    if (!FDllHandle) {
        FDllHandle = LoadLibrary(TEXT("touchkeyboard.dll"));
    }

    if (!FDllHandle) {
        DWORD errCode = GetLastError();
        ShowMessage("Failed to load touchkeyboard.dll\nError code: " + IntToStr((int)errCode));
        return false;
    }

    // DLL loaded successfully, now get the exported functions
    FShowKeyboard = (TShowKeyboardProc)GetProcAddress(FDllHandle, "ShowKeyboard");
    FHideKeyboard = (THideKeyboardProc)GetProcAddress(FDllHandle, "HideKeyboard");
    FAttachKeyboardToForm = (TAttachKeyboardToFormProc)GetProcAddress(FDllHandle, "AttachKeyboardToForm");
    FDetachKeyboardFromForm = (TDetachKeyboardFromFormProc)GetProcAddress(FDllHandle, "DetachKeyboardFromForm");

    if (!FShowKeyboard || !FHideKeyboard || !FAttachKeyboardToForm) {
        ShowMessage("DLL loaded but functions not found!");
        UnloadKeyboardDLL();
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
// Unload the DLL
//---------------------------------------------------------------------------
void TFormMain::UnloadKeyboardDLL()
{
    if (FDllHandle) {
    	FreeLibrary(FDllHandle);
        FDllHandle = NULL;
        FShowKeyboard = NULL;
        FHideKeyboard = NULL;
        FAttachKeyboardToForm = NULL;
        FDetachKeyboardFromForm = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TextControlEnter(TObject *Sender)
{
    TWinControl *ctrl = dynamic_cast<TWinControl*>(Sender);
    if (!ctrl || !FShowKeyboard) return;

    int layout = -1;  // Standard par défaut

    // Vérifier si c'est un Edit numérique
    TEdit *edit = dynamic_cast<TEdit*>(Sender);
    if (edit && edit->NumbersOnly) {
        layout = 0;  // NumPad
    }

    FShowKeyboard(ctrl->Handle, layout);
}

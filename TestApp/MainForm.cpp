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
}                                                                             

//---------------------------------------------------------------------------
// Form creation event
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    if (!LoadKeyboardDLL()) {
        ShowMessage("Error: Cannot load touchkeyboard.dll\n");
    }
    if (FAttachKeyboardToForm) {
        FAttachKeyboardToForm(Handle, false);
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
// Show keyboard button click
//---------------------------------------------------------------------------
void __fastcall TFormMain::BtnShowClick(TObject *Sender)
{
    if (FShowKeyboard) {
        FShowKeyboard(MemoTest->Handle);
    }
}

//---------------------------------------------------------------------------
// Hide keyboard button click
//---------------------------------------------------------------------------
void __fastcall TFormMain::BtnHideClick(TObject *Sender)
{
    if (FHideKeyboard) {
        FHideKeyboard();
    }
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
    if (FShowKeyboard) {
        FShowKeyboard(MemoTest->Handle,0);
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// MainForm.cpp - Simple Test Application Implementation
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;

//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner), FDllHandle(NULL), FShowKeyboard(NULL),
      FHideKeyboard(NULL), FIsKeyboardVisible(NULL)
{
}

//---------------------------------------------------------------------------
// Form creation event
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    if (!LoadKeyboardDLL()) {
        ShowMessage("Error: Cannot load VirtualKeyboardDLL.dll\n\n"
                   "Make sure the DLL file is in the same directory "
                   "as the application or in the system PATH.");
        BtnShow->Enabled = false;
        BtnHide->Enabled = false;
    }
}

//---------------------------------------------------------------------------
// Form destruction event
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    UnloadKeyboardDLL();
}

//---------------------------------------------------------------------------
// Load the virtual keyboard DLL
//---------------------------------------------------------------------------
bool TFormMain::LoadKeyboardDLL()
{
    // First try to load from application directory
    String dllPath = ExtractFilePath(Application->ExeName) + "VirtualKeyboardDLL.dll";
    FDllHandle = LoadLibrary(dllPath.c_str());
    
    if (!FDllHandle) {
        // Try to load from system PATH
        FDllHandle = LoadLibrary(L"VirtualKeyboardDLL.dll");
    }
    
    if (!FDllHandle) {
        return false;
    }
    
    // Load exported functions
    FShowKeyboard = (TShowKeyboardProc)GetProcAddress(FDllHandle, "ShowKeyboard");
    FHideKeyboard = (THideKeyboardProc)GetProcAddress(FDllHandle, "HideKeyboard");
    FIsKeyboardVisible = (TIsKeyboardVisibleProc)GetProcAddress(FDllHandle, "IsKeyboardVisible");
    
    if (!FShowKeyboard || !FHideKeyboard || !FIsKeyboardVisible) {
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
        FIsKeyboardVisible = NULL;
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

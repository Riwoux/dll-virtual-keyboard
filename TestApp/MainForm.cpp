//---------------------------------------------------------------------------
// MainForm.cpp - Implémentation du formulaire principal de test
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;

//---------------------------------------------------------------------------
// Constructeur
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner), FDllHandle(NULL), FShowKeyboard(NULL),
      FHideKeyboard(NULL), FIsKeyboardVisible(NULL), FSetKeyboardMode(NULL)
{
}

//---------------------------------------------------------------------------
// Événement de création du formulaire
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    if (!LoadKeyboardDLL()) {
        ShowMessage("Erreur: Impossible de charger VirtualKeyboardDLL.dll\n\n"
                   "Assurez-vous que le fichier DLL est présent dans le même répertoire "
                   "que l'application ou dans le PATH système.");
        BtnShowSimple->Enabled = false;
        BtnShowWithNumpad->Enabled = false;
        BtnHide->Enabled = false;
    }
    UpdateStatus();
}

//---------------------------------------------------------------------------
// Événement de destruction du formulaire
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    UnloadKeyboardDLL();
}

//---------------------------------------------------------------------------
// Charger la DLL du clavier virtuel
//---------------------------------------------------------------------------
bool TFormMain::LoadKeyboardDLL()
{
    // Chercher d'abord dans le répertoire de l'application
    String dllPath = ExtractFilePath(Application->ExeName) + "VirtualKeyboardDLL.dll";
    FDllHandle = LoadLibrary(dllPath.c_str());
    
    if (!FDllHandle) {
        // Essayer de charger depuis le PATH système
        FDllHandle = LoadLibrary(L"VirtualKeyboardDLL.dll");
    }
    
    if (!FDllHandle) {
        return false;
    }
    
    // Charger les fonctions exportées
    FShowKeyboard = (TShowKeyboardProc)GetProcAddress(FDllHandle, "ShowKeyboard");
    FHideKeyboard = (THideKeyboardProc)GetProcAddress(FDllHandle, "HideKeyboard");
    FIsKeyboardVisible = (TIsKeyboardVisibleProc)GetProcAddress(FDllHandle, "IsKeyboardVisible");
    FSetKeyboardMode = (TSetKeyboardModeProc)GetProcAddress(FDllHandle, "SetKeyboardMode");
    
    if (!FShowKeyboard || !FHideKeyboard || !FIsKeyboardVisible || !FSetKeyboardMode) {
        UnloadKeyboardDLL();
        return false;
    }
    
    return true;
}

//---------------------------------------------------------------------------
// Décharger la DLL
//---------------------------------------------------------------------------
void TFormMain::UnloadKeyboardDLL()
{
    if (FDllHandle) {
        FreeLibrary(FDllHandle);
        FDllHandle = NULL;
        FShowKeyboard = NULL;
        FHideKeyboard = NULL;
        FIsKeyboardVisible = NULL;
        FSetKeyboardMode = NULL;
    }
}

//---------------------------------------------------------------------------
// Mettre à jour l'état
//---------------------------------------------------------------------------
void TFormMain::UpdateStatus()
{
    if (FIsKeyboardVisible && FIsKeyboardVisible()) {
        LabelStatus->Caption = "État: Clavier visible";
    } else {
        LabelStatus->Caption = "État: Clavier masqué";
    }
}

//---------------------------------------------------------------------------
// Afficher le clavier simple (Mode 0)
//---------------------------------------------------------------------------
void __fastcall TFormMain::BtnShowSimpleClick(TObject *Sender)
{
    if (FShowKeyboard) {
        FShowKeyboard(0, MemoTest->Handle);
        UpdateStatus();
    }
}

//---------------------------------------------------------------------------
// Afficher le clavier avec pavé numérique (Mode 1)
//---------------------------------------------------------------------------
void __fastcall TFormMain::BtnShowWithNumpadClick(TObject *Sender)
{
    if (FShowKeyboard) {
        FShowKeyboard(1, MemoTest->Handle);
        UpdateStatus();
    }
}

//---------------------------------------------------------------------------
// Masquer le clavier
//---------------------------------------------------------------------------
void __fastcall TFormMain::BtnHideClick(TObject *Sender)
{
    if (FHideKeyboard) {
        FHideKeyboard();
        UpdateStatus();
    }
}

//---------------------------------------------------------------------------

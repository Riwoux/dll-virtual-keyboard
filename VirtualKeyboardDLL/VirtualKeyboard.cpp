//---------------------------------------------------------------------------
// VirtualKeyboard.cpp - Point d'entrée de la DLL et implémentation des exports
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused

#include "VirtualKeyboard.h"
#include "KeyboardForm.h"
//---------------------------------------------------------------------------
// Directive USEFORM pour C++ Builder - nécessaire pour lier le formulaire à la DLL
#pragma link "KeyboardForm"
//---------------------------------------------------------------------------
// Variables globales
//---------------------------------------------------------------------------
static TFormKeyboard* g_KeyboardForm = NULL;

//---------------------------------------------------------------------------
// Point d'entrée de la DLL
// Utilise DllMain pour compatibilité C++ Builder 13 / RAD Studio 12 Athens
//---------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID lpReserved)
{
    try {
        if (reason == DLL_PROCESS_ATTACH) {
            // Initialisation de la DLL
        } else if (reason == DLL_PROCESS_DETACH) {
            // Nettoyage
            if (g_KeyboardForm) {
                delete g_KeyboardForm;
                g_KeyboardForm = NULL;
            }
        }
    } catch (...) {
        return FALSE;
    }
    return TRUE;
}

//---------------------------------------------------------------------------
// Show the virtual keyboard
// targetHandle: HWND of target control to receive characters
//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle)
{
    try {
        if (!g_KeyboardForm) {
            Application->Initialize();
            Application->CreateForm(__classid(TFormKeyboard), &g_KeyboardForm);
        }
        
        if (g_KeyboardForm) {
            g_KeyboardForm->SetTargetHandle(targetHandle);
            g_KeyboardForm->Show();
        }
    } catch (...) {
        // Silent error handling
    }
}

//---------------------------------------------------------------------------
// Masquer le clavier virtuel
//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) void __stdcall HideKeyboard()
{
    try {
        if (g_KeyboardForm) {
            g_KeyboardForm->Hide();
        }
    } catch (...) {
        // Gestion des erreurs silencieuse
    }
}

//---------------------------------------------------------------------------
// Vérifier si le clavier est visible
//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) bool __stdcall IsKeyboardVisible()
{
    try {
        if (g_KeyboardForm) {
            return g_KeyboardForm->Visible;
        }
    } catch (...) {
        // Gestion des erreurs silencieuse
    }
    return false;
}

//---------------------------------------------------------------------------

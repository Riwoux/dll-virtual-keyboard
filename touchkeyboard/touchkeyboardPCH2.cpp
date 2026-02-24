//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include <commctrl.h>
#include <map>
#include "clavier.h"
#include "touchkeyboardPCH2.h"

#pragma hdrstop
#pragma argsused

// Pour le sous-classement
#pragma comment(lib, "comctl32.lib")

//---------------------------------------------------------------------------
// Structures pour gérer les contrôles sous-classés
//---------------------------------------------------------------------------
struct ControlInfo {
    HWND hwnd;
    bool isNumeric;
};

// Map pour stocker les infos des contrôles sous-classés
static std::map<HWND, ControlInfo> g_AttachedControls;
static bool g_AutoHide = true;

//---------------------------------------------------------------------------
// Identifie si un contrôle est une zone de texte
//---------------------------------------------------------------------------
bool IsTextControl(HWND hwnd)
{
    wchar_t className[256];
    GetClassNameW(hwnd, className, 256);

    // Classes de contrôles de texte Windows/VCL
    return (wcscmp(className, L"Edit") == 0 ||
            wcscmp(className, L"RichEdit") == 0 ||
            wcscmp(className, L"RichEdit20A") == 0 ||
            wcscmp(className, L"RichEdit20W") == 0 ||
            wcscmp(className, L"TMemo") == 0 ||
            wcscmp(className, L"TEdit") == 0 ||
            wcscmp(className, L"TRichEdit") == 0 ||
            wcsstr(className, L"Edit") != NULL);  // Attrape aussi d'autres variantes
}

//---------------------------------------------------------------------------
// Vérifie si un Edit est en mode numérique
//---------------------------------------------------------------------------
bool IsNumericControl(HWND hwnd)
{
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    return (style & ES_NUMBER) != 0;  // Style ES_NUMBER
}

//---------------------------------------------------------------------------
// Procédure de sous-classement pour intercepter les messages
//---------------------------------------------------------------------------
LRESULT CALLBACK SubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                              UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
        case WM_SETFOCUS:  // Le contrôle reçoit le focus
        {
            auto it = g_AttachedControls.find(hwnd);
            if (it != g_AttachedControls.end()) {
                int layout = it->second.isNumeric ? 0 : -1;  // 0 = NumPad, -1 = Standard
                ShowKeyboard(hwnd, layout);
            }
            break;
        }

        case WM_KILLFOCUS:  // Le contrôle perd le focus
        {
            if (g_AutoHide) {
                HideKeyboard();
            }
            break;
        }

        case WM_DESTROY:  // Le contrôle est détruit
        {
            // Nettoyer le sous-classement
            RemoveWindowSubclass(hwnd, SubclassProc, uIdSubclass);
            g_AttachedControls.erase(hwnd);
            break;
        }
    }

    // Appeler la procédure par défaut
    return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}

//---------------------------------------------------------------------------
// Callback pour énumérer les contrôles enfants
//---------------------------------------------------------------------------
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    if (IsTextControl(hwnd)) {
        // Vérifier si déjà attaché
        if (g_AttachedControls.find(hwnd) == g_AttachedControls.end()) {
            // Sous-classer le contrôle
            SetWindowSubclass(hwnd, SubclassProc, 0, 0);

            // Enregistrer les infos
            ControlInfo info;
            info.hwnd = hwnd;
            info.isNumeric = IsNumericControl(hwnd);

            g_AttachedControls[hwnd] = info;
        }
    }

    return TRUE;  // Continuer l'énumération
}

//---------------------------------------------------------------------------
// Point d'entrée de la DLL
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    if (reason == DLL_PROCESS_DETACH) {
        // Nettoyer tous les sous-classements
        for (auto& pair : g_AttachedControls) {
            RemoveWindowSubclass(pair.first, SubclassProc, 0);
        }
        g_AttachedControls.clear();
    }
    return 1;
}

//---------------------------------------------------------------------------
void InitKeyboard(void)
{
    if (!keyboard)
    {
        Application->CreateForm(__classid(Tkeyboard), &keyboard);
    }
}

//---------------------------------------------------------------------------
// Fonctions exportées
//---------------------------------------------------------------------------
extern "C"
{
    __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle, int etat)
    {
        try {
            if (!keyboard) {
                Application->Initialize();
                Application->CreateForm(__classid(Tkeyboard), &keyboard);
            }

            if (keyboard) {
                keyboard->Etat(etat);
                keyboard->SetTargetControl(targetHandle);
                keyboard->Show();
            }
        } catch (...) {
        }
    }

    __declspec(dllexport) void __stdcall HideKeyboard(void)
    {
        try {
            if (keyboard) {
                keyboard->Hide();
            }
        } catch (...) {
        }
    }

    __declspec(dllexport) void __stdcall AttachKeyboardToForm(HWND formHandle, bool autoHide)
    {
        if (!formHandle || !::IsWindow(formHandle)) return;

        g_AutoHide = autoHide;

        // Énumérer tous les contrôles enfants du formulaire
        ::EnumChildWindows(formHandle, EnumChildProc, 0);
    }

    __declspec(dllexport) void __stdcall DetachKeyboardFromForm(HWND formHandle)
    {
        if (!formHandle || !::IsWindow(formHandle)) return;

        // Parcourir tous les contrôles attachés
        auto it = g_AttachedControls.begin();
        while (it != g_AttachedControls.end()) {
            HWND parent = ::GetParent(it->first);
            if (parent == formHandle) {
                // Enlever le sous-classement
                RemoveWindowSubclass(it->first, SubclassProc, 0);
                it = g_AttachedControls.erase(it);
            } else {
                ++it;
            }
        }
    }
}
//---------------------------------------------------------------------------

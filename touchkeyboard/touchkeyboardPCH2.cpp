//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include <commctrl.h>
#include <map>
#include "clavier.h"
#include "touchkeyboardPCH2.h"

#pragma hdrstop
#pragma argsused
#pragma comment(lib, "comctl32.lib")

//---------------------------------------------------------------------------
struct ControlInfo {
    HWND hwnd;
    bool isNumeric;
};

static std::map<HWND, ControlInfo> g_AttachedControls;
static bool g_AutoHide = true;
static int g_ControlsFound = 0;  // ← Compteur de diagnostic

//---------------------------------------------------------------------------
bool IsTextControl(HWND hwnd)
{
    wchar_t className[256];
    GetClassNameW(hwnd, className, 256);

    return (wcscmp(className, L"Edit") == 0 ||
            wcscmp(className, L"RichEdit") == 0 ||
            wcscmp(className, L"RichEdit20A") == 0 ||
            wcscmp(className, L"RichEdit20W") == 0 ||
            wcscmp(className, L"TMemo") == 0 ||
            wcscmp(className, L"TEdit") == 0 ||
            wcscmp(className, L"TRichEdit") == 0 ||
            wcsstr(className, L"Edit") != NULL);
}

//---------------------------------------------------------------------------
bool IsNumericControl(HWND hwnd)
{
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    return (style & ES_NUMBER) != 0;
}

//---------------------------------------------------------------------------
LRESULT CALLBACK SubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                              UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
        case WM_SETFOCUS:
        {
            // ← DIAGNOSTIC
            MessageBoxW(NULL, L"WM_SETFOCUS reçu!", L"Debug", MB_OK);

            auto it = g_AttachedControls.find(hwnd);
            if (it != g_AttachedControls.end()) {
                int layout = it->second.isNumeric ? 0 : -1;
                ShowKeyboard(hwnd, layout);
            }
            break;
        }

        case WM_KILLFOCUS:
        {
            if (g_AutoHide) {
                HideKeyboard();
            }
            break;
        }

        case WM_DESTROY:
        {
            RemoveWindowSubclass(hwnd, SubclassProc, uIdSubclass);
            g_AttachedControls.erase(hwnd);
            break;
        }
    }

    return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}

//---------------------------------------------------------------------------
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    wchar_t className[256];
    GetClassNameW(hwnd, className, 256);

    g_ControlsFound++;  // ← Compteur

    if (IsTextControl(hwnd)) {
        if (g_AttachedControls.find(hwnd) == g_AttachedControls.end()) {
            SetWindowSubclass(hwnd, SubclassProc, 0, 0);

            ControlInfo info;
            info.hwnd = hwnd;
            info.isNumeric = IsNumericControl(hwnd);

            g_AttachedControls[hwnd] = info;
        }
    }

    return TRUE;
}

//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    if (reason == DLL_PROCESS_DETACH) {
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
        if (!formHandle || !::IsWindow(formHandle)) {
            MessageBoxW(NULL, L"formHandle invalide!", L"Erreur", MB_OK | MB_ICONERROR);
            return;
        }

        g_AutoHide = autoHide;
        g_ControlsFound = 0;  // Reset compteur

        // Énumérer tous les contrôles enfants
        ::EnumChildWindows(formHandle, EnumChildProc, 0);

        // ← DIAGNOSTIC : Afficher le résultat
        wchar_t msg[256];
        swprintf(msg, 256, L"Contrôles trouvés : %d\nContrôles attachés : %d",
                 g_ControlsFound, (int)g_AttachedControls.size());
        MessageBoxW(NULL, msg, L"AttachKeyboardToForm", MB_OK | MB_ICONINFORMATION);
    }

    __declspec(dllexport) void __stdcall DetachKeyboardFromForm(HWND formHandle)
    {
        if (!formHandle || !::IsWindow(formHandle)) return;

        auto it = g_AttachedControls.begin();
        while (it != g_AttachedControls.end()) {
            HWND parent = ::GetParent(it->first);
            if (parent == formHandle) {
                RemoveWindowSubclass(it->first, SubclassProc, 0);
                it = g_AttachedControls.erase(it);
            } else {
                ++it;
            }
        }
    }
}
//---------------------------------------------------------------------------

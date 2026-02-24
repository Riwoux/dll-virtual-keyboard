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

//fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
static HWND  g_CurrentTarget = NULL;
static HHOOK g_MouseHook     = NULL;
//fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
static bool IsPointInsideWindow(HWND hwnd, const POINT& ptScreen)
{
    if (!hwnd) return false;
    RECT rc{};
    if (!GetWindowRect(hwnd, &rc)) return false;
    return PtInRect(&rc, ptScreen) != 0;
}


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
                HWND newFocus = (HWND)wParam;

                if (g_AttachedControls.find(newFocus) == g_AttachedControls.end()) {
                    HideKeyboard();
                }
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

 //fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        // On s'intéresse aux clics (client et non-client)
        if (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN || wParam == WM_MBUTTONDOWN ||
            wParam == WM_NCLBUTTONDOWN || wParam == WM_NCRBUTTONDOWN || wParam == WM_NCMBUTTONDOWN)
        {
            MOUSEHOOKSTRUCT* mhs = reinterpret_cast<MOUSEHOOKSTRUCT*>(lParam);
            POINT pt = mhs->pt; // coordonnées écran

            // Si le clic est en dehors de l'edit actuellement ciblé -> on cache le clavier
            if (g_CurrentTarget && !IsPointInsideWindow(g_CurrentTarget, pt))
            {
                HideKeyboard();
            }
        }
    }
    return CallNextHookEx(g_MouseHook, nCode, wParam, lParam);
}

//---------------------------------------------------------------------------
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    wchar_t className[256];
    GetClassNameW(hwnd, className, 256);


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

        //fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
        if (g_MouseHook) {
                UnhookWindowsHookEx(g_MouseHook);
                g_MouseHook = NULL;
        }

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
                g_CurrentTarget = targetHandle; //fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
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

        // Énumérer tous les contrôles enfants
        ::EnumChildWindows(formHandle, EnumChildProc, 0);

        //fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
        if (!g_MouseHook) {
                g_MouseHook = SetWindowsHookEx(WH_MOUSE, MouseHookProc, NULL, GetCurrentThreadId());
        }


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

        //fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
        if (g_AttachedControls.empty() && g_MouseHook) {
                UnhookWindowsHookEx(g_MouseHook);
                g_MouseHook = NULL;
        }

    }
}
//---------------------------------------------------------------------------

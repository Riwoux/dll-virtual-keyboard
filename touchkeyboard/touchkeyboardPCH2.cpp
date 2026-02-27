//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include <commctrl.h>
#include <map>
#include "clavier.h"
#include "touchkeyboardPCH2.h"

#pragma hdrstop
#pragma argsused
#pragma comment(lib, "comctl32")


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
static HWND g_KeyboardHwnd = NULL;
static bool g_KeyboardVisible = false;

//---------------------------------------------------------------------------

//fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
static bool IsPointInsideWindow(HWND hwnd, const POINT& ptScreen)
{
	if (!hwnd) return false;
	RECT rc{};
	if (!GetWindowRect(hwnd, &rc)) return false;
	return PtInRect(&rc, ptScreen) != 0;
}

static bool IsInKeyboardWindow(HWND hwnd)
{
	if (!hwnd) return false;
    if (!keyboard) return false;
    HWND kb = keyboard->Handle;
    if (!kb || !::IsWindow(kb)) return false;

	if (hwnd == kb) return true;
	if (::IsChild(kb, hwnd)) return true;

    HWND root = (HWND)::GetAncestor(hwnd, GA_ROOT);
    return (root == kb);
}

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

bool IsNumericControl(HWND hwnd)
{
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
    return (style & ES_NUMBER) != 0;
}

// gère les focus en jouant avec l'apparation du clavier
LRESULT CALLBACK SubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
							  UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (uMsg)
	{
        // afficher le clavier et le mettre au premier plan
		case WM_SETFOCUS:
		{
			auto it = g_AttachedControls.find(hwnd);
			if (it != g_AttachedControls.end()) {
				LONG st = GetWindowLongW(hwnd, GWL_STYLE);
                const bool isNum = (st & ES_NUMBER) != 0;
				KeyboardShow(hwnd, isNum ? 0: -1);
			}
            break;
        }
        // caché le clavier
        case WM_KILLFOCUS:
		{
			if (g_AutoHide) {
                HWND newFocus = (HWND)wParam;
		       	if (IsInKeyboardWindow(newFocus)) {
					break;
        		}
				if (g_AttachedControls.find(newFocus) == g_AttachedControls.end()) {
                    KeyboardHide();
				}
            }
            break;
		}
        // détruire les gestions de focus
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
 // Recupere le focus en dessous di clique de la souris
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN || wParam == WM_MBUTTONDOWN ||
            wParam == WM_NCLBUTTONDOWN || wParam == WM_NCRBUTTONDOWN || wParam == WM_NCMBUTTONDOWN)
        {
            MOUSEHOOKSTRUCT* mhs = reinterpret_cast<MOUSEHOOKSTRUCT*>(lParam);
            POINT pt = mhs->pt;
			HWND hwndHit = ::WindowFromPoint(pt);

            // si on est dans le clavier -> ne rien faire
			if (IsInKeyboardWindow(hwndHit)) {
				return CallNextHookEx(g_MouseHook, nCode, wParam, lParam);
			}

            // si un focus est défini, recuperer ses parametres et afficher le clavier en conséquences
			if (g_CurrentTarget) {
                if (IsPointInsideWindow(g_CurrentTarget, pt)) {
                    if (!g_KeyboardVisible) {
                        int layout = -1;
                        auto it = g_AttachedControls.find(g_CurrentTarget);
                        if (it != g_AttachedControls.end()) layout = it->second.isNumeric ? 0 : -1;
                        KeyboardShow(g_CurrentTarget, layout);
                    }
                    return CallNextHookEx(g_MouseHook, nCode, wParam, lParam);
                }
                KeyboardHide();
            }
        }
    }
    return CallNextHookEx(g_MouseHook, nCode, wParam, lParam);
}

// identifie et mémorise les informations de la fenetre
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    if (IsTextControl(hwnd)) {
        if (g_AttachedControls.find(hwnd) == g_AttachedControls.end()) {
            SetWindowSubclass(hwnd, SubclassProc, 0, 0);
            ControlInfo info;
            info.hwnd = hwnd;
            info.isNumeric = IsNumericControl(hwnd);
            g_AttachedControls[hwnd] = info;
        }
    }
    // TRUE -> continue l'énumération
    return TRUE;
}
// appelé automatiquement par windows lors de l'utilisation de la DLL
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    // lors de l'arret de l'utilisation de la DLL il va enlever ses pocédures de controle des fenetres
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

void InitKeyboard(void)
{
    if (!keyboard)
    {
        Application->CreateForm(__classid(Tkeyboard), &keyboard);
    }
}

extern "C"
{
    __declspec(dllexport) void __stdcall KeyboardShow(HWND targetHandle, int etat)
    {
        try {
            if (!keyboard) {
                Application->Initialize();
                Application->CreateForm(__classid(Tkeyboard), &keyboard);
            }

            // prend le focus sur le clavier et l'affiche en le mettant au premier plan
            if (keyboard) {
				g_CurrentTarget = targetHandle; //fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
                g_KeyboardHwnd  = keyboard->Handle;
                keyboard->Etat(etat);
                keyboard->SetTargetControl(targetHandle);
                keyboard->Show();
                g_KeyboardVisible = true;
            }
		} catch (...) {
        }
    }

    __declspec(dllexport) void __stdcall KeyboardHide(void)
    {
        try {
            if (keyboard) {
                keyboard->Hide();
                g_KeyboardVisible = false;
            }
        } catch (...) {
        }
    }

    // initialise le fonctionnement du jeu de focus entre fenetres
    __declspec(dllexport) void __stdcall KeyboardAttachToForm(HWND formHandle, bool autoHide)
    {
        if (!formHandle || !::IsWindow(formHandle)) {
            MessageBoxW(NULL, L"formHandle invalide!", L"Erreur", MB_OK | MB_ICONERROR);
            return;
        }
        g_AutoHide = autoHide;
        // Énumérer tous les contrôles enfants pour gérer toutes les fenetres
        ::EnumChildWindows(formHandle, EnumChildProc, 0);
        //fais partis du principe de cacher le clavier lorsque que la souris clique en dehors de la zone
        if (!g_MouseHook) {
                g_MouseHook = SetWindowsHookEx(WH_MOUSE, MouseHookProc, NULL, GetCurrentThreadId());
        }


    }

    // Suprimme les controles du jeu de focus entre fenetres
    __declspec(dllexport) void __stdcall KeyboardDetachFromForm(HWND formHandle)
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

    // fonction a appeler lors d'évenement comme OnEnter pour afficher le clavier
    __declspec(dllexport) void __stdcall KeyboardAutoShow(HWND hwnd)
    {
        try {
            if (!hwnd || !::IsWindow(hwnd)) return;

            if (!IsTextControl(hwnd)) return;

            bool isNumeric = IsNumericControl(hwnd);
            int layout = isNumeric ? 0 : -1;
            KeyboardShow(hwnd, layout);
        } catch (...) {
        }
    }


}

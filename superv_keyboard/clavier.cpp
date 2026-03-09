//   Remarque importante sur la gestion mémoire de la DLL quand votre DLL utilise la
//   version statique de la bibliothèque d'exécution (RTL) :
//
//   Si votre DLL exporte des fonctions qui passent des objets chaîne (ou des classes structs/
//   contenant des chaînes imbriquées) par le biais de paramètres ou de résultats de fonctions,
//   vous devrez ajouter la bibliothèque MEMMGR.LIB au projet DLL et aux autres
//   projets qui utilisent la DLL.  Il sera aussi nécessaire d'utiliser MEMMGR.LIB
//   si d'autres projets utilisant la DLL effectuent des opérations new ou delete
//   sur des classes ne dérivant pas de TObject qui sont exportées depuis la
//   DLL. Ajouter MEMMGR.LIB à votre projet changera la DLL et son EXE appelant
//   afin d'utiliser BORLNDMM.DLL en tant que gestionnaire de mémoire.  Dans ces cas,
//   le fichier BORLNDMM.DLL doit être déployé avec votre DLL.
//
//   Pour éviter l'emploi de BORLNDMM.DLL, passez des informations chaîne par
//   le biais de paramètres "char *" ou ShortString.
//
//   Si votre DLL utilise la version dynamique de la RTL, il n'est pas nécessaire
//   d'ajouter explicitement MEMMGR.LIB car cela sera fait implicitement.
//   Si votre DLL utilise la version statique de la RTL, ajoutez #include<usebormm.h>
//   à l'un des fichiers source pour votre DLL
//---------------------------------------------------------------------------
#include "clavier1.h"
#include <vcl.h>
#include <windows.h>
#include <System.Rtti.hpp>

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma argsused

//---------------------------------------------------------------------------
TFVirtualKeyboard *FVirtualKeyboard = NULL;

//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    try
    {
        if (reason == DLL_PROCESS_ATTACH)
        {
        }
        else if (reason == DLL_PROCESS_DETACH)
        {
            if (FVirtualKeyboard)
            {
                delete FVirtualKeyboard;
                FVirtualKeyboard = NULL;
            }
        }
    }
    catch (Exception &exception)
    {
        return 0;
    }
    catch (...)
    {
        return 0;
    }
    return 1;
}
//---------------------------------------------------------------------------
bool NumberStatus(TObject* Obj)
{
    if (Obj == NULL) {
        return false;
    }
    try {
        TWinControl* WinCtrl = static_cast<TWinControl*>(Obj);
        if (WinCtrl && WinCtrl->HandleAllocated()) {
            int style = GetWindowLongW(WinCtrl->Handle, GWL_STYLE); // récupère le type de l'objet
            return (style & ES_NUMBER) != 0;
        }
    } catch (...) {
        return false;
    }
    return false;
}
//---------------------------------------------------------------------------
HWND GetTargetWindowFromSender(TObject* Sender)
{
    // 1. Essayer de récupérer depuis le Sender (si c'est un TWinControl)
    if (Sender)
    {
        TWinControl* WinCtrl = dynamic_cast<TWinControl*>(Sender);
        if (WinCtrl && WinCtrl->HandleAllocated())
        {
            return WinCtrl->Handle;
        }
    }

    // 2. Fallback : récupérer la fenêtre active avec GetGUIThreadInfo
    HWND hActiveWindow = GetForegroundWindow();
    if (hActiveWindow)
    {
        GUITHREADINFO gti = {0};
        gti.cbSize = sizeof(GUITHREADINFO);

        DWORD dwThread = GetWindowThreadProcessId(hActiveWindow, NULL);
        if (GetGUIThreadInfo(dwThread, &gti))
        {
            if (gti.hwndFocus && IsWindow(gti.hwndFocus))
            {
                return gti.hwndFocus;
            }
        }
    }

    return hActiveWindow;
}
//---------------------------------------------------------------------------
void CalculateAutoPosition(HWND hTarget, int keyboardWidth, int keyboardHeight,
                           int offsetY, int* outLeft, int* outTop)
{
    // Valeurs par défaut
    *outLeft = 700;
    *outTop = 500;

    if (!hTarget || !IsWindow(hTarget))
        return;

    // Récupérer la position du contrôle à l'écran
    RECT rect;
    GetWindowRect(hTarget, &rect);

    // Position initiale : sous le contrôle
    int left = rect.left;
    int top = rect.bottom + offsetY;

    // Gestion multi-moniteurs
    HMONITOR hMonitor = MonitorFromWindow(hTarget, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = {0};
    mi.cbSize = sizeof(MONITORINFO);

    if (GetMonitorInfo(hMonitor, &mi))
    {
        RECT wa = mi.rcWork;  // Zone de travail (sans barre des tâches)

        // Si déborde en bas, placer au-dessus
        if (top + keyboardHeight > wa.bottom)
        {
            top = rect.top - keyboardHeight - offsetY;

            // Si déborde encore en haut, forcer en bas de l'écran
            if (top < wa.top)
            {
                top = wa.bottom - keyboardHeight - 10;
            }
        }

        // Ajustements horizontaux
        if (left + keyboardWidth > wa.right)
        {
            left = wa.right - keyboardWidth - 10;
        }
        if (left < wa.left)
        {
            left = wa.left + 10;
        }
    }

    *outLeft = left;
    *outTop = top;
}
//---------------------------------------------------------------------------
// Fonction interne qui gère toute la logique d'affichage du clavier
void KeyboardShowInternal(TObject* Sender, int Type, int Left, int Top, float ratio)
{
    // 1. Récupérer la fenêtre/contrôle cible AVANT de créer le clavier
    HWND hTargetWindow = GetTargetWindowFromSender(Sender);
    HWND hPreviousWindow = GetForegroundWindow();

    // 2. Créer le clavier si nécessaire
    if (!FVirtualKeyboard)
    {
        Application->Handle = 0;
        Application->CreateForm(__classid(TFVirtualKeyboard), &FVirtualKeyboard);
    }

    // 3. Détection automatique du type (numérique ou non)
    if (Type == -1)
    {
        Type = NumberStatus(Sender);
    }

    // 4. Validation du ratio
    if (ratio < 0.7f) ratio = 0.7f;
    if (ratio > 2.0f) ratio = 2.0f;

    // 5. Configurer l'état du clavier
    FVirtualKeyboard->Etat(Type, ratio);

    // 6. Position automatique si Left et Top sont à leurs valeurs par défaut
    bool isDefaultPosition = (Left == 700 && Top == 500);

    if (isDefaultPosition && hTargetWindow)
    {
        // Calculer position automatique sous le contrôle
        int autoLeft, autoTop;
        CalculateAutoPosition(
            hTargetWindow,
            FVirtualKeyboard->Width,
            FVirtualKeyboard->Height,
            50,  // Offset de 50 pixels
            &autoLeft,
            &autoTop
        );

        FVirtualKeyboard->Left = autoLeft;
        FVirtualKeyboard->Top = autoTop;
    }
    else
    {
        // Position manuelle spécifiée
        FVirtualKeyboard->Left = Left;
        FVirtualKeyboard->Top = Top;
    }

    // 7. Sauvegarder le contrôle cible
    if (hTargetWindow)
    {
        FVirtualKeyboard->TargetWindow = hTargetWindow;
    }

    // 8. Afficher le clavier
    FVirtualKeyboard->Show();

    // 9. Restaurer le focus
    if (hPreviousWindow && (hPreviousWindow != FVirtualKeyboard->Handle))
    {
        SetForegroundWindow(hPreviousWindow);
        SetWindowPos(FVirtualKeyboard->Handle, HWND_TOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

//---------------------------------------------------------------------------
// Fonction interne pour affichage automatique avec offset personnalisé
void KeyboardShowAutoInternal(TObject* Sender, int Type, int offsetY, float ratio)
{
    HWND hTargetWindow = GetTargetWindowFromSender(Sender);
    HWND hPreviousWindow = GetForegroundWindow();

    if (!FVirtualKeyboard)
    {
        Application->Handle = 0;
        Application->CreateForm(__classid(TFVirtualKeyboard), &FVirtualKeyboard);
    }

    if (Type == -1)
    {
        Type = NumberStatus(Sender);
    }

    if (ratio < 0.7f) ratio = 0.7f;
    if (ratio > 2.0f) ratio = 2.0f;

    FVirtualKeyboard->Etat(Type, ratio);

    // TOUJOURS calculer position automatique
    int autoLeft, autoTop;
    CalculateAutoPosition(
        hTargetWindow,
        FVirtualKeyboard->Width,
        FVirtualKeyboard->Height,
        offsetY,
        &autoLeft,
        &autoTop
    );

    FVirtualKeyboard->Left = autoLeft;
    FVirtualKeyboard->Top = autoTop;

    if (hTargetWindow)
    {
        FVirtualKeyboard->TargetWindow = hTargetWindow;
    }

    FVirtualKeyboard->Show();

    if (hPreviousWindow && (hPreviousWindow != FVirtualKeyboard->Handle))
    {
        SetForegroundWindow(hPreviousWindow);
        SetWindowPos(FVirtualKeyboard->Handle, HWND_TOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

//---------------------------------------------------------------------------
// FONCTIONS EXPORTÉES (extern "C")
//---------------------------------------------------------------------------
extern "C"
{
    __declspec(dllexport) void __stdcall KeyboardSetLocation(int Left, int Top)
    {
        if (FVirtualKeyboard)
        {
            FVirtualKeyboard->Left = Left;
            FVirtualKeyboard->Top = Top;
        }
    }

    //---------------------------------------------------------------------------
    __declspec(dllexport) void __stdcall KeyboardShow(TObject *Sender, int Type=0, int Left=700, int Top=500, float ratio=1)
    {
        try
        {
            KeyboardShowInternal(Sender, Type, Left, Top, ratio);
        }
        catch (...)
        {
            // Suppression des exceptions pour éviter les crashs dans l'application hôte
        }
    }

    //---------------------------------------------------------------------------
    __declspec(dllexport) void __stdcall KeyboardShowAuto(TObject *Sender, int Type=0, int offsetY=50, float ratio=1)
    {
        try
        {
            KeyboardShowAutoInternal(Sender, Type, offsetY, ratio);
        }
        catch (...)
        {
            // Suppression des exceptions pour éviter les crashs dans l'application hôte
        }
    }

    //---------------------------------------------------------------------------
    __declspec(dllexport) void __stdcall KeyboardHide(void)
    {
        if (FVirtualKeyboard)
        {
            FVirtualKeyboard->Hide();
        }
    }

    //---------------------------------------------------------------------------
    __declspec(dllexport) BOOL __stdcall KeyboardIsVisible(void)
    {
        return (FVirtualKeyboard && FVirtualKeyboard->Visible);
    }
}
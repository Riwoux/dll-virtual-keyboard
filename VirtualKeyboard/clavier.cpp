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

#include "clavier1.h"
#include <vcl.h>
#include <windows.h>
#include <System.Rtti.hpp>

#pragma hdrstop
#pragma argsused

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}

void InitKeyboard(void)
{
    if (!FVirtualKeyboard) {
        Application->CreateForm(__classid(TFVirtualKeyboard), &FVirtualKeyboard);
    }
}

// Ne fonctionne pas car NumbersOnly dan TCustomEdit est protected mais les TEdit donnés semble etr des TCustomEdit
bool NumberStatus(TObject* Obj)
{
    if (Obj == NULL) {
        return false;
    }
    try {
        //tous les types possibles qui ont NumbersOnly en paramètre
        TEdit* Edit = dynamic_cast<TEdit*>(Obj);
        if (Edit != NULL) {
            return Edit->NumbersOnly;
        }
        TCustomEdit* CustomEdit = dynamic_cast<TCustomEdit*>(Obj);
        if (CustomEdit != NULL) {
            return CustomEdit->NumbersOnly;
        }
        TLabeledEdit* LabeledEdit = dynamic_cast<TLabeledEdit*>(Obj);
        if (LabeledEdit != NULL) {
            return LabeledEdit->NumbersOnly;
        }
        TButtonedEdit* ButtonedEdit = dynamic_cast<TButtonedEdit*>(Obj);
        if (ButtonedEdit != NULL) {
            return ButtonedEdit->NumbersOnly;
        }

    } catch (...) {
        return false;
    }
    return false;
}


extern "C"
{
    __declspec(dllexport) void __stdcall KeyboardShow(TObject* Sender)
    {
        try {
            InitKeyboard();
            int etat = NumberStatus(Sender);
            FVirtualKeyboard->Etat(etat);
            FVirtualKeyboard->Show();
        } catch (...) {
        }
    }
    __declspec(dllexport) void __stdcall KeyboardHide(void)
    {
        try {
            if (FVirtualKeyboard) {
            	FVirtualKeyboard->Hide();
            }
        } catch (...) {
        }
    }

}
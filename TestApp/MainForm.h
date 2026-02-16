//---------------------------------------------------------------------------
// MainForm.h - Formulaire principal de l'application de test
//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <windows.h>
//---------------------------------------------------------------------------

// Types des fonctions exportées de la DLL
typedef void (__stdcall *TShowKeyboardProc)(int mode, HWND targetHandle);
typedef void (__stdcall *THideKeyboardProc)();
typedef bool (__stdcall *TIsKeyboardVisibleProc)();
typedef void (__stdcall *TSetKeyboardModeProc)(int mode);

class TFormMain : public TForm
{
__published:	// Composants gérés par l'IDE
    TMemo *MemoTest;
    TButton *BtnShowSimple;
    TButton *BtnShowWithNumpad;
    TButton *BtnHide;
    TLabel *Label1;
    TLabel *LabelStatus;
    void __fastcall BtnShowSimpleClick(TObject *Sender);
    void __fastcall BtnShowWithNumpadClick(TObject *Sender);
    void __fastcall BtnHideClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    
private:	// Déclarations utilisateur
    HINSTANCE FDllHandle;
    TShowKeyboardProc FShowKeyboard;
    THideKeyboardProc FHideKeyboard;
    TIsKeyboardVisibleProc FIsKeyboardVisible;
    TSetKeyboardModeProc FSetKeyboardMode;
    
    bool LoadKeyboardDLL();
    void UnloadKeyboardDLL();
    void UpdateStatus();
    
public:		// Déclarations utilisateur
    __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif

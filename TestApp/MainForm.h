//---------------------------------------------------------------------------
// MainForm.h - Simple Test Application Form
//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <windows.h>
#include <Vcl.Touch.Keyboard.hpp>
//---------------------------------------------------------------------------

// DLL exported function types
typedef void (__stdcall *TShowKeyboardProc)(HWND targetHandle, int etat);
typedef void (__stdcall *THideKeyboardProc)();
typedef bool (__stdcall *TIsKeyboardVisibleProc)();

class TFormMain : public TForm
{
__published:
    TMemo *MemoTest;
    TButton *BtnShow;
    TButton *BtnHide;
    TLabel *Label1;
	TButton *Button1;
    void __fastcall BtnShowClick(TObject *Sender);
    void __fastcall BtnHideClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
    
private:
    HINSTANCE FDllHandle;
    TShowKeyboardProc FShowKeyboard;
    THideKeyboardProc FHideKeyboard;
    TIsKeyboardVisibleProc FIsKeyboardVisible;
    
    bool LoadKeyboardDLL();
    void UnloadKeyboardDLL();
    
public:
    __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif

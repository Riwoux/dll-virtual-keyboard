//---------------------------------------------------------------------------
// MainForm.h - Simple Test Application Form
//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------

#include "C:\user\lib\c10\wide\wide.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <windows.h>
#include <Vcl.Touch.Keyboard.hpp>
#include <Winapi.Windows.hpp>

//D�but modif 023 CL
int KeyboardShow(HWND targetHandle, int etat);
int KeyboardHide(void);
int KeyboardAttachToForm(HWND formHandle, bool autohide);
int KeyboardFromFormDetach(HWND formHandle);
int KeyboardAutoShow(HWND hwnd);

UnicodeString dirClavierVirtuel = "C:\\Users\\corentin.langlade\\Documents\\Stage\\Clavier_virtuel\\testclaviervirtuel\\touchkeyboard\\Win64\\Release\\touchkeyboard.dll";  //Modif 023 CL
//Fin modif 023 CL
//---------------------------------------------------------------------------


class TFormMain : public TForm
{
__published:
	TEdit *Edit1;
	TEdit *Edit2;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall TextControlEnter(TObject* Sender);

private:
public:
    __fastcall TFormMain(TComponent* Owner);
};


//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif

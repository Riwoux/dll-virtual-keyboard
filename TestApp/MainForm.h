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
#include "Edit_Int.h"
#include "Edit_Dbl.h"

//Début modif 023 CL
int KeyboardShow(int Type=-1, int Left=700, int Top=500, int ratio=1);
int KeyboardHide();

UnicodeString dirClavierVirtuel = "C:\\User\\Util\\C10\\DLL.C13\\Superv_Keyboard.dll";  //Modif 023 CL
//Fin modif 023 CL
//---------------------------------------------------------------------------


class TFormMain : public TForm
{
__published:
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit_Int *Edit_Int1;
	TMemo *Memo1;
    void __fastcall FormCreate(TObject *Sender);
private:
	void __fastcall AutoShow(TObject *Sender);
    void __fastcall AutoShowNumPad(TObject *Sender);
    void __fastcall AutoHide(TObject *Sender);
public:
    __fastcall TFormMain(TComponent* Owner);
};


//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif

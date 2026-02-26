//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clavier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tkeyboard *keyboard = NULL;
//---------------------------------------------------------------------------
__fastcall Tkeyboard::Tkeyboard(TComponent* Owner)
	: TForm(Owner), FTargetHandle(NULL)
{
    BorderStyle = bsSizeable;
}
//---------------------------------------------------------------------------

void Tkeyboard::Etat(int etat)
{
    keyboard->Left = 500 ;
    keyboard->Top = 500 ;
    if (etat==-1) {
    	TouchKeyboard1->Layout = "Standard";
        keyboard->Width = 997;
    	keyboard->Height = 297;
    }
    if (etat!=-1) {
        TouchKeyboard1->Layout = "NumPad" ;
        keyboard->Width = 297;
    	keyboard->Height = 297;
    }
}

void Tkeyboard::SetTargetControl(HWND targetHandle)
{
    FTargetHandle = targetHandle;
    if (FTargetHandle && ::IsWindow(FTargetHandle)) {
        ::SetFocus(FTargetHandle);
        ::SetForegroundWindow(::GetParent(FTargetHandle));
    }
}

void __fastcall Tkeyboard::TouchKeyboard1KeyPress(TObject *Sender, System::WideChar &Key)
{
    if (FTargetHandle && ::IsWindow(FTargetHandle)) {
        ::PostMessage(FTargetHandle, WM_CHAR, (WPARAM)Key, 0);
    }
}


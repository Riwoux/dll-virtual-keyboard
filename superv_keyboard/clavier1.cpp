/*------------------------------------------------------------------------------
04/03/2026	001	Cl	Création
-------------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop

#define LIBRAIRIE

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
#include "clavier1.h"
#include "C:\User\Lib\C10\Wide\wide.h"

//---------------------------------------------------------------------------
__fastcall TFVirtualKeyboard::TFVirtualKeyboard(TComponent* Owner)
	: TForm(Owner)
{
    FTargetWindow = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFVirtualKeyboard::CreateParams(TCreateParams &Params)
{
    TForm::CreateParams(Params);

    Params.ExStyle |= WS_EX_NOACTIVATE | WS_EX_TOPMOST;
    Params.WndParent = GetDesktopWindow();
}
//---------------------------------------------------------------------------
void __fastcall TFVirtualKeyboard::WMMouseActivate(TWMMouseActivate &Message)
{
    Message.Result = MA_NOACTIVATE; // Ignore le focus sur la fenetre mais pas l'action de la souris
}
//---------------------------------------------------------------------------
void __fastcall TFVirtualKeyboard::FormCreate(TObject *Sender)
{
    BorderStyle = bsSizeable;
    FormStyle = fsStayOnTop;

    TouchKeyboard1->Align = alClient;

    ClientWidth = FVirtualKeyboard->Width;
    ClientHeight = FVirtualKeyboard->Height;
}
//---------------------------------------------------------------------------
void __fastcall TFVirtualKeyboard::FormClose(TObject *Sender, TCloseAction &Action)
{
    Hide();
    Action = caHide;
}
//---------------------------------------------------------------------------
void __fastcall TFVirtualKeyboard::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    Hide();
    CanClose = false;
}
//---------------------------------------------------------------------------
void TFVirtualKeyboard::Etat(bool etat, float ratio)
{
    if (!etat) {
    	TouchKeyboard1->Layout = "Standard";
        ClientWidth = 1000*ratio;
        ClientHeight = 300*ratio;
        TouchKeyboard1->Height = 300*ratio;
        TouchKeyboard1->Width = 1000*ratio;
    }
    else if (etat) {
        TouchKeyboard1->Layout = "NumPad" ;
        ClientWidth = 300*ratio;
        ClientHeight = 300*ratio;
        TouchKeyboard1->Height = 300*ratio;
        TouchKeyboard1->Width = 300*ratio;
    }

}
//---------------------------------------------------------------------------


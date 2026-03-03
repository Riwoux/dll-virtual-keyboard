//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#define LIBRAIRIE

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
#include "clavier1.h"

//---------------------------------------------------------------------------
TFVirtualKeyboard *FVirtualKeyboard;
//---------------------------------------------------------------------------
__fastcall TFVirtualKeyboard::TFVirtualKeyboard(TComponent* Owner)
	: TForm(Owner)
{
    BorderStyle = bsSizeable;
}

void __fastcall TFVirtualKeyboard::FormClose(TObject *Sender, TCloseAction &Action)
{
    Hide();
}

void __fastcall TFVirtualKeyboard::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    Hide();
    CanClose = false;
}

void TFVirtualKeyboard::Etat(bool etat)
{
    Left = 500 ;
    Top = 700 ;
    if (!etat) {
    	TouchKeyboard1->Layout = "Standard";
        ClientWidth = 1000;
        ClientHeight = 300;
        TouchKeyboard1->Width = 1000;
    	TouchKeyboard1->Height = 300;
    }
    else if (etat) {
        TouchKeyboard1->Layout = "NumPad" ;
        ClientWidth = 300;
        ClientHeight = 300;
        TouchKeyboard1->Width = 300;
    	TouchKeyboard1->Height = 300;
    }

}


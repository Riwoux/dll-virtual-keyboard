//---------------------------------------------------------------------------

#ifndef clavier1H
#define clavier1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Touch.Keyboard.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
//---------------------------------------------------------------------------
class TFVirtualKeyboard : public TForm
{
__published:	// Composants gérés par l'EDI
	TTouchKeyboard *TouchKeyboard1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	__fastcall TFVirtualKeyboard(TComponent* Owner);
    void Etat(bool etat);
};
//---------------------------------------------------------------------------
extern PACKAGE TFVirtualKeyboard *FVirtualKeyboard;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef clavier1H
#define clavier1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Touch.Keyboard.hpp>
//---------------------------------------------------------------------------
class TFVirtualKeyboard : public TForm
{
__published:	// Composants gérés par l'EDI
	TTouchKeyboard *TouchKeyboard1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall KeyPress(TObject* Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// Déclarations utilisateur
    TObject* FTargetControl;
public:		// Déclarations utilisateur
	__fastcall TFVirtualKeyboard(TComponent* Owner);
    void Etat(bool etat, float ratio);
    void SetTargetControl(TObject* Target);
};
//---------------------------------------------------------------------------
extern PACKAGE TFVirtualKeyboard *FVirtualKeyboard;
//---------------------------------------------------------------------------
#endif

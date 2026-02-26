//---------------------------------------------------------------------------

#ifndef clavierH
#define clavierH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Touch.Keyboard.hpp>
#include <Vcl.Touch.KeyboardTypes.hpp>
//---------------------------------------------------------------------------
class Tkeyboard : public TForm
{
__published:	// Composants gérés par l'EDI
	TTouchKeyboard *TouchKeyboard1;
    void __fastcall TouchKeyboard1KeyPress(TObject *Sender, System::WideChar &Key);

private:
    HWND FTargetHandle;
public:		// Déclarations utilisateur
	__fastcall Tkeyboard(TComponent* Owner);
    void Etat(int etat);
    void SetTargetControl(HWND targetHandle);
};
//---------------------------------------------------------------------------
extern PACKAGE Tkeyboard *keyboard;
//---------------------------------------------------------------------------
#endif

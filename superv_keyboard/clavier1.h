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
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// Déclarations utilisateur
    HWND FTargetWindow;
protected:
    virtual void __fastcall CreateParams(TCreateParams &Params);
    void __fastcall WMMouseActivate(TWMMouseActivate &Message);

    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_MOUSEACTIVATE, TWMMouseActivate, WMMouseActivate)
    END_MESSAGE_MAP(TForm)
public:		// Déclarations utilisateur
	__fastcall TFVirtualKeyboard(TComponent* Owner);
    __property HWND TargetWindow = {read=FTargetWindow, write=FTargetWindow};
    void Etat(bool etat, float ratio);
};
//---------------------------------------------------------------------------
extern PACKAGE TFVirtualKeyboard *FVirtualKeyboard;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
// KeyboardForm.h - Simple Virtual Keyboard Form
//---------------------------------------------------------------------------
#ifndef KeyboardFormH
#define KeyboardFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

class TFormKeyboard : public TForm
{
__published:
    
private:
    HWND FTargetHandle;        // Target control handle
    bool FShiftActive;         // Shift key state
    
    // Event handlers
    void __fastcall OnKeyButtonClick(TObject *Sender);
    void __fastcall OnShiftClick(TObject *Sender);
    void __fastcall OnBackspaceClick(TObject *Sender);
    void __fastcall OnEnterClick(TObject *Sender);
    void __fastcall OnSpaceClick(TObject *Sender);
    
    void __fastcall SendCharToTarget(wchar_t ch);
    void __fastcall SendKeyToTarget(WORD vKey);
    TButton* __fastcall CreateButton(const String& Caption, 
                                      int Left, int Top, int Width, int Height);
    
public:
    __fastcall TFormKeyboard(TComponent* Owner);
    void __fastcall SetTargetHandle(HWND handle);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKeyboard *FormKeyboard;
//---------------------------------------------------------------------------
#endif

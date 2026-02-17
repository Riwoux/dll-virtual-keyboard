//---------------------------------------------------------------------------
#ifndef KeyboardFormH
#define KeyboardFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <vector>
#include <windows.h>
//---------------------------------------------------------------------------
class TFormKeyboard : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
    HWND FTargetHandle;
    bool FShiftActive;
    bool NumPadActive;
	std::vector<TButton*> padbuttons;
	std::vector<TButton*> azerty;
	std::vector<TButton*> qwerty;
	int etatlangue;

    void __fastcall FormShow(TObject *Sender);
    void __fastcall OnKeyButtonMouseDown(TObject *Sender, TMouseButton Button,
                                         TShiftState Shift, int X, int Y);
    void __fastcall OnArrowMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
    void __fastcall OnShiftMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
    void __fastcall OnBackspaceMouseDown(TObject *Sender, TMouseButton Button,
                                         TShiftState Shift, int X, int Y);
    void __fastcall OnEnterMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
    void __fastcall OnSpaceMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
	void __fastcall OnNumPadClick(TObject *Sender);
    void __fastcall OnLanguageClick(TObject *Sender);

    void CaptureTargetWindow();
    void __fastcall SendCharToTarget(wchar_t ch);
    void __fastcall SendKeyToTarget(WORD vKey);
    void __fastcall SendArrowKeyToTarget(BYTE vkArrowCode);

    TButton* __fastcall CreateButton(const String& Caption, int Left, int Top,
                                     int Width, int Height);

public:		// User declarations
    __fastcall TFormKeyboard(TComponent* Owner);
    void __fastcall SetTargetHandle(HWND handle);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKeyboard *FormKeyboard;
//---------------------------------------------------------------------------
#endif

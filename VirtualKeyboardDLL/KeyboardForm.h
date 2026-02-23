//---------------------------------------------------------------------------
#ifndef KeyboardFormH
#define KeyboardFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Touch.Keyboard.hpp>
#define WIN32_LEAN_AND_MEAN
#include <Winapi.Windows.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <vector>

//---------------------------------------------------------------------------
// Structure to hold key data with both normal and shifted states
struct KeyData {
    String normalCaption;   // Display text when not shifted (VCL-safe, e.g., "&&" for ampersand)
    String shiftedCaption;  // Display text when shifted (VCL-safe)
    wchar_t normalChar;     // Character to send when not shifted
    wchar_t shiftedChar;    // Character to send when shifted
};
//---------------------------------------------------------------------------
class TFormKeyboard : public TForm
{
__published:
private:
    HWND FTargetHandle;
    bool FShiftActive;
    bool FMajActive;
    bool NumPadActive;
    double SizeRatio;
	std::vector<TButton*> padbuttons;
	std::vector<TButton*> azerty;
	std::vector<TButton*> qwerty;
    std::vector<TButton*> qwertz;
	std::vector<KeyData> azertyData;
	std::vector<KeyData> qwertyData;
	std::vector<KeyData> qwertzData;
	int etatlangue;
	bool FDeadPending;
    wchar_t FDeadChar;

    TButton* btnShift;
    TButton* btnMaj;

    TButton* __fastcall CreateButton(const String& Caption, int Left, int Top,
                                     int Width, int Height);


    void __fastcall FormShow(TObject *Sender);
    void __fastcall OnKeyButtonMouseDown(TObject *Sender, TMouseButton Button,
                                         TShiftState Shift, int X, int Y);
    void __fastcall OnArrowMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
    void __fastcall OnShiftMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
    void __fastcall OnMajMouseDown(TObject *Sender, TMouseButton Button,
    								TShiftState Shift, int X, int Y);
    void __fastcall OnBackspaceMouseDown(TObject *Sender, TMouseButton Button,
                                         TShiftState Shift, int X, int Y);
    void __fastcall OnEnterMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
    void __fastcall OnSpaceMouseDown(TObject *Sender, TMouseButton Button,
                                     TShiftState Shift, int X, int Y);
	void __fastcall OnNumPadKeyMouseDown(TObject *Sender, TMouseButton Button,
                                         TShiftState Shift, int X, int Y);
	void __fastcall OnNumPadClick(TObject *Sender);
	void __fastcall OnLanguageClick(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
									TShiftState Shift, int X, int Y);
    void __fastcall UpdateShiftButtonState();
    void __fastcall UpdateMajButtonState();
    void __fastcall InitializeKeyboardData();
    void __fastcall UpdateAllButtonLabels();
    wchar_t __fastcall ComposeDeadKey(wchar_t dead, wchar_t base) const;
    void __fastcall SendCharToTarget(wchar_t ch);
    void __fastcall SendKeyToTarget(WORD vKey);
    bool __fastcall IsDeadKey(wchar_t ch) const;
    void __fastcall SendArrowKeyToTarget(BYTE vkArrowCode);



    void AutoDetectLanguage();
    void ApplyLanguageVisibility();
    void CaptureTargetWindow();



public:
    __fastcall TFormKeyboard(TComponent* Owner);
    void __fastcall SetTargetHandle(HWND handle);
    void __fastcall ShowNumPad();
    void __fastcall ShowKeyboard();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKeyboard *FormKeyboard;
extern "C" void __stdcall KeyboardForm_NotifyDestroyed(void);
//---------------------------------------------------------------------------
#endif

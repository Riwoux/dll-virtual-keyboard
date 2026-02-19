//---------------------------------------------------------------------------
#ifndef KeyboardFormH
#define KeyboardFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <vector>
#include <windows.h>

#ifndef RT_RCDATA
#define RT_RCDATA MAKEINTRESOURCEW(10)
#endif
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

    TImage* imgMaj;
    TPngImage* MajOffImage;
    TPngImage* MajOnImage;
    TPanel* pnlMaj;
    TButton* btnShift;

    TButton* __fastcall CreateButton(const String& Caption, int Left, int Top,
                                     int Width, int Height);
    TPanel* __fastcall CreateImageButton(int Left, int Top, int Width, int Height);
    void __fastcall LoadPNGFromResource();
    void __fastcall UpdateMajButtonImage();


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
    
    // Initialize keyboard layout data
    void __fastcall InitializeKeyboardData();
    
    // Mise à jour des labels de tous les boutons
    void __fastcall UpdateAllButtonLabels();

    void CaptureTargetWindow();
    void __fastcall SendCharToTarget(wchar_t ch);
    void __fastcall SendKeyToTarget(WORD vKey);
    void __fastcall SendArrowKeyToTarget(BYTE vkArrowCode);


public:
    __fastcall TFormKeyboard(TComponent* Owner);
    __fastcall ~TFormKeyboard();
    void __fastcall SetTargetHandle(HWND handle);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKeyboard *FormKeyboard;
//---------------------------------------------------------------------------
#endif

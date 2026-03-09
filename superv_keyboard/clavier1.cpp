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
TFVirtualKeyboard *FVirtualKeyboard;
//---------------------------------------------------------------------------
__fastcall TFVirtualKeyboard::TFVirtualKeyboard(TComponent* Owner)
	: TForm(Owner)
{
    BorderStyle = bsSizeable;
    FormStyle = fsStayOnTop;
    Left = 500;
    Top = 700;
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
        TouchKeyboard1->Width = 1000*ratio;
    	TouchKeyboard1->Height = 300*ratio;
    }
    else if (etat) {
        TouchKeyboard1->Layout = "NumPad" ;
        ClientWidth = 300*ratio;
        ClientHeight = 300*ratio;
        TouchKeyboard1->Width = 300*ratio;
    	TouchKeyboard1->Height = 300*ratio;
    }

}
//---------------------------------------------------------------------------
void TFVirtualKeyboard::SetTargetControl(TObject* Target)
{
    FTargetControl = Target;
}
//---------------------------------------------------------------------------
void __fastcall TFVirtualKeyboard::KeyPress(TObject *Sender, wchar_t &Key)
{
    /*if (FTargetControl == NULL) {
        return;
    }

    try {
        String className = FTargetControl->ClassName();
        TCustomEdit* edit = static_cast<TCustomEdit*>(FTargetControl);
        if (Key == VK_BACK) {
            // Backspace
            String text = edit->Text;
            int posCaract = edit->SelStart;

            if (posCaract > 0) {
                text.Delete(posCaract, 1);
                edit->Text = text;
                edit->SelStart = posCaract - 1;
            }
            return;
        }
        else if (Key == VK_RETURN) {
            // Enter : pour les Memo uniquement
            if (className == "TMemo" || className == "TRichEdit") {
                TMemo* memo = static_cast<TMemo*>(FTargetControl);
                int posCaract = memo->SelStart;
                String text = memo->Text;
                text.Insert(L"\r\n", posCaract + 1);
                memo->Text = text;
                memo->SelStart = posCaract + 2;
            }
            return;
        }

        // Récupérer NumbersOnly car protected dans TCustomEdit
        class TCustomEditAccessor : public TCustomEdit {
        public:
            bool GetNumbersOnly() const { return NumbersOnly; }
        };

        TCustomEditAccessor* accessor = reinterpret_cast<TCustomEditAccessor*>(edit);
        bool isNumbersOnly = accessor->GetNumbersOnly();
        if (isNumbersOnly) {
            if (Key < L'0' || Key > L'9') {
                return;
            }
        }
        edit->SelText = String(Key);
    } catch (...) {
    } */
}

void __fastcall TFVirtualKeyboard::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    INPUT in{};
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = Key;
    SendInput(1, &in, sizeof(INPUT));
}
//---------------------------------------------------------------------------

void __fastcall TFVirtualKeyboard::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
    INPUT in{};
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = Key;
    in.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &in, sizeof(INPUT));
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

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
}

void __fastcall TFVirtualKeyboard::FormClose(TObject *Sender, TCloseAction &Action)
{
    Hide();
    Action = caHide;
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

void TFVirtualKeyboard::SetTargetControl(TObject* Target)
{
    FTargetControl = Target;
}

void __fastcall TFVirtualKeyboard::KeyPress(TObject *Sender, wchar_t &Key)
{
    if (FTargetControl == NULL) {
        return;
    }

    try {
        String className = FTargetControl->ClassName();
        TCustomEdit* edit = static_cast<TCustomEdit*>(FTargetControl);
        if (Key == VK_BACK) {
            // Backspace
            String text = edit->Text;
            int selStart = edit->SelStart;

            if (selStart > 0) {
                text.Delete(selStart, 1);
                edit->Text = text;
                edit->SelStart = selStart - 1;
            }
            return;
        }
        else if (Key == VK_RETURN) {
            // Enter : pour les Memo uniquement
            if (className == "TMemo" || className == "TRichEdit") {
                TMemo* memo = static_cast<TMemo*>(FTargetControl);
                int selStart = memo->SelStart;
                String text = memo->Text;
                text.Insert(L"\r\n", selStart + 1);
                memo->Text = text;
                memo->SelStart = selStart + 2;
            }
            return;
        }

        // Permet de faire de faire respecter le NumbersOnly
        class TCustomEditAccessor : public TCustomEdit {
        public:
            bool GetNumbersOnly() const { return NumbersOnly; }
        };

        TCustomEditAccessor* accessor = reinterpret_cast<TCustomEditAccessor*>(edit);
        bool isNumbersOnly = accessor->GetNumbersOnly();
        if (isNumbersOnly) {
            if (Key < L'0' || Key > L'9') {
                return;  // Rejeter tout ce qui n'est pas 0-9
            }
        }
        edit->SelLength = 0;
        edit->SelText = String(Key);
    } catch (...) {
    }
}

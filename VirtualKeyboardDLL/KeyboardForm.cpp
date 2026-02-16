//---------------------------------------------------------------------------
// KeyboardForm.cpp - Simple Virtual Keyboard Implementation
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "KeyboardForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormKeyboard *FormKeyboard;

//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
__fastcall TFormKeyboard::TFormKeyboard(TComponent* Owner)
    : TForm(Owner), FTargetHandle(NULL), FShiftActive(false)
{
    // Form configuration
    BorderStyle = bsToolWindow;
    FormStyle = fsStayOnTop;
    Position = poScreenCenter;
    Caption = "Clavier Virtuel";
    ClientWidth = 660;
    ClientHeight = 250;
    
    const int btnWidth = 50;
    const int btnHeight = 45;
    const int spacing = 5;
    int row = 10;
    
    // Row 1: Numbers 1-0
    String row1Keys[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    for (int i = 0; i < 10; i++) {
        TButton* btn = CreateButton(row1Keys[i], 
                                   10 + i * (btnWidth + spacing), row, 
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)row1Keys[i][1];
        btn->OnClick = OnKeyButtonClick;
    }
    
    // Row 2: A-Z-E-R-T-Y-U-I-O-P
    row += btnHeight + spacing;
    String row2Keys[] = {"A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P"};
    for (int i = 0; i < 10; i++) {
        TButton* btn = CreateButton(row2Keys[i], 
                                   10 + i * (btnWidth + spacing), row, 
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)row2Keys[i][1];
        btn->OnClick = OnKeyButtonClick;
    }
    
    // Row 3: Q-S-D-F-G-H-J-K-L-M
    row += btnHeight + spacing;
    String row3Keys[] = {"Q", "S", "D", "F", "G", "H", "J", "K", "L", "M"};
    for (int i = 0; i < 10; i++) {
        TButton* btn = CreateButton(row3Keys[i], 
                                   35 + i * (btnWidth + spacing), row, 
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)row3Keys[i][1];
        btn->OnClick = OnKeyButtonClick;
    }
    
    // Row 4: W-X-C-V-B-N
    row += btnHeight + spacing;
    String row4Keys[] = {"W", "X", "C", "V", "B", "N"};
    for (int i = 0; i < 6; i++) {
        TButton* btn = CreateButton(row4Keys[i], 
                                   60 + i * (btnWidth + spacing), row, 
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)row4Keys[i][1];
        btn->OnClick = OnKeyButtonClick;
    }
    
    // Row 5: Special keys
    row += btnHeight + spacing;
    
    // Shift button
    TButton* btnShift = CreateButton("Maj", 10, row, 70, btnHeight);
    btnShift->OnClick = OnShiftClick;
    
    // Space button
    TButton* btnSpace = CreateButton("Espace", 85, row, 200, btnHeight);
    btnSpace->OnClick = OnSpaceClick;
    
    // Backspace button
    TButton* btnBackspace = CreateButton("←", 290, row, 70, btnHeight);
    btnBackspace->OnClick = OnBackspaceClick;
    
    // Enter button
    TButton* btnEnter = CreateButton("Entrée", 365, row, 100, btnHeight);
    btnEnter->OnClick = OnEnterClick;
}

//---------------------------------------------------------------------------
// Create a button
//---------------------------------------------------------------------------
TButton* __fastcall TFormKeyboard::CreateButton(const String& Caption,
                                                 int Left, int Top, int Width, int Height)
{
    TButton* btn = new TButton(this);
    btn->Parent = this;
    btn->Caption = Caption;
    btn->Left = Left;
    btn->Top = Top;
    btn->Width = Width;
    btn->Height = Height;
    btn->Font->Size = 10;
    return btn;
}

//---------------------------------------------------------------------------
// Set target handle
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SetTargetHandle(HWND handle)
{
    FTargetHandle = handle;
}

//---------------------------------------------------------------------------
// Key button click handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnKeyButtonClick(TObject *Sender)
{
    TButton* btn = dynamic_cast<TButton*>(Sender);
    if (!btn || !FTargetHandle) return;
    
    wchar_t ch = (wchar_t)btn->Tag;
    
    // Apply shift if active
    if (FShiftActive) {
        if (ch >= 'A' && ch <= 'Z') {
            // Already uppercase
        } else if (ch >= 'a' && ch <= 'z') {
            ch = ch - 'a' + 'A';
        }
        FShiftActive = false; // Reset shift after one key
    } else {
        // Lowercase
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A' + 'a';
        }
    }
    
    SendCharToTarget(ch);
}

//---------------------------------------------------------------------------
// Shift button click handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnShiftClick(TObject *Sender)
{
    FShiftActive = !FShiftActive;
}

//---------------------------------------------------------------------------
// Backspace button click handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnBackspaceClick(TObject *Sender)
{
    SendKeyToTarget(VK_BACK);
}

//---------------------------------------------------------------------------
// Enter button click handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnEnterClick(TObject *Sender)
{
    SendKeyToTarget(VK_RETURN);
}

//---------------------------------------------------------------------------
// Space button click handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnSpaceClick(TObject *Sender)
{
    SendCharToTarget(' ');
}

//---------------------------------------------------------------------------
// Send a character to the target control
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SendCharToTarget(wchar_t ch)
{
    if (!FTargetHandle || !IsWindow(FTargetHandle)) return;
    PostMessage(FTargetHandle, WM_CHAR, ch, 0);
}

//---------------------------------------------------------------------------
// Send a virtual key to the target control
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SendKeyToTarget(WORD vKey)
{
    if (!FTargetHandle || !IsWindow(FTargetHandle)) return;
    PostMessage(FTargetHandle, WM_KEYDOWN, vKey, 0);
    PostMessage(FTargetHandle, WM_KEYUP, vKey, 0);
}
//---------------------------------------------------------------------------

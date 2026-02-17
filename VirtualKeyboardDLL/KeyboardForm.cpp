//---------------------------------------------------------------------------
// KeyboardForm.cpp - Simple Virtual Keyboard Implementation
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#pragma hdrstop

#include "KeyboardForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormKeyboard *FormKeyboard;

#define AZERTY 0
#define QWERTY 1
int langues[2]={AZERTY, QWERTY};

//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
__fastcall TFormKeyboard::TFormKeyboard(TComponent* Owner)
    : TForm(Owner), FTargetHandle(NULL), FShiftActive(false), NumPadActive(false), etatlangue(AZERTY)
{
    // Form configuration
    BorderStyle = bsToolWindow;
    FormStyle = fsStayOnTop;
    Position = poScreenCenter;
    Caption = "Virtual Keyboard";
    ClientWidth = 700;
    ClientHeight = 270;

    OnShow = FormShow;

    const int btnWidth = 50;
    const int btnHeight = 45;
    const int spacing = 5;
    int row = 10;

	// Azerty Row 1
	String azerty1Keys[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "="};
    for (int i = 0; i < 11; i++) {
		TButton* btn = CreateButton(azerty1Keys[i],
                                   10 + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)azerty1Keys[i][1];
		btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
	}
	// Qwerty Row 1
	String qwerty1Keys[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "="};
	for (int i = 0; i < 11; i++) {
		TButton* btn = CreateButton(qwerty1Keys[i],
								   10 + i * (btnWidth + spacing), row,
								   btnWidth, btnHeight);
		btn->Tag = (NativeInt)(wchar_t)qwerty1Keys[i][1];
		btn->OnMouseDown = OnKeyButtonMouseDown;
		qwerty.push_back(btn);
	}
    // Changer la langue
	TButton* btnLanguage = CreateButton("Language", 560 , row, 75, btnHeight);
	btnLanguage->OnClick = OnLanguageClick;

	row += btnHeight + spacing;
	// Azerty Row 2
	String azerty2Keys[] = {"A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P"};
    for (int i = 0; i < 10; i++) {
		TButton* btn = CreateButton(azerty2Keys[i],
                                   10 + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
		btn->Tag = (NativeInt)(wchar_t)azerty2Keys[i][1];
		btn->OnMouseDown = OnKeyButtonMouseDown;
		azerty.push_back(btn);
	}
	// Qwerty Row 2
	String qwerty2Keys[] = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"};
	for (int i = 0; i < 10; i++) {
		TButton* btn = CreateButton(qwerty2Keys[i],
								   10 + i * (btnWidth + spacing), row,
								   btnWidth, btnHeight);
		btn->Tag = (NativeInt)(wchar_t)qwerty2Keys[i][1];
		btn->OnMouseDown = OnKeyButtonMouseDown;
		qwerty.push_back(btn);
	}

    // Backspace button
    TButton* btnBackspace = CreateButton("Delete", 560, row, 100, btnHeight);
    btnBackspace->OnMouseDown = OnBackspaceMouseDown;

	row += btnHeight + spacing;
	// Azerty Row 3
	String azerty3Keys[] = {"Q", "S", "D", "F", "G", "H", "J", "K", "L", "M"};
	for (int i = 0; i < 10; i++) {
		TButton* btn = CreateButton(azerty3Keys[i],
                                   35 + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
		btn->Tag = (NativeInt)(wchar_t)azerty3Keys[i][1];
		btn->OnMouseDown = OnKeyButtonMouseDown;
		azerty.push_back(btn);
	}
    // Qwerty Row 3
	String qwerty3Keys[] = {"A", "S", "D", "F", "G", "H", "J", "K", "L"};
	for (int i = 0; i < 9; i++) {
		TButton* btn = CreateButton(qwerty3Keys[i],
                                   35 + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
		btn->Tag = (NativeInt)(wchar_t)qwerty3Keys[i][1];
		btn->OnMouseDown = OnKeyButtonMouseDown;
		qwerty.push_back(btn);
    }

	row += btnHeight + spacing;
	// Azerty Row 4
	String azerty4Keys[] = {"W", "X", "C", "V", "B", "N"};
    for (int i = 0; i < 6; i++) {
		TButton* btn = CreateButton(azerty4Keys[i],
                                   60 + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)azerty4Keys[i][1];
		btn->OnMouseDown = OnKeyButtonMouseDown;
		azerty.push_back(btn);
	}
    // Qwerty Row 4
	String qwerty4Keys[] = {"W", "X", "C", "V", "B", "N", "M"};
    for (int i = 0; i < 7; i++) {
		TButton* btn = CreateButton(qwerty4Keys[i],
                                   60 + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
		btn->Tag = (NativeInt)(wchar_t)qwerty4Keys[i][1];
		btn->OnMouseDown = OnKeyButtonMouseDown;
		qwerty.push_back(btn);
	}

	// Special keys

    // Activer et desactiver NumPad
    TButton* btnNumPad = CreateButton("NumPad", 590 , row, 75, 1.5*btnHeight);
    btnNumPad->OnClick = OnNumPadClick;

	// Up button
	TButton* btnUp = CreateButton("Up", 460, row, 50, btnHeight);
	btnUp->Tag = VK_UP;
	btnUp->OnMouseDown = OnArrowMouseDown;

    row += btnHeight + spacing;

    // Left button
    TButton* btnLeft = CreateButton("Left", 405, row, 50, btnHeight);
    btnLeft->Tag = VK_LEFT;
    btnLeft->OnMouseDown = OnArrowMouseDown;

    // Down button
    TButton* btnDown = CreateButton("Down", 460, row, 50, btnHeight);
    btnDown->Tag = VK_DOWN;
    btnDown->OnMouseDown = OnArrowMouseDown;

    // Right button
    TButton* btnRight = CreateButton("Right", 515, row, 50, btnHeight);
    btnRight->Tag = VK_RIGHT;
    btnRight->OnMouseDown = OnArrowMouseDown;

    // Shift button
    TButton* btnShift = CreateButton("Shift", 10, row, 70, btnHeight);
    btnShift->OnMouseDown = OnShiftMouseDown;

    // Space button
    TButton* btnSpace = CreateButton("Space", 85, row, 200, btnHeight);
    btnSpace->OnMouseDown = OnSpaceMouseDown;

    // Enter button
    TButton* btnEnter = CreateButton("Enter", 295, row, 100, btnHeight);
    btnEnter->OnMouseDown = OnEnterMouseDown;

    // Row PadNum1
    String row1PadNum[] = {"/","*","-"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row1PadNum[i], 10 + (i+12)*55, 10, 50, 45);
        btn->Tag = (NativeInt)(wchar_t)row1PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        padbuttons.push_back(btn);
    }

    // Row PadNum2
    String row2PadNum[] = {"7","8","9"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row2PadNum[i], 10 + (i+12)*55, 60, 50, 45);
        btn->Tag = (NativeInt)(wchar_t)row2PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
		padbuttons.push_back(btn);
    }

    // Plus button NumPad
    TButton* btnPlusNumPad = CreateButton("+", 835, 60, 50, 2*45);
    btnPlusNumPad->Tag = (NativeInt)(wchar_t)'+';
    btnPlusNumPad->OnMouseDown = OnKeyButtonMouseDown;
	padbuttons.push_back(btnPlusNumPad);

    // Row PadNum3
    String row3PadNum[] = {"4","5","6"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row3PadNum[i], 10 + (i+12)*55, 110, 50, 45);
        btn->Tag = (NativeInt)(wchar_t)row3PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
		padbuttons.push_back(btn);
    }

    // Row PadNum4
    String row4PadNum[] = {"1","2","3"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row4PadNum[i], 10 + (i+12)*55, 160, 50, 45);
        btn->Tag = (NativeInt)(wchar_t)row4PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
		padbuttons.push_back(btn);
    }

    // Enter button NumPad
    TButton* btnEnterNumPad = CreateButton("Enter", 835, 160, 50, 2*45);
    btnEnterNumPad->OnMouseDown = OnEnterMouseDown;
	padbuttons.push_back(btnEnterNumPad);

    // Row PadNum5
    String row5PadNum[] = {"0","."};
    for (int i=0; i < 2; i++) {
        TButton* btn = CreateButton(row5PadNum[i], 10 + (i+12)*55, 210, 50, 45);
        btn->Tag = (NativeInt)(wchar_t)row5PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
		padbuttons.push_back(btn);
    }

    // Mettre le NumPad invisible
    for (int i = 0; i < padbuttons.size(); i++)
    {
		padbuttons[i]->Visible = false;
	}
    // Mettre les autres langues invisibles
	for (int i = 0; i < qwerty.size(); i++)
	{
		qwerty[i]->Visible = false;
	}
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
// Capture the target window
//---------------------------------------------------------------------------
void TFormKeyboard::CaptureTargetWindow()
{
    HWND hForeground = GetForegroundWindow();

    // Ne capturer que si ce n'est PAS notre propre clavier
    if (hForeground != NULL && hForeground != Handle)
    {
        FTargetHandle = hForeground;
    }
}

//---------------------------------------------------------------------------
// Form Show event
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::FormShow(TObject *Sender)
{
    CaptureTargetWindow();
}

//---------------------------------------------------------------------------
// Key button MouseDown handler (lettres, chiffres, caractères)
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnKeyButtonMouseDown(TObject *Sender,
                                                     TMouseButton Button,
                                                     TShiftState Shift,
                                                     int X, int Y)
{
    if (Button != mbLeft) return;

    TButton* btn = dynamic_cast<TButton*>(Sender);
    if (!btn) return;

    // Capturer la fenêtre cible
    CaptureTargetWindow();
    if (!FTargetHandle) return;

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
// Shift button MouseDown handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnShiftMouseDown(TObject *Sender,
                                                 TMouseButton Button,
                                                 TShiftState Shift,
                                                 int X, int Y)
{
    if (Button != mbLeft) return;
    FShiftActive = !FShiftActive;
}

//---------------------------------------------------------------------------
// Backspace button MouseDown handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnBackspaceMouseDown(TObject *Sender,
                                                     TMouseButton Button,
                                                     TShiftState Shift,
                                                     int X, int Y)
{
    if (Button != mbLeft) return;

    CaptureTargetWindow();
    SendKeyToTarget(VK_BACK);
}

//---------------------------------------------------------------------------
// Enter button MouseDown handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnEnterMouseDown(TObject *Sender,
                                                 TMouseButton Button,
                                                 TShiftState Shift,
                                                 int X, int Y)
{
    if (Button != mbLeft) return;

    CaptureTargetWindow();
    SendKeyToTarget(VK_RETURN);
}

//---------------------------------------------------------------------------
// Space button MouseDown handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnSpaceMouseDown(TObject *Sender,
                                                 TMouseButton Button,
                                                 TShiftState Shift,
                                                 int X, int Y)
{
    if (Button != mbLeft) return;

    CaptureTargetWindow();
    SendCharToTarget(' ');
}

//---------------------------------------------------------------------------
// Arrow buttons MouseDown handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnArrowMouseDown(TObject *Sender,
                                                 TMouseButton Button,
                                                 TShiftState Shift,
                                                 int X, int Y)
{
    if (Button != mbLeft) return;

    TButton* btn = dynamic_cast<TButton*>(Sender);
    if (!btn) return;

    CaptureTargetWindow();

    BYTE vkCode = (BYTE)btn->Tag;
    SendArrowKeyToTarget(vkCode);
}

//---------------------------------------------------------------------------
// NumPad button Click handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnNumPadClick(TObject *Sender)
{
    NumPadActive = !NumPadActive;
    if (NumPadActive) {
        ClientWidth = 920;
        for (int i = 0; i < padbuttons.size(); i++)
        {
			padbuttons[i]->Visible = true;
        }
    }
    else {
        ClientWidth = 700;
		for (int i = 0; i < padbuttons.size(); i++)
        {
			padbuttons[i]->Visible = false;
        }
    }
}

//---------------------------------------------------------------------------
// Send a character to the target control
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SendCharToTarget(wchar_t ch)
{
    if (!FTargetHandle || !IsWindow(FTargetHandle)) return;

    // Donner le focus à la fenêtre cible
    SetForegroundWindow(FTargetHandle);
    Sleep(20);

    // Utiliser SendInput au lieu de PostMessage
    INPUT allInputs[4] = {};  // Max : Shift down + Key down + Key up + Shift up
    int inputCount = 0;

    // Convertir le caractère en Virtual Key
    SHORT vk = VkKeyScanW(ch);
    BYTE vkCode = LOBYTE(vk);
    BYTE shiftState = HIBYTE(vk);

    // Si le caractère nécessite Shift, l'ajouter
    if (shiftState & 1) {
        allInputs[inputCount].type = INPUT_KEYBOARD;
        allInputs[inputCount].ki.wVk = VK_SHIFT;
        allInputs[inputCount].ki.dwFlags = 0;
        inputCount++;
    }

    // Key Down
    allInputs[inputCount].type = INPUT_KEYBOARD;
    allInputs[inputCount].ki.wVk = vkCode;
    allInputs[inputCount].ki.dwFlags = 0;
    inputCount++;

    // Key Up
    allInputs[inputCount].type = INPUT_KEYBOARD;
    allInputs[inputCount].ki.wVk = vkCode;
    allInputs[inputCount].ki.dwFlags = KEYEVENTF_KEYUP;
    inputCount++;

    // Si Shift était nécessaire, le relâcher
    if (shiftState & 1) {
        allInputs[inputCount].type = INPUT_KEYBOARD;
        allInputs[inputCount].ki.wVk = VK_SHIFT;
        allInputs[inputCount].ki.dwFlags = KEYEVENTF_KEYUP;
        inputCount++;
    }

    SendInput(inputCount, allInputs, sizeof(INPUT));
}

//---------------------------------------------------------------------------
// Send a virtual key to the target control
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SendKeyToTarget(WORD vKey)
{
    if (!FTargetHandle || !IsWindow(FTargetHandle)) return;

    // Donner le focus à la fenêtre cible
    SetForegroundWindow(FTargetHandle);
    Sleep(20);

    // Utiliser SendInput au lieu de PostMessage
    INPUT inputs[2] = {};

    // Key Down
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = vKey;
    inputs[0].ki.dwFlags = 0;

    // Key Up
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = vKey;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, inputs, sizeof(INPUT));
}

//---------------------------------------------------------------------------
// Send arrow key to target window
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SendArrowKeyToTarget(BYTE vkArrowCode)
{
    if (FTargetHandle == NULL || !IsWindow(FTargetHandle))
    {
        CaptureTargetWindow();
        if (FTargetHandle == NULL) return;
    }

    SetForegroundWindow(FTargetHandle);
    Sleep(20);

    INPUT inputs[2] = {};

    // Key Down
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = vkArrowCode;
    inputs[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
    inputs[0].ki.wScan = 0;
    inputs[0].ki.time = 0;
    inputs[0].ki.dwExtraInfo = 0;

    // Key Up
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = vkArrowCode;
    inputs[1].ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
    inputs[1].ki.wScan = 0;
    inputs[1].ki.time = 0;
    inputs[1].ki.dwExtraInfo = 0;

    SendInput(2, inputs, sizeof(INPUT));
}
//---------------------------------------------------------------------------


void __fastcall TFormKeyboard::OnLanguageClick(TObject *Sender)
{
    etatlangue += 1;
	if (etatlangue >= 2)
	{
        etatlangue=AZERTY;
	}
	if (etatlangue == AZERTY)
	{
		for (int i = 0; i < azerty.size(); i++)
		{
			azerty[i]->Visible = true;
			qwerty[i]->Visible = false;
		}
    }
    else if (etatlangue == QWERTY) {
		for (int i = 0; i < qwerty.size(); i++)
        {
			qwerty[i]->Visible = true;
			azerty[i]->Visible = false;
        }
    }
}

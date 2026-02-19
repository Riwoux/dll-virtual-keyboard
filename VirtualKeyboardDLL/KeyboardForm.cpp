//---------------------------------------------------------------------------
// KeyboardForm.cpp - Simple Virtual Keyboard Implementation
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#pragma hdrstop
#include "KeyboardForm.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma resource "keyboard_resources.res"
TFormKeyboard *FormKeyboard;

#define AZERTY 0
#define QWERTY 1
#define QWERTZ 2
int langues[3]={AZERTY, QWERTY, QWERTZ};

__fastcall TFormKeyboard::TFormKeyboard(TComponent* Owner)
    : TForm(Owner), FTargetHandle(NULL), FShiftActive(false), FMajActive(false),
    NumPadActive(false), etatlangue(QWERTY), MajOffImage(NULL), MajOnImage(NULL),
    imgMaj(NULL), pnlMaj(NULL), pnlShift(NULL)
{
    LoadPNGFromResource();

    SizeRatio = 1.3; // Modifier cette valeur pour changer la taille du clavier

    const int BASE_BTN_WIDTH = 50;
    const int BASE_BTN_HEIGHT = 45;
    const int BASE_SPACING = 5;
    const int BASE_FORM_WIDTH = 800;
    const int BASE_FORM_HEIGHT = 270;
    const int BASE_NUMPAD_WIDTH = 220;
    const int btnWidth = (int)(BASE_BTN_WIDTH * SizeRatio);
    const int btnHeight = (int)(BASE_BTN_HEIGHT * SizeRatio);
    const int spacing = (int)(BASE_SPACING * SizeRatio);

    // Form configuration
    BorderStyle = bsNone;
    FormStyle = fsStayOnTop;
    Position = poScreenCenter;
    Caption = "Virtual Keyboard";
    ClientWidth = (int)(BASE_FORM_WIDTH * SizeRatio);
    ClientHeight = (int)(BASE_FORM_HEIGHT * SizeRatio);
    Color = (TColor)0x00cccccc;
    OnMouseDown = FormMouseDown;
    OnShow = FormShow;

    int row = (int)(10 * SizeRatio);

    // Azerty Row 1
    String azerty1Keys[] = {"&&", "é", '"', "'", "(", "-", "è", "_", "ç", "à", ")","="};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(azerty1Keys[i],
                                    (int)(10 * SizeRatio) + i * (btnWidth + spacing),
                                    row, btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)azerty1Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
    }
    // Qwerty Row 1
    String qwerty1Keys[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "="};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwerty1Keys[i],
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)qwerty1Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwerty.push_back(btn);
    }
    // Qwerty Row 1
    String qwertz1Keys[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "ß", "´"};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertz1Keys[i],
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)qwertz1Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwertz.push_back(btn);
    }

    // Changer la langue
    TButton* btnLanguage = CreateButton("Language", (int)(670 * SizeRatio), row,
                                       (int)(75 * SizeRatio), btnHeight);
    btnLanguage->OnClick = OnLanguageClick;

    row += btnHeight + spacing;
    // Azerty Row 2
    String azerty2Keys[] = {"A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P", "^", "$"};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(azerty2Keys[i],
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)azerty2Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
    }
    // Qwerty Row 2
    String qwerty2Keys[] = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]"};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwerty2Keys[i],
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)qwerty2Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwerty.push_back(btn);
    }
    // Qwertz Row 2
    String qwertz2Keys[] = {"Q", "W", "E", "R", "T", "Z", "U", "I", "O", "P", "ü", "+"};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertz2Keys[i],
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)qwertz2Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwertz.push_back(btn);
    }

    // Backspace button
    TButton* btnBackspace = CreateButton("Delete", (int)(670 * SizeRatio), row,
                                        (int)(100 * SizeRatio), btnHeight);
    btnBackspace->OnMouseDown = OnBackspaceMouseDown;

    row += btnHeight + spacing;
    // Azerty Row 3
    String azerty3Keys[] = {"Q", "S", "D", "F", "G", "H", "J", "K", "L", "M", "ù", "*"};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(azerty3Keys[i],
                                   (int)(35 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)azerty3Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
    }
    // Qwerty Row 3
    String qwerty3Keys[] = {"A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "\\"};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwerty3Keys[i],
                                   (int)(35 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)qwerty3Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwerty.push_back(btn);
    }
    // Qwertz Row 3
    String qwertz3Keys[] = {"A", "S", "D", "F", "G", "H", "J", "K", "L", "ö", "ä", "#"};
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertz3Keys[i],
                                   (int)(35 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)qwertz3Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwertz.push_back(btn);
    }

    // Enter button
    TButton* btnEnter = CreateButton("Enter", (int)(695 * SizeRatio), row,
                                    (int)(100 * SizeRatio), btnHeight);
    btnEnter->OnMouseDown = OnEnterMouseDown;

    row += btnHeight + spacing;
    // Azerty Row 4
    String azerty4Keys[] = {"<", "W", "X", "C", "V", "B", "N", ",", ";",":"};
    for (int i = 0; i < 10; i++) {
        TButton* btn = CreateButton(azerty4Keys[i],
                                   (int)(5 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)azerty4Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
    }
    // Qwerty Row 4
    String qwerty4Keys[] = {"<", "Z", "X", "C", "V", "B", "N", "M", ",", "."};
    for (int i = 0; i < 10; i++) {
        TButton* btn = CreateButton(qwerty4Keys[i],
                                   (int)(5 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)qwerty4Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwerty.push_back(btn);
    }
    // Qwertz Row 4
    String qwertz4Keys[] = {"<", "Y", "X", "C", "V", "B", "N", "M", ",", "."};
    for (int i = 0; i < 10; i++) {
        TButton* btn = CreateButton(qwertz4Keys[i],
                                   (int)(5 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)qwertz4Keys[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwertz.push_back(btn);
    }

    // Special keys

    // Activer et desactiver NumPad
    TButton* btnNumPad = CreateButton("NumPad", (int)(670 * SizeRatio), row,
                                     (int)(75 * SizeRatio), (int)(1.5 * btnHeight));
    btnNumPad->OnClick = OnNumPadClick;

    // Up button
    TButton* btnUp = CreateButton("Up", (int)(555 * SizeRatio), row, btnWidth, btnHeight);
    btnUp->Tag = VK_UP;
    btnUp->OnMouseDown = OnArrowMouseDown;

    row += btnHeight + spacing;

    // Left button
    TButton* btnLeft = CreateButton("Left", (int)(500 * SizeRatio), row, btnWidth, btnHeight);
    btnLeft->Tag = VK_LEFT;
    btnLeft->OnMouseDown = OnArrowMouseDown;

    // Down button
    TButton* btnDown = CreateButton("Down", (int)(555 * SizeRatio), row, btnWidth, btnHeight);
    btnDown->Tag = VK_DOWN;
    btnDown->OnMouseDown = OnArrowMouseDown;

    // Right button
    TButton* btnRight = CreateButton("Right", (int)(610 * SizeRatio), row, btnWidth, btnHeight);
    btnRight->Tag = VK_RIGHT;
    btnRight->OnMouseDown = OnArrowMouseDown;

    // Shift button
    pnlShift = new TPanel(this);
    pnlShift->Parent = this;
    pnlShift->Left   = (int)(85 * SizeRatio);
    pnlShift->Top    = row;
    pnlShift->Width  = (int)(70 * SizeRatio);
    pnlShift->Height = btnHeight;
    pnlShift->Caption    = "Shift";
    pnlShift->BevelOuter = bvRaised;
    pnlShift->ParentColor = false;
    pnlShift->Color      = clWhite;
    pnlShift->Cursor     = crHandPoint;
    pnlShift->Font->Size = (int)(10 * SizeRatio);
	pnlShift->OnMouseDown = OnShiftMouseDown;
    UpdateShiftButtonColor();

    // Maj button
    pnlMaj = CreateImageButton((int)(10 * SizeRatio), row,
                                  (int)(70 * SizeRatio), btnHeight);
    pnlMaj->OnMouseDown = OnMajMouseDown;

    // Space button
    TButton* btnSpace = CreateButton("Space", (int)(160 * SizeRatio), row,
                                    (int)(200 * SizeRatio), btnHeight);
    btnSpace->OnMouseDown = OnSpaceMouseDown;

    // Row PadNum1
    String row1PadNum[] = {"/","*","-"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row1PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(10 * SizeRatio), btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)row1PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        padbuttons.push_back(btn);
    }

    // Row PadNum2
    String row2PadNum[] = {"7","8","9"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row2PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(60 * SizeRatio), btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)row2PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        padbuttons.push_back(btn);
    }

    // Plus button NumPad
    TButton* btnPlusNumPad = CreateButton("+", (int)(1000 * SizeRatio),
                                         (int)(60 * SizeRatio), btnWidth,
                                         (int)(2 * btnHeight));
    btnPlusNumPad->Tag = (NativeInt)(wchar_t)'+';
    btnPlusNumPad->OnMouseDown = OnKeyButtonMouseDown;
    padbuttons.push_back(btnPlusNumPad);

    // Row PadNum3
    String row3PadNum[] = {"4","5","6"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row3PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(110 * SizeRatio), btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)row3PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        padbuttons.push_back(btn);
    }

    // Row PadNum4
    String row4PadNum[] = {"1","2","3"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row4PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(160 * SizeRatio), btnWidth, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)row4PadNum[i][1];
        btn->OnMouseDown = OnKeyButtonMouseDown;
        padbuttons.push_back(btn);
    }

    // Enter button NumPad
    TButton* btnEnterNumPad = CreateButton("Enter", (int)(1000 * SizeRatio),
                                          (int)(160 * SizeRatio), btnWidth,
                                          (int)(2 * btnHeight));
    btnEnterNumPad->OnMouseDown = OnEnterMouseDown;
    padbuttons.push_back(btnEnterNumPad);

    // Row PadNum5
    String row5PadNum[] = {"0","."};
    for (int i=0; i < 2; i++) {
        TButton* btn = CreateButton(row5PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(210 * SizeRatio), btnWidth, btnHeight);
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
        azerty[i]->Visible = false;
    }
}

__fastcall TFormKeyboard::~TFormKeyboard()
{
    if (MajOffImage) delete MajOffImage;
    if (MajOnImage) delete MajOnImage;
}

//---------------------------------------------------------------------------
// Create a normal button
//---------------------------------------------------------------------------
TButton* __fastcall TFormKeyboard::CreateButton(const String& Caption,
                                                 int Left, int Top, int Width,
                                                 int Height)
{
    TButton* btn = new TButton(this);
    btn->Parent = this;
    btn->Caption = Caption;
    btn->Left = Left;
    btn->Top = Top;
    btn->Width = Width;
    btn->Height = Height;
    btn->Font->Size = (int)(10 * SizeRatio);
    return btn;
}

//---------------------------------------------------------------------------
// Create an image button (Panel + TImage pour PNG)
//---------------------------------------------------------------------------
TPanel* __fastcall TFormKeyboard::CreateImageButton(int Left, int Top,
                                                     int Width, int Height)
{
    // Créer un panel comme conteneur
    TPanel* panel = new TPanel(this);
    panel->Parent = this;
    panel->Left = Left;
    panel->Top = Top;
    panel->Width = Width;
    panel->Height = Height;
    panel->BevelOuter = bvNone;
    panel->Caption = "";
    panel->Color = clBtnFace;
    panel->Cursor = crHandPoint;

    // Créer le composant TImage pour afficher le PNG
    imgMaj = new TImage(panel);
    imgMaj->Parent = panel;
    imgMaj->Align = alClient;
    imgMaj->Stretch = true;
    imgMaj->Proportional = true;
    imgMaj->Center = true;
    imgMaj->Transparent = true;

    imgMaj->OnMouseDown = OnMajMouseDown;

    UpdateMajButtonImage();

    return panel;
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
    if (FShiftActive || FMajActive) {
        if (ch >= 'A' && ch <= 'Z') {
            // Already uppercase
        } else if (ch >= 'a' && ch <= 'z') {
            ch = ch - 'a' + 'A';
        } else if (ch== '<') {
            ch = '>';
        } else if (etatlangue == AZERTY) {
        	if (ch == '&') ch = '1';
            else if (ch == 'é') ch = '2';
            else if (ch == '"') ch = '3';
            else if (ch == '\x27') ch = '4';
            else if (ch == '(') ch = '5';
            else if (ch == '-') ch = '6';
            else if (ch == 'è') ch = '7';
            else if (ch == '_') ch = '8';
            else if (ch == 'ç') ch = '9';
            else if (ch == 'à') ch = '0';
            else if (ch == ')') ch = '°';
            else if (ch == '=') ch = '+';
            else if (ch == '^') ch = '¨';
            else if (ch == '$') ch = '£';
            else if (ch == 'ù') ch = '%';
            else if (ch == '*') ch = 'µ';
            else if (ch == ',') ch = '?';
            else if (ch == ';') ch = '.';
            else if (ch == ':') ch = '/';
        } else if (etatlangue == QWERTY) {
        	if (ch == '1') ch = '!';
            else if (ch == '2') ch = '@';
            else if (ch == '3') ch = '#';
            else if (ch == '4') ch = '$';
            else if (ch == '5') ch = '%';
            else if (ch == '6') ch = '^';
            else if (ch == '7') ch = '&';
            else if (ch == '8') ch = '*';
            else if (ch == '9') ch = '(';
            else if (ch == '0') ch = ')';
            else if (ch == '-') ch = '_';
            else if (ch == '=') ch = '+';
            else if (ch == '[') ch = '{';
            else if (ch == ']') ch = '}';
            else if (ch == ';') ch = ':';
            else if (ch == '\x27') ch = '"';
            else if (ch == ',') ch = '<';
            else if (ch == '.') ch = '>';
            else if (ch == '/') ch = '?';
            else if (ch == '\\') ch = '\x7c';
        } else if (etatlangue == QWERTZ) {
            if (ch == '1') ch = '!';
            else if (ch == '2') ch = '"';
            else if (ch == '3') ch = L'\x00A7';
            else if (ch == '4') ch = '$';
            else if (ch == '5') ch = '%';
            else if (ch == '6') ch = '&';
            else if (ch == '7') ch = '/';
            else if (ch == '8') ch = '(';
            else if (ch == '9') ch = ')';
            else if (ch == '0') ch = '=';
            else if (ch == L'\x00DF') ch = '?';
            else if (ch == L'\x00B4') ch = '`';
            else if (ch == L'\x00FC') ch = L'\x00DC';
            else if (ch == '+') ch = '*';
            else if (ch == L'\x00F6') ch = L'\x00D6';
            else if (ch == L'\x00E4') ch = L'\x00C4';
            else if (ch == '#') ch = '\'';
            else if (ch == ',') ch = ';';
            else if (ch == '.') ch = ':';
        }
        FShiftActive = false; // Reset shift after one key
        UpdateShiftButtonColor();
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
    UpdateShiftButtonColor();
}

//---------------------------------------------------------------------------
// Maj button MouseDown handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnMajMouseDown(TObject *Sender,
                                                 TMouseButton Button,
                                                 TShiftState Shift,
                                                 int X, int Y)
{
    if (Button != mbLeft) return;
    FMajActive = !FMajActive;
    UpdateMajButtonImage();
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
        ClientWidth = (int)(1100 * SizeRatio);
        for (int i = 0; i < padbuttons.size(); i++)
        {
            padbuttons[i]->Visible = true;
        }
    }
    else {
        ClientWidth = (int)(800 * SizeRatio);
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

    INPUT inputs[2] = {};

    // Key Down avec Unicode
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = 0;
    inputs[0].ki.wScan = ch;
    inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;

    // Key Up avec Unicode
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 0;
    inputs[1].ki.wScan = ch;
    inputs[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;

    SendInput(2, inputs, sizeof(INPUT));
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
    if (etatlangue >= 3)
    {
        etatlangue=AZERTY;
    }
    if (etatlangue == AZERTY)
    {
        for (int i = 0; i < azerty.size(); i++)
        {
            azerty[i]->Visible = true;
            qwerty[i]->Visible = false;
            qwertz[i]->Visible = false;
        }
    } else if (etatlangue == QWERTY) {
        for (int i = 0; i < qwerty.size(); i++)
        {
            qwerty[i]->Visible = true;
            azerty[i]->Visible = false;
            qwertz[i]->Visible = false;
        }
    } else if (etatlangue == QWERTZ) {
        for (int i = 0; i < qwerty.size(); i++)
        {
            qwertz[i]->Visible = true;
            azerty[i]->Visible = false;
            qwerty[i]->Visible = false;
        }
    }
}

void __fastcall TFormKeyboard::FormMouseDown(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft) {
        ReleaseCapture();
        SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    }
}

void __fastcall TFormKeyboard::LoadPNGFromResource()
{
    try {
        MajOffImage = new TPngImage();
        MajOnImage = new TPngImage();

        // Définir le type de ressource RCDATA
        WideChar* ResTypeRCDATA = MAKEINTRESOURCEW(10);

        TResourceStream* rsOff = new TResourceStream(
            (NativeUInt)HInstance,
            "MAJ_OFF",
            ResTypeRCDATA
        );

        TResourceStream* rsOn = new TResourceStream(
            (NativeUInt)HInstance,
            "MAJ_ON",
            ResTypeRCDATA
        );

        MajOffImage->LoadFromStream(rsOff);
        MajOnImage->LoadFromStream(rsOn);

        delete rsOff;
        delete rsOn;
    }
    catch (Exception &e) {
        ShowMessage("Erreur lors du chargement des PNG: " + e.Message);

        if (!MajOffImage) MajOffImage = new TPngImage();
        if (!MajOnImage) MajOnImage = new TPngImage();
    }
}

void __fastcall TFormKeyboard::UpdateMajButtonImage()
{
    if (!imgMaj) return;

    if (FMajActive) {
        imgMaj->Picture->Assign(MajOnImage);
    } else {
        imgMaj->Picture->Assign(MajOffImage);
    }

    imgMaj->Refresh();
}
//---------------------------------------------------------------------------
// Met à jour la couleur du bouton Shift selon son état
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::UpdateShiftButtonColor()
{
    if (!pnlShift) return;
	pnlShift->ParentColor = false;
    pnlShift->Color      = clWhite;
    if (FShiftActive) {
        pnlShift->BevelOuter = bvLowered;
    } else {
        pnlShift->BevelOuter = bvRaised;
    }
    pnlShift->Refresh();
    pnlShift->Update();
}

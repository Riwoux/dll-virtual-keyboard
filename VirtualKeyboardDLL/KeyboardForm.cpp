//---------------------------------------------------------------------------
// KeyboardForm.cpp - Simple Virtual Keyboard Implementation
//---------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <Winapi.Windows.hpp>
#include <vcl.h>
#include <vector>
#pragma hdrstop
#include "KeyboardForm.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TFormKeyboard *FormKeyboard;

#define AZERTY 0
#define QWERTY 1
#define QWERTZ 2
int langues[3]={AZERTY, QWERTY, QWERTZ};

//---------------------------------------------------------------------------
// Helper function to create KeyData structs for bcc32 compatibility
//---------------------------------------------------------------------------
static KeyData MakeKey(const String& normalCaption, const String& shiftedCaption,
                       wchar_t normalChar, wchar_t shiftedChar)
{
    KeyData kd;
    kd.normalCaption = normalCaption;
    kd.shiftedCaption = shiftedCaption;
    kd.normalChar = normalChar;
    kd.shiftedChar = shiftedChar;
    return kd;
}

//---------------------------------------------------------------------------
// Initialize keyboard layout data with explicit normal/shifted mappings
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::InitializeKeyboardData()
{
    // AZERTY Layout Data
    // Row 1
    azertyData.push_back(MakeKey("&&", "1", L'&', L'1'));
    azertyData.push_back(MakeKey("é", "2", L'é', L'2'));
    azertyData.push_back(MakeKey("\"", "3", L'"', L'3'));
    azertyData.push_back(MakeKey("'", "4", L'\'', L'4'));
    azertyData.push_back(MakeKey("(", "5", L'(', L'5'));
    azertyData.push_back(MakeKey("-", "6", L'-', L'6'));
    azertyData.push_back(MakeKey("è", "7", L'è', L'7'));
    azertyData.push_back(MakeKey("_", "8", L'_', L'8'));
    azertyData.push_back(MakeKey("ç", "9", L'ç', L'9'));
    azertyData.push_back(MakeKey("à", "0", L'à', L'0'));
    azertyData.push_back(MakeKey(")", "°", L')', L'°'));
    azertyData.push_back(MakeKey("=", "+", L'=', L'+'));
    
    // Row 2
    azertyData.push_back(MakeKey("a", "A", L'a', L'A'));
    azertyData.push_back(MakeKey("z", "Z", L'z', L'Z'));
    azertyData.push_back(MakeKey("e", "E", L'e', L'E'));
    azertyData.push_back(MakeKey("r", "R", L'r', L'R'));
    azertyData.push_back(MakeKey("t", "T", L't', L'T'));
    azertyData.push_back(MakeKey("y", "Y", L'y', L'Y'));
    azertyData.push_back(MakeKey("u", "U", L'u', L'U'));
    azertyData.push_back(MakeKey("i", "I", L'i', L'I'));
    azertyData.push_back(MakeKey("o", "O", L'o', L'O'));
    azertyData.push_back(MakeKey("p", "P", L'p', L'P'));
    azertyData.push_back(MakeKey("^", "¨", L'^', L'¨'));
    azertyData.push_back(MakeKey("$", "£", L'$', L'£'));
    
    // Row 3
    azertyData.push_back(MakeKey("q", "Q", L'q', L'Q'));
    azertyData.push_back(MakeKey("s", "S", L's', L'S'));
    azertyData.push_back(MakeKey("d", "D", L'd', L'D'));
    azertyData.push_back(MakeKey("f", "F", L'f', L'F'));
    azertyData.push_back(MakeKey("g", "G", L'g', L'G'));
    azertyData.push_back(MakeKey("h", "H", L'h', L'H'));
    azertyData.push_back(MakeKey("j", "J", L'j', L'J'));
    azertyData.push_back(MakeKey("k", "K", L'k', L'K'));
    azertyData.push_back(MakeKey("l", "L", L'l', L'L'));
    azertyData.push_back(MakeKey("m", "M", L'm', L'M'));
    azertyData.push_back(MakeKey("ù", "%", L'ù', L'%'));
    azertyData.push_back(MakeKey("*", "µ", L'*', L'µ'));
    
    // Row 4
    azertyData.push_back(MakeKey("<", ">", L'<', L'>'));
    azertyData.push_back(MakeKey("w", "W", L'w', L'W'));
    azertyData.push_back(MakeKey("x", "X", L'x', L'X'));
    azertyData.push_back(MakeKey("c", "C", L'c', L'C'));
    azertyData.push_back(MakeKey("v", "V", L'v', L'V'));
    azertyData.push_back(MakeKey("b", "B", L'b', L'B'));
    azertyData.push_back(MakeKey("n", "N", L'n', L'N'));
    azertyData.push_back(MakeKey(",", "?", L',', L'?'));
    azertyData.push_back(MakeKey(";", ".", L';', L'.'));
    azertyData.push_back(MakeKey(":", "/", L':', L'/'));
    azertyData.push_back(MakeKey("!", "§", L'!', L'\x00A7'));
    
    // QWERTY Layout Data
    // Row 1
    qwertyData.push_back(MakeKey("1", "!", L'1', L'!'));
    qwertyData.push_back(MakeKey("2", "@", L'2', L'@'));
    qwertyData.push_back(MakeKey("3", "#", L'3', L'#'));
    qwertyData.push_back(MakeKey("4", "$", L'4', L'$'));
    qwertyData.push_back(MakeKey("5", "%", L'5', L'%'));
    qwertyData.push_back(MakeKey("6", "^", L'6', L'^'));
    qwertyData.push_back(MakeKey("7", "&&", L'7', L'&'));
    qwertyData.push_back(MakeKey("8", "*", L'8', L'*'));
    qwertyData.push_back(MakeKey("9", "(", L'9', L'('));
    qwertyData.push_back(MakeKey("0", ")", L'0', L')'));
    qwertyData.push_back(MakeKey("-", "_", L'-', L'_'));
    qwertyData.push_back(MakeKey("=", "+", L'=', L'+'));
    
    // Row 2
    qwertyData.push_back(MakeKey("q", "Q", L'q', L'Q'));
    qwertyData.push_back(MakeKey("w", "W", L'w', L'W'));
    qwertyData.push_back(MakeKey("e", "E", L'e', L'E'));
    qwertyData.push_back(MakeKey("r", "R", L'r', L'R'));
    qwertyData.push_back(MakeKey("t", "T", L't', L'T'));
    qwertyData.push_back(MakeKey("y", "Y", L'y', L'Y'));
    qwertyData.push_back(MakeKey("u", "U", L'u', L'U'));
    qwertyData.push_back(MakeKey("i", "I", L'i', L'I'));
    qwertyData.push_back(MakeKey("o", "O", L'o', L'O'));
    qwertyData.push_back(MakeKey("p", "P", L'p', L'P'));
    qwertyData.push_back(MakeKey("[", "{", L'[', L'{'));
    qwertyData.push_back(MakeKey("]", "}", L']', L'}'));
    
    // Row 3
    qwertyData.push_back(MakeKey("a", "A", L'a', L'A'));
    qwertyData.push_back(MakeKey("s", "S", L's', L'S'));
    qwertyData.push_back(MakeKey("d", "D", L'd', L'D'));
    qwertyData.push_back(MakeKey("f", "F", L'f', L'F'));
    qwertyData.push_back(MakeKey("g", "G", L'g', L'G'));
    qwertyData.push_back(MakeKey("h", "H", L'h', L'H'));
    qwertyData.push_back(MakeKey("j", "J", L'j', L'J'));
    qwertyData.push_back(MakeKey("k", "K", L'k', L'K'));
    qwertyData.push_back(MakeKey("l", "L", L'l', L'L'));
    qwertyData.push_back(MakeKey(";", ":", L';', L':'));
    qwertyData.push_back(MakeKey("'", "\"", L'\'', L'"'));
    qwertyData.push_back(MakeKey("\\", "|", L'\\', L'|'));
    
    // Row 4
    qwertyData.push_back(MakeKey("<", ">", L'<', L'>'));
    qwertyData.push_back(MakeKey("z", "Z", L'z', L'Z'));
    qwertyData.push_back(MakeKey("x", "X", L'x', L'X'));
    qwertyData.push_back(MakeKey("c", "C", L'c', L'C'));
    qwertyData.push_back(MakeKey("v", "V", L'v', L'V'));
    qwertyData.push_back(MakeKey("b", "B", L'b', L'B'));
    qwertyData.push_back(MakeKey("n", "N", L'n', L'N'));
    qwertyData.push_back(MakeKey("m", "M", L'm', L'M'));
    qwertyData.push_back(MakeKey(",", "<", L',', L'<'));
    qwertyData.push_back(MakeKey(".", ">", L'.', L'>'));
    qwertyData.push_back(MakeKey("/", "?", L'/', L'?'));
    
    // QWERTZ Layout Data
    // Row 1
    qwertzData.push_back(MakeKey("1", "!", L'1', L'!'));
    qwertzData.push_back(MakeKey("2", "\"", L'2', L'"'));
    qwertzData.push_back(MakeKey("3", "§", L'3', L'\x00A7'));
    qwertzData.push_back(MakeKey("4", "$", L'4', L'$'));
    qwertzData.push_back(MakeKey("5", "%", L'5', L'%'));
    qwertzData.push_back(MakeKey("6", "&&", L'6', L'&'));
    qwertzData.push_back(MakeKey("7", "/", L'7', L'/'));
    qwertzData.push_back(MakeKey("8", "(", L'8', L'('));
    qwertzData.push_back(MakeKey("9", ")", L'9', L')'));
    qwertzData.push_back(MakeKey("0", "=", L'0', L'='));
    qwertzData.push_back(MakeKey("ß", "?", L'\x00DF', L'?'));
    qwertzData.push_back(MakeKey("´", "`", L'\x00B4', L'`'));
    
    // Row 2
    qwertzData.push_back(MakeKey("q", "Q", L'q', L'Q'));
    qwertzData.push_back(MakeKey("w", "W", L'w', L'W'));
    qwertzData.push_back(MakeKey("e", "E", L'e', L'E'));
    qwertzData.push_back(MakeKey("r", "R", L'r', L'R'));
    qwertzData.push_back(MakeKey("t", "T", L't', L'T'));
    qwertzData.push_back(MakeKey("z", "Z", L'z', L'Z'));
    qwertzData.push_back(MakeKey("u", "U", L'u', L'U'));
    qwertzData.push_back(MakeKey("i", "I", L'i', L'I'));
    qwertzData.push_back(MakeKey("o", "O", L'o', L'O'));
    qwertzData.push_back(MakeKey("p", "P", L'p', L'P'));
    qwertzData.push_back(MakeKey("ü", "Ü", L'\x00FC', L'\x00DC'));
    qwertzData.push_back(MakeKey("+", "*", L'+', L'*'));
    
    // Row 3
    qwertzData.push_back(MakeKey("a", "A", L'a', L'A'));
    qwertzData.push_back(MakeKey("s", "S", L's', L'S'));
    qwertzData.push_back(MakeKey("d", "D", L'd', L'D'));
    qwertzData.push_back(MakeKey("f", "F", L'f', L'F'));
    qwertzData.push_back(MakeKey("g", "G", L'g', L'G'));
    qwertzData.push_back(MakeKey("h", "H", L'h', L'H'));
    qwertzData.push_back(MakeKey("j", "J", L'j', L'J'));
    qwertzData.push_back(MakeKey("k", "K", L'k', L'K'));
    qwertzData.push_back(MakeKey("l", "L", L'l', L'L'));
    qwertzData.push_back(MakeKey("ö", "Ö", L'\x00F6', L'\x00D6'));
    qwertzData.push_back(MakeKey("ä", "Ä", L'\x00E4', L'\x00C4'));
    qwertzData.push_back(MakeKey("#", "'", L'#', L'\''));
    
    // Row 4
    qwertzData.push_back(MakeKey("<", ">", L'<', L'>'));
    qwertzData.push_back(MakeKey("y", "Y", L'y', L'Y'));
    qwertzData.push_back(MakeKey("x", "X", L'x', L'X'));
    qwertzData.push_back(MakeKey("c", "C", L'c', L'C'));
    qwertzData.push_back(MakeKey("v", "V", L'v', L'V'));
    qwertzData.push_back(MakeKey("b", "B", L'b', L'B'));
    qwertzData.push_back(MakeKey("n", "N", L'n', L'N'));
    qwertzData.push_back(MakeKey("m", "M", L'm', L'M'));
    qwertzData.push_back(MakeKey(",", ";", L',', L';'));
    qwertzData.push_back(MakeKey(".", ":", L'.', L':'));
    qwertzData.push_back(MakeKey("-", "_", L'-', L'_'));
}

//---------------------------------------------------------------------------
__fastcall TFormKeyboard::TFormKeyboard(TComponent* Owner)
    : TForm(Owner), FTargetHandle(NULL), FShiftActive(false), FMajActive(false),
    NumPadActive(false), etatlangue(QWERTY), btnShift(NULL), btnMaj(NULL)
{
    // Initialize keyboard layout data FIRST
    InitializeKeyboardData();

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

    FDeadPending = false;
    FDeadChar = 0;
    int row = (int)(10 * SizeRatio);

    // Azerty Row 1 - Store index in Tag, use normalCaption from data
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(azertyData[i].normalCaption,
                                    (int)(10 * SizeRatio) + i * (btnWidth + spacing),
                                    row, btnWidth, btnHeight);
        btn->Tag = i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
    }
    // Qwerty Row 1
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertyData[i].normalCaption,
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwerty.push_back(btn);
    }
    // Qwertz Row 1
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertzData[i].normalCaption,
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwertz.push_back(btn);
    }

    // Changer la langue
    TButton* btnLanguage = CreateButton("Language", (int)(695 * SizeRatio), row,
                                       (int)(100 * SizeRatio), btnHeight);
    btnLanguage->OnClick = OnLanguageClick;

    row += btnHeight + spacing;
    // Azerty Row 2
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(azertyData[12 + i].normalCaption,
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 12 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
    }
    // Qwerty Row 2
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertyData[12 + i].normalCaption,
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 12 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwerty.push_back(btn);
    }
    // Qwertz Row 2
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertzData[12 + i].normalCaption,
                                   (int)(10 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 12 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwertz.push_back(btn);
    }

    // Backspace button
    TButton* btnBackspace = CreateButton("Delete", (int)(670 * SizeRatio), row,
                                        (int)(125 * SizeRatio), btnHeight);
    btnBackspace->OnMouseDown = OnBackspaceMouseDown;

    row += btnHeight + spacing;
    // Azerty Row 3
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(azertyData[24 + i].normalCaption,
                                   (int)(35 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 24 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
    }
    // Qwerty Row 3
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertyData[24 + i].normalCaption,
                                   (int)(35 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 24 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwerty.push_back(btn);
    }
    // Qwertz Row 3
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(qwertzData[24 + i].normalCaption,
                                   (int)(35 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 24 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwertz.push_back(btn);
    }

    // Enter button
    TButton* btnEnter = CreateButton("Enter", (int)(695 * SizeRatio), row,
                                    (int)(100 * SizeRatio), btnHeight);
    btnEnter->OnMouseDown = OnEnterMouseDown;

    row += btnHeight + spacing;
    // Azerty Row 4
    for (int i = 0; i < 11; i++) {
        TButton* btn = CreateButton(azertyData[36 + i].normalCaption,
                                   (int)(5 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 36 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        azerty.push_back(btn);
    }
    // Qwerty Row 4
    for (int i = 0; i < 11; i++) {
        TButton* btn = CreateButton(qwertyData[36 + i].normalCaption,
                                   (int)(5 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 36 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwerty.push_back(btn);
    }
    // Qwertz Row 4
    for (int i = 0; i < 11; i++) {
        TButton* btn = CreateButton(qwertzData[36 + i].normalCaption,
                                   (int)(5 * SizeRatio) + i * (btnWidth + spacing), row,
                                   btnWidth, btnHeight);
        btn->Tag = 36 + i;  // Store index, not character
        btn->OnMouseDown = OnKeyButtonMouseDown;
        qwertz.push_back(btn);
    }

    // Special keys

    // Activer et desactiver NumPad
    TButton* btnNumPad = CreateButton("NumPad", (int)(720 * SizeRatio), row,
                                     (int)(75 * SizeRatio), (int)(1.5 * btnHeight));
    btnNumPad->OnClick = OnNumPadClick;

    // Up button
    TButton* btnUp = CreateButton("Up", (int)(610 * SizeRatio), row, btnWidth, btnHeight);
    btnUp->Tag = VK_UP;
    btnUp->OnMouseDown = OnArrowMouseDown;

    row += btnHeight + spacing;

    // Left button
    TButton* btnLeft = CreateButton("Left", (int)(555 * SizeRatio), row, btnWidth, btnHeight);
    btnLeft->Tag = VK_LEFT;
    btnLeft->OnMouseDown = OnArrowMouseDown;

    // Down button
    TButton* btnDown = CreateButton("Down", (int)(610 * SizeRatio), row, btnWidth, btnHeight);
    btnDown->Tag = VK_DOWN;
    btnDown->OnMouseDown = OnArrowMouseDown;

    // Right button
    TButton* btnRight = CreateButton("Right", (int)(665 * SizeRatio), row, btnWidth, btnHeight);
    btnRight->Tag = VK_RIGHT;
    btnRight->OnMouseDown = OnArrowMouseDown;

    // Shift button
    btnShift = CreateButton("Shift", (int)(85 * SizeRatio), row,
                            (int)(70 * SizeRatio), btnHeight);
    btnShift->OnMouseDown = OnShiftMouseDown;
    UpdateShiftButtonState();

    // Maj button
    btnMaj = CreateButton("CapsLock", (int)(10 * SizeRatio), row,
                            (int)(70 * SizeRatio), btnHeight);
    btnMaj->OnMouseDown = OnMajMouseDown;
    UpdateMajButtonState();

    // Space button
    TButton* btnSpace = CreateButton("Space", (int)(160 * SizeRatio), row,
                                    (int)(390 * SizeRatio), btnHeight);
    btnSpace->OnMouseDown = OnSpaceMouseDown;

    // Row PadNum1
    String row1PadNum[] = {"/","*","-"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row1PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(10 * SizeRatio), btnWidth, btnHeight);
        if (row1PadNum[i].Length() > 0) {
            btn->Tag = (NativeInt)(wchar_t)row1PadNum[i][1];
        }
        btn->OnMouseDown = OnNumPadKeyMouseDown;  // Use separate handler
        padbuttons.push_back(btn);
    }

    // Row PadNum2
    String row2PadNum[] = {"7","8","9"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row2PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(60 * SizeRatio), btnWidth, btnHeight);
        if (row2PadNum[i].Length() > 0) {
            btn->Tag = (NativeInt)(wchar_t)row2PadNum[i][1];
        }
        btn->OnMouseDown = OnNumPadKeyMouseDown;  // Use separate handler
        padbuttons.push_back(btn);
    }

    // Plus button NumPad
    TButton* btnPlusNumPad = CreateButton("+", (int)(1000 * SizeRatio),
                                         (int)(60 * SizeRatio), btnWidth,
                                         (int)(2 * btnHeight));
    btnPlusNumPad->Tag = (NativeInt)(wchar_t)'+';
    btnPlusNumPad->OnMouseDown = OnNumPadKeyMouseDown;  // Use separate handler
    padbuttons.push_back(btnPlusNumPad);

    // Row PadNum3
    String row3PadNum[] = {"4","5","6"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row3PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(110 * SizeRatio), btnWidth, btnHeight);
        if (row3PadNum[i].Length() > 0) {
            btn->Tag = (NativeInt)(wchar_t)row3PadNum[i][1];
        }
        btn->OnMouseDown = OnNumPadKeyMouseDown;  // Use separate handler
        padbuttons.push_back(btn);
    }

    // Row PadNum4
    String row4PadNum[] = {"1","2","3"};
    for (int i=0; i < 3; i++) {
        TButton* btn = CreateButton(row4PadNum[i],
                                   (int)((10 + (i+15)*55) * SizeRatio),
                                   (int)(160 * SizeRatio), btnWidth, btnHeight);
        if (row4PadNum[i].Length() > 0) {
            btn->Tag = (NativeInt)(wchar_t)row4PadNum[i][1];
        }
        btn->OnMouseDown = OnNumPadKeyMouseDown;  // Use separate handler
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
    TButton* btn0 = CreateButton("0", (int)((10 + (15)*55) * SizeRatio),
                                   (int)(210 * SizeRatio), 105*SizeRatio, btnHeight);
    btn0->Tag = (NativeInt)(wchar_t)row5PadNum[0][1];
    btn0->OnMouseDown = OnNumPadKeyMouseDown;  // Use separate handler
    padbuttons.push_back(btn0);

    TButton* btnpoint = CreateButton(".", (int)((10 + (17)*55) * SizeRatio),
                                   (int)(210 * SizeRatio), btnWidth, btnHeight);
    btnpoint->Tag = (NativeInt)(wchar_t)row5PadNum[1][1];
    btnpoint->OnMouseDown = OnNumPadKeyMouseDown;  // Use separate handler
    padbuttons.push_back(btnpoint);

    // Mettre le NumPad invisible
    for (int i = 0; i < padbuttons.size(); i++)
    {
        padbuttons[i]->Visible = false;
    }

    // D'abord définir la langue AVANT de mettre à jour les labels
    etatlangue = AZERTY;

    // Configurer la visibilité des boutons
    for (int i = 0; i < azerty.size(); i++)
    {
        azerty[i]->Visible = true;
        qwerty[i]->Visible = false;
        qwertz[i]->Visible = false;
    }

    // Initialiser les labels des boutons selon l'état initial (maintenant en AZERTY)
    UpdateAllButtonLabels();
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

    // Determine which data vector to use based on current language
    std::vector<KeyData>* activeData = NULL;
    if (etatlangue == AZERTY) {
        activeData = &azertyData;
    } else if (etatlangue == QWERTY) {
        activeData = &qwertyData;
    } else if (etatlangue == QWERTZ) {
        activeData = &qwertzData;
    }
    
    if (!activeData) return;
    
    int index = btn->Tag;  // Tag stores index into data vector
    if (index < 0 || index >= activeData->size()) return;
    
    const KeyData& keyData = (*activeData)[index];
    bool applyShift = (FShiftActive || FMajActive);
    
    // Get the character to send based on shift state
    wchar_t ch = applyShift ? keyData.shiftedChar : keyData.normalChar;
    
    // Désactiver Shift après utilisation (mais pas Maj qui reste verrouillé)
    if (FShiftActive) {
        FShiftActive = false;
        UpdateShiftButtonState();
        UpdateAllButtonLabels();
    }

	// --- Gestion des touches mortes ---
    // Si l'utilisateur clique une touche morte, on la met en attente
    if (IsDeadKey(ch)) {
        // Double appui sur la même touche morte => on sort le caractère espacé (^^ => ^)
        if (FDeadPending && FDeadChar == ch) {
            SendCharToTarget(ch);
            FDeadPending = false;
            FDeadChar = 0;
            return;
        }

        FDeadPending = true;
        FDeadChar = ch;
        return;
    }

    // Si une touche morte est en attente, on essaie de composer
    if (FDeadPending) {
        // Si l'utilisateur tape espace après l'accent => sortir l'accent seul
        if (ch == L' ') {
            SendCharToTarget(FDeadChar);
            FDeadPending = false;
            FDeadChar = 0;
            return;
        }

        wchar_t composed = ComposeDeadKey(FDeadChar, ch);
        if (composed != 0) {
            SendCharToTarget(composed);
        } else {
            // Envoie l'accent puis la lettre
            SendCharToTarget(FDeadChar);
            SendCharToTarget(ch);
        }

        FDeadPending = false;
        FDeadChar = 0;
        return;
    }


    SendCharToTarget(ch);
}

//---------------------------------------------------------------------------
// NumPad key button MouseDown handler
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnNumPadKeyMouseDown(TObject *Sender,
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

    // For NumPad buttons, Tag still stores the character directly
    wchar_t ch = (wchar_t)btn->Tag;
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
    UpdateShiftButtonState();
    UpdateAllButtonLabels();
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
    UpdateMajButtonState();
    UpdateAllButtonLabels();
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
    
    // Mettre à jour les labels après changement de langue
    UpdateAllButtonLabels();
}

void __fastcall TFormKeyboard::FormMouseDown(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft) {
        ReleaseCapture();
        SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    }
}
//---------------------------------------------------------------------------
// Met à jour les labels de tous les boutons selon l'état Shift/Maj
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::UpdateAllButtonLabels()
{
    bool isShifted = (FShiftActive || FMajActive);
    
    // Determine which vector of buttons and data is currently visible
    std::vector<TButton*>* activeButtons = NULL;
    std::vector<KeyData>* activeData = NULL;
    
    if (etatlangue == AZERTY) {
        activeButtons = &azerty;
        activeData = &azertyData;
    } else if (etatlangue == QWERTY) {
        activeButtons = &qwerty;
        activeData = &qwertyData;
    } else if (etatlangue == QWERTZ) {
        activeButtons = &qwertz;
        activeData = &qwertzData;
    }
    
    if (!activeButtons || !activeData) return;
    
    // Update each button using the KeyData
    for (int i = 0; i < activeButtons->size(); i++) {
        TButton* btn = (*activeButtons)[i];
        if (!btn) continue;
        
        int index = btn->Tag;  // Tag now stores index into data vector
        if (index < 0 || index >= activeData->size()) continue;
        
        const KeyData& keyData = (*activeData)[index];
        btn->Caption = isShifted ? keyData.shiftedCaption : keyData.normalCaption;
    }
}

//---------------------------------------------------------------------------
// Met à jour l'apparence du bouton Shift selon son état
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::UpdateShiftButtonState()
{
    if (!btnShift) return;

    if (FShiftActive) {
        btnShift->Font->Style = TFontStyles() << fsBold;  // Gras quand actif
    } else {
        btnShift->Font->Style = TFontStyles();  // Normal quand inactif
    }
}
//---------------------------------------------------------------------------
// Met à jour l'apparence du bouton Maj selon son état
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::UpdateMajButtonState()
{
    if (!btnMaj) return;

    if (FMajActive) {
        btnMaj->Font->Style = TFontStyles() << fsBold;  // Gras quand actif
    } else {
        btnMaj->Font->Style = TFontStyles();  // Normal quand inactif
    }
}


bool __fastcall TFormKeyboard::IsDeadKey(wchar_t ch) const
{
    return (ch == L'^' || ch == L'¨');
}

wchar_t __fastcall TFormKeyboard::ComposeDeadKey(wchar_t dead, wchar_t base) const
{
    // Circonflexe ^
    if (dead == L'^') {
        switch (base) {
            case L'a': return L'â';
            case L'e': return L'ê';
            case L'i': return L'î';
            case L'o': return L'ô';
            case L'u': return L'û';
            case L'A': return L'Â';
            case L'E': return L'Ê';
            case L'I': return L'Î';
            case L'O': return L'Ô';
            case L'U': return L'Û';
        }
    }

    // Tréma ¨
    if (dead == L'¨') {
        switch (base) {
            case L'a': return L'ä';
            case L'e': return L'ë';
            case L'i': return L'ï';
            case L'o': return L'ö';
            case L'u': return L'ü';
            case L'y': return L'ÿ';
            case L'A': return L'Ä';
            case L'E': return L'Ë';
            case L'I': return L'Ï';
            case L'O': return L'Ö';
            case L'U': return L'Ü';
            case L'Y': return L'Ÿ';
        }
    }

    return 0;
}


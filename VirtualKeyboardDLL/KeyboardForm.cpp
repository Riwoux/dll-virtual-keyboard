//---------------------------------------------------------------------------
// KeyboardForm.cpp - Implémentation du formulaire du clavier virtuel
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "KeyboardForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormKeyboard *FormKeyboard;

//---------------------------------------------------------------------------
// Constructeur
//---------------------------------------------------------------------------
__fastcall TFormKeyboard::TFormKeyboard(TComponent* Owner)
    : TForm(Owner), 
      PanelMain(NULL), PanelNumpad(NULL), BtnToggleMode(NULL),
      FTargetHandle(NULL), FCurrentMode(0), 
      FShiftActive(false), FCapsLockActive(false),
      FBtnShift(NULL), FBtnCapsLock(NULL)
{
    // Configuration du formulaire
    BorderStyle = bsToolWindow;
    FormStyle = fsStayOnTop;
    Position = poScreenCenter;
    Caption = "Clavier Virtuel";
    KeyPreview = true;
    
    // Créer le panel principal
    PanelMain = new TPanel(this);
    PanelMain->Parent = this;
    PanelMain->Align = alLeft;
    PanelMain->BevelOuter = bvNone;
    PanelMain->Width = 800;
    
    // Créer le panel du pavé numérique
    PanelNumpad = new TPanel(this);
    PanelNumpad->Parent = this;
    PanelNumpad->Align = alRight;
    PanelNumpad->BevelOuter = bvNone;
    PanelNumpad->Width = 200;
    PanelNumpad->Visible = false;
    
    // Créer le bouton de basculement de mode
    BtnToggleMode = new TButton(this);
    BtnToggleMode->Parent = PanelMain;
    BtnToggleMode->Caption = "Pavé Num";
    BtnToggleMode->Left = 10;
    BtnToggleMode->Top = 260;
    BtnToggleMode->Width = 100;
    BtnToggleMode->Height = 30;
    BtnToggleMode->OnClick = OnToggleModeClick;
    
    // Créer le clavier principal
    CreateMainKeyboard();
    
    // Ajuster la taille du formulaire
    ClientWidth = PanelMain->Width;
    ClientHeight = 300;
}

//---------------------------------------------------------------------------
// Destructeur
//---------------------------------------------------------------------------
__fastcall TFormKeyboard::~TFormKeyboard()
{
    ClearKeyboard();
}

//---------------------------------------------------------------------------
// Nettoyer les boutons du clavier
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::ClearKeyboard()
{
    FMainKeyButtons.clear();
    FNumpadButtons.clear();
    FBtnShift = NULL;
    FBtnCapsLock = NULL;
}

//---------------------------------------------------------------------------
// Créer un bouton
//---------------------------------------------------------------------------
TButton* __fastcall TFormKeyboard::CreateButton(TPanel* Parent, const String& Caption,
                                                 int Left, int Top, int Width, int Height)
{
    TButton* btn = new TButton(Parent);
    btn->Parent = Parent;
    btn->Caption = Caption;
    btn->Left = Left;
    btn->Top = Top;
    btn->Width = Width;
    btn->Height = Height;
    btn->Font->Size = 10;
    return btn;
}

//---------------------------------------------------------------------------
// Créer le clavier principal
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::CreateMainKeyboard()
{
    const int btnWidth = 50;
    const int btnHeight = 45;
    const int spacing = 5;
    int row = 0;
    int col = 0;
    
    // Ligne 1: Touches numériques et caractères spéciaux
    String row1Keys[] = {"&\n1", "é\n2", "\"\n3", "'\n4", "(\n5", 
                         "-\n6", "è\n7", "_\n8", "ç\n9", "à\n0", "=", "+"};
    row = 10;
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(PanelMain, row1Keys[i], 
                                   10 + i * (btnWidth + spacing), row, 
                                   btnWidth, btnHeight);
        btn->Tag = (i < 10) ? (wchar_t)('0' + (i + 1) % 10) : 
                   (i == 10 ? (wchar_t)'=' : (wchar_t)'+');
        btn->OnClick = OnKeyButtonClick;
        FMainKeyButtons.push_back(btn);
    }
    
    // Ligne 2: A-Z-E-R-T-Y-U-I-O-P-^-$
    // Correction: Utiliser [1] pour accéder au premier caractère de la String (index 1-based en VCL)
    String row2Keys[] = {"A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P", "^", "$"};
    row += btnHeight + spacing;
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(PanelMain, row2Keys[i], 
                                   10 + i * (btnWidth + spacing), row, 
                                   btnWidth, btnHeight);
        // String VCL utilise un index 1-based, donc [1] donne le premier caractère
        btn->Tag = (NativeInt)(wchar_t)row2Keys[i][1];
        btn->OnClick = OnKeyButtonClick;
        FMainKeyButtons.push_back(btn);
    }
    
    // Ligne 3: Q-S-D-F-G-H-J-K-L-M-ù-*
    String row3Keys[] = {"Q", "S", "D", "F", "G", "H", "J", "K", "L", "M", "ù", "*"};
    row += btnHeight + spacing;
    for (int i = 0; i < 12; i++) {
        TButton* btn = CreateButton(PanelMain, row3Keys[i], 
                                   35 + i * (btnWidth + spacing), row, 
                                   btnWidth, btnHeight);
        // String VCL utilise un index 1-based, donc [1] donne le premier caractère
        btn->Tag = (NativeInt)(wchar_t)row3Keys[i][1];
        btn->OnClick = OnKeyButtonClick;
        FMainKeyButtons.push_back(btn);
    }
    
    // Ligne 4: W-X-C-V-B-N-;-:
    String row4Keys[] = {"W", "X", "C", "V", "B", "N", ";", ":"};
    row += btnHeight + spacing;
    for (int i = 0; i < 8; i++) {
        TButton* btn = CreateButton(PanelMain, row4Keys[i], 
                                   60 + i * (btnWidth + spacing), row, 
                                   btnWidth, btnHeight);
        // String VCL utilise un index 1-based, donc [1] donne le premier caractère
        btn->Tag = (NativeInt)(wchar_t)row4Keys[i][1];
        btn->OnClick = OnKeyButtonClick;
        FMainKeyButtons.push_back(btn);
    }
    
    // Ligne 5: Touches spéciales
    row += btnHeight + spacing;
    
    // Bouton Maj
    FBtnShift = CreateButton(PanelMain, "Maj", 10, row, 70, btnHeight);
    FBtnShift->OnClick = OnShiftClick;
    // Note: TButton ne supporte pas la propriété Color publiquement en C++ Builder
    // La propriété Color est protected dans TControl et n'est pas accessible sur TButton
    // Pour des boutons avec couleurs personnalisées, il faudrait utiliser TSpeedButton ou TBitBtn
    FMainKeyButtons.push_back(FBtnShift);
    
    // Bouton Caps Lock
    FBtnCapsLock = CreateButton(PanelMain, "Caps", 85, row, 70, btnHeight);
    FBtnCapsLock->OnClick = OnCapsLockClick;
    // Note: TButton ne supporte pas la propriété Color (voir commentaire bouton Maj ci-dessus)
    FMainKeyButtons.push_back(FBtnCapsLock);
    
    // Bouton Espace
    TButton* btnSpace = CreateButton(PanelMain, "Espace", 160, row, 200, btnHeight);
    btnSpace->OnClick = OnSpaceClick;
    // Note: TButton ne supporte pas la propriété Color (voir commentaire bouton Maj ci-dessus)
    FMainKeyButtons.push_back(btnSpace);
    
    // Bouton Tab
    TButton* btnTab = CreateButton(PanelMain, "Tab", 365, row, 70, btnHeight);
    btnTab->OnClick = OnTabClick;
    // Note: TButton ne supporte pas la propriété Color (voir commentaire bouton Maj ci-dessus)
    FMainKeyButtons.push_back(btnTab);
    
    // Bouton Backspace
    TButton* btnBackspace = CreateButton(PanelMain, "←", 440, row, 70, btnHeight);
    btnBackspace->OnClick = OnBackspaceClick;
    // Note: TButton ne supporte pas la propriété Color (voir commentaire bouton Maj ci-dessus)
    FMainKeyButtons.push_back(btnBackspace);
    
    // Bouton Enter
    TButton* btnEnter = CreateButton(PanelMain, "Entrée", 515, row, 100, btnHeight);
    btnEnter->OnClick = OnEnterClick;
    // Note: TButton ne supporte pas la propriété Color (voir commentaire bouton Maj ci-dessus)
    FMainKeyButtons.push_back(btnEnter);
}

//---------------------------------------------------------------------------
// Créer le pavé numérique
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::CreateNumpad()
{
    const int btnWidth = 50;
    const int btnHeight = 45;
    const int spacing = 5;
    
    // Titre
    TLabel* lbl = new TLabel(PanelNumpad);
    lbl->Parent = PanelNumpad;
    lbl->Caption = "Pavé Numérique";
    lbl->Left = 10;
    lbl->Top = 10;
    
    int row = 40;
    
    // Ligne 1: 7, 8, 9, /
    String nums1[] = {"7", "8", "9", "/"};
    for (int i = 0; i < 4; i++) {
        TButton* btn = CreateButton(PanelNumpad, nums1[i], 
                                   10 + i * (btnWidth - 10), row, 
                                   btnWidth - 10, btnHeight);
        // String VCL utilise un index 1-based, donc [1] donne le premier caractère
        btn->Tag = (NativeInt)(wchar_t)nums1[i][1];
        btn->OnClick = OnKeyButtonClick;
        FNumpadButtons.push_back(btn);
    }
    
    // Ligne 2: 4, 5, 6, *
    row += btnHeight + spacing;
    String nums2[] = {"4", "5", "6", "*"};
    for (int i = 0; i < 4; i++) {
        TButton* btn = CreateButton(PanelNumpad, nums2[i], 
                                   10 + i * (btnWidth - 10), row, 
                                   btnWidth - 10, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)nums2[i][1];
        btn->OnClick = OnKeyButtonClick;
        FNumpadButtons.push_back(btn);
    }
    
    // Ligne 3: 1, 2, 3, -
    row += btnHeight + spacing;
    String nums3[] = {"1", "2", "3", "-"};
    for (int i = 0; i < 4; i++) {
        TButton* btn = CreateButton(PanelNumpad, nums3[i], 
                                   10 + i * (btnWidth - 10), row, 
                                   btnWidth - 10, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)nums3[i][1];
        btn->OnClick = OnKeyButtonClick;
        FNumpadButtons.push_back(btn);
    }
    
    // Ligne 4: 0, ., +, Enter
    row += btnHeight + spacing;
    String nums4[] = {"0", ".", "+"};
    for (int i = 0; i < 3; i++) {
        TButton* btn = CreateButton(PanelNumpad, nums4[i], 
                                   10 + i * (btnWidth - 10), row, 
                                   btnWidth - 10, btnHeight);
        btn->Tag = (NativeInt)(wchar_t)nums4[i][1];
        btn->OnClick = OnKeyButtonClick;
        FNumpadButtons.push_back(btn);
    }
    
    // Enter du pavé numérique (plus grand)
    TButton* btnEnter = CreateButton(PanelNumpad, "↵", 
                                    130, row, btnWidth - 10, btnHeight);
    btnEnter->OnClick = OnEnterClick;
    // Note: TButton ne supporte pas la propriété Color (voir commentaire dans CreateMainKeyboard)
    FNumpadButtons.push_back(btnEnter);
}

//---------------------------------------------------------------------------
// Gestionnaire de clic sur touche normale
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnKeyButtonClick(TObject *Sender)
{
    TButton* btn = dynamic_cast<TButton*>(Sender);
    if (!btn) return;
    
    wchar_t ch = (wchar_t)btn->Tag;
    
    // Gérer les majuscules pour les lettres
    // Utilisation des fonctions Windows API pour compatibilité C++ Builder
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        if (FShiftActive || FCapsLockActive) {
            // Convertir en majuscule
            if (ch >= 'a' && ch <= 'z') {
                ch = ch - 'a' + 'A';
            }
        } else {
            // Convertir en minuscule
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch - 'A' + 'a';
            }
        }
        
        // Désactiver Maj temporaire après utilisation
        if (FShiftActive) {
            FShiftActive = false;
            UpdateShiftDisplay();
        }
    }
    
    SendCharToTarget(ch);
}

//---------------------------------------------------------------------------
// Gestionnaire de clic sur Maj
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnShiftClick(TObject *Sender)
{
    FShiftActive = !FShiftActive;
    UpdateShiftDisplay();
}

//---------------------------------------------------------------------------
// Gestionnaire de clic sur Caps Lock
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnCapsLockClick(TObject *Sender)
{
    FCapsLockActive = !FCapsLockActive;
    UpdateShiftDisplay();
}

//---------------------------------------------------------------------------
// Gestionnaire de clic sur Backspace
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnBackspaceClick(TObject *Sender)
{
    SendKeyToTarget(VK_BACK);
}

//---------------------------------------------------------------------------
// Gestionnaire de clic sur Enter
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnEnterClick(TObject *Sender)
{
    SendKeyToTarget(VK_RETURN);
}

//---------------------------------------------------------------------------
// Gestionnaire de clic sur Espace
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnSpaceClick(TObject *Sender)
{
    SendCharToTarget(' ');
}

//---------------------------------------------------------------------------
// Gestionnaire de clic sur Tab
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnTabClick(TObject *Sender)
{
    SendKeyToTarget(VK_TAB);
}

//---------------------------------------------------------------------------
// Gestionnaire de clic sur basculement de mode
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::OnToggleModeClick(TObject *Sender)
{
    SetKeyboardMode(FCurrentMode == 0 ? 1 : 0);
}

//---------------------------------------------------------------------------
// Mettre à jour l'affichage des boutons Maj et Caps Lock
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::UpdateShiftDisplay()
{
    // Note: TButton ne supporte pas la propriété Color en C++ Builder
    // La visualisation de l'état Shift/CapsLock pourrait être implémentée avec:
    // - TSpeedButton ou TBitBtn au lieu de TButton (supportent Color)
    // - Modification du Caption (ex: "Maj*" quand actif)
    // - Style propriétaire (OwnerDraw) pour dessiner la couleur manuellement
    // Pour l'instant, l'état est géré en interne mais pas visuellement affiché
    if (FBtnShift) {
        // Impossible d'utiliser: FBtnShift->Color = FShiftActive ? clLime : clBtnFace;
        // Alternative: modifier le caption pour indiquer l'état
        FBtnShift->Caption = FShiftActive ? "Maj*" : "Maj";
    }
    if (FBtnCapsLock) {
        // Impossible d'utiliser: FBtnCapsLock->Color = FCapsLockActive ? clLime : clBtnFace;
        // Alternative: modifier le caption pour indiquer l'état
        FBtnCapsLock->Caption = FCapsLockActive ? "Caps*" : "Caps";
    }
}

//---------------------------------------------------------------------------
// Envoyer un caractère au contrôle cible
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SendCharToTarget(wchar_t ch)
{
    if (FTargetHandle && IsWindow(FTargetHandle)) {
        SendMessageW(FTargetHandle, WM_CHAR, (WPARAM)ch, 0);
    }
}

//---------------------------------------------------------------------------
// Envoyer une touche spéciale au contrôle cible
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SendKeyToTarget(WORD vKey)
{
    if (FTargetHandle && IsWindow(FTargetHandle)) {
        // Envoyer WM_KEYDOWN puis WM_KEYUP
        SendMessageW(FTargetHandle, WM_KEYDOWN, (WPARAM)vKey, 0);
        SendMessageW(FTargetHandle, WM_KEYUP, (WPARAM)vKey, 0);
    }
}

//---------------------------------------------------------------------------
// Définir le handle du contrôle cible
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SetTargetHandle(HWND handle)
{
    FTargetHandle = handle;
}

//---------------------------------------------------------------------------
// Définir le mode du clavier
//---------------------------------------------------------------------------
void __fastcall TFormKeyboard::SetKeyboardMode(int mode)
{
    if (mode == FCurrentMode) return;
    
    FCurrentMode = mode;
    
    if (mode == 1) {
        // Mode avec pavé numérique
        if (FNumpadButtons.empty()) {
            CreateNumpad();
        }
        PanelNumpad->Visible = true;
        ClientWidth = PanelMain->Width + PanelNumpad->Width;
        BtnToggleMode->Caption = "Simple";
    } else {
        // Mode simple
        PanelNumpad->Visible = false;
        ClientWidth = PanelMain->Width;
        BtnToggleMode->Caption = "Pavé Num";
    }
}

//---------------------------------------------------------------------------
// Obtenir le mode actuel du clavier
//---------------------------------------------------------------------------
int __fastcall TFormKeyboard::GetKeyboardMode()
{
    return FCurrentMode;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// KeyboardForm.h - Formulaire du clavier virtuel
//---------------------------------------------------------------------------
#ifndef KeyboardFormH
#define KeyboardFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>
//---------------------------------------------------------------------------

class TFormKeyboard : public TForm
{
__published:	// Composants gérés par l'IDE (aucun pour l'instant - tout est créé dynamiquement)
    
private:	// Déclarations utilisateur
    // Composants créés dynamiquement
    TPanel *PanelMain;
    TPanel *PanelNumpad;
    TButton *BtnToggleMode;
    
    // Variables d'état
    HWND FTargetHandle;           // Handle du contrôle cible
    int FCurrentMode;             // Mode actuel (0=simple, 1=avec pavé)
    bool FShiftActive;            // État Maj temporaire
    bool FCapsLockActive;         // État Caps Lock
    
    std::vector<TButton*> FMainKeyButtons;   // Boutons du clavier principal
    std::vector<TButton*> FNumpadButtons;    // Boutons du pavé numérique
    TButton* FBtnShift;                      // Bouton Maj
    TButton* FBtnCapsLock;                   // Bouton Caps Lock
    
    // Méthodes privées
    void __fastcall CreateMainKeyboard();
    void __fastcall CreateNumpad();
    void __fastcall ClearKeyboard();
    void __fastcall OnKeyButtonClick(TObject *Sender);
    void __fastcall OnShiftClick(TObject *Sender);
    void __fastcall OnCapsLockClick(TObject *Sender);
    void __fastcall OnBackspaceClick(TObject *Sender);
    void __fastcall OnEnterClick(TObject *Sender);
    void __fastcall OnSpaceClick(TObject *Sender);
    void __fastcall OnTabClick(TObject *Sender);
    void __fastcall OnToggleModeClick(TObject *Sender);
    void __fastcall UpdateShiftDisplay();
    void __fastcall SendCharToTarget(wchar_t ch);
    void __fastcall SendKeyToTarget(WORD vKey);
    TButton* __fastcall CreateButton(TPanel* Parent, const String& Caption, 
                                      int Left, int Top, int Width, int Height);
    
public:		// Déclarations utilisateur
    __fastcall TFormKeyboard(TComponent* Owner);
    __fastcall ~TFormKeyboard();
    
    void __fastcall SetTargetHandle(HWND handle);
    void __fastcall SetKeyboardMode(int mode);
    int __fastcall GetKeyboardMode();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKeyboard *FormKeyboard;
//---------------------------------------------------------------------------
#endif

# Clavier Virtuel DLL pour C++ Builder 13

DLL de clavier virtuel avec deux modes d'affichage : clavier simple et clavier avec pavé numérique intégré.

## Description

Cette DLL fournit un clavier virtuel complet compatible avec tous les contrôles Windows standards (Edit, Memo, RichEdit, etc.). Le clavier peut fonctionner en deux modes :

- **Mode 0 (Simple)** : Clavier AZERTY complet avec touches spéciales
- **Mode 1 (Avec pavé numérique)** : Clavier complet + pavé numérique séparé sur le côté droit

## Fonctionnalités

### Touches disponibles

**Clavier principal (Mode 0 et 1) :**
- Ligne 1 : Touches numériques (1-9, 0) et caractères spéciaux (&, é, ", ', (, -, è, _, ç, à, =, +)
- Ligne 2 : A-Z-E-R-T-Y-U-I-O-P-^-$
- Ligne 3 : Q-S-D-F-G-H-J-K-L-M-ù-*
- Ligne 4 : W-X-C-V-B-N-;-:
- Ligne 5 : Touches spéciales (Maj, Caps Lock, Espace, Tab, Backspace, Entrée)

**Pavé numérique (Mode 1 uniquement) :**
- Chiffres : 0-9
- Opérateurs : +, -, *, /
- Point décimal : .
- Touche Entrée du pavé

### Gestion des majuscules

- **Bouton Maj** : Majuscule temporaire (désactivée après une touche)
- **Bouton Caps Lock** : Verrouillage des majuscules
- **Indication visuelle** : Les boutons actifs deviennent verts (clLime)

### Touches spéciales

- **Backspace** : Supprime le caractère précédent
- **Entrée** : Insère une nouvelle ligne ou valide
- **Espace** : Insère un espace
- **Tab** : Insère une tabulation

### Basculement de mode

- Bouton "Pavé Num" / "Simple" pour basculer entre les modes
- Le formulaire se redimensionne automatiquement

## Fonctions exportées

```cpp
// Affiche le clavier virtuel
// mode: 0 = simple, 1 = avec pavé numérique
// targetHandle: HWND du contrôle qui recevra les caractères
void __stdcall ShowKeyboard(int mode, HWND targetHandle);

// Masque le clavier virtuel
void __stdcall HideKeyboard();

// Vérifie si le clavier est visible
bool __stdcall IsKeyboardVisible();

// Change le mode du clavier (0 = simple, 1 = avec pavé)
void __stdcall SetKeyboardMode(int mode);
```

## Compilation

### Prérequis

- C++ Builder 13 (RAD Studio 12 Athens) ou version compatible
- VCL Framework
- Windows SDK

### Instructions de compilation

1. Ouvrez le projet `VirtualKeyboardDLL.cbproj` dans C++ Builder 13
2. Sélectionnez la configuration (Debug ou Release)
3. Choisissez la plateforme (Win32 ou Win64)
4. Menu : Project → Build VirtualKeyboardDLL
5. La DLL sera générée dans `Win32\Debug\` ou `Win32\Release\`

### Structure des fichiers

```
VirtualKeyboardDLL/
├── VirtualKeyboardDLL.cbproj    # Fichier projet C++ Builder
├── VirtualKeyboard.h            # Déclarations des exports
├── VirtualKeyboard.cpp          # Implémentation de la DLL
├── KeyboardForm.h               # Header du formulaire
├── KeyboardForm.cpp             # Implémentation du formulaire
├── KeyboardForm.dfm             # Design VCL du formulaire
└── README.md                    # Ce fichier
```

## Utilisation dans votre application

### 1. Charger la DLL dynamiquement

```cpp
#include <windows.h>

// Types des fonctions
typedef void (__stdcall *TShowKeyboardProc)(int mode, HWND targetHandle);
typedef void (__stdcall *THideKeyboardProc)();
typedef bool (__stdcall *TIsKeyboardVisibleProc)();
typedef void (__stdcall *TSetKeyboardModeProc)(int mode);

// Variables globales
HINSTANCE hDll;
TShowKeyboardProc ShowKeyboard;
THideKeyboardProc HideKeyboard;
TIsKeyboardVisibleProc IsKeyboardVisible;
TSetKeyboardModeProc SetKeyboardMode;

// Charger la DLL
hDll = LoadLibrary(L"VirtualKeyboardDLL.dll");
if (hDll) {
    ShowKeyboard = (TShowKeyboardProc)GetProcAddress(hDll, "ShowKeyboard");
    HideKeyboard = (THideKeyboardProc)GetProcAddress(hDll, "HideKeyboard");
    IsKeyboardVisible = (TIsKeyboardVisibleProc)GetProcAddress(hDll, "IsKeyboardVisible");
    SetKeyboardMode = (TSetKeyboardModeProc)GetProcAddress(hDll, "SetKeyboardMode");
}
```

### 2. Afficher le clavier

```cpp
// Afficher en mode simple (Mode 0)
if (ShowKeyboard) {
    ShowKeyboard(0, Edit1->Handle);  // Edit1 est votre contrôle cible
}

// Afficher en mode avec pavé numérique (Mode 1)
if (ShowKeyboard) {
    ShowKeyboard(1, Memo1->Handle);  // Memo1 est votre contrôle cible
}
```

### 3. Masquer le clavier

```cpp
if (HideKeyboard) {
    HideKeyboard();
}
```

### 4. Vérifier l'état

```cpp
if (IsKeyboardVisible && IsKeyboardVisible()) {
    // Le clavier est visible
}
```

### 5. Changer le mode

```cpp
if (SetKeyboardMode) {
    SetKeyboardMode(1);  // Passer en mode avec pavé numérique
}
```

### 6. Décharger la DLL

```cpp
if (hDll) {
    FreeLibrary(hDll);
}
```

## Exemple complet

Voir l'application de test dans le dossier `../TestApp/` pour un exemple complet d'utilisation.

## Compatibilité

- **Plateformes** : Windows 32-bit et 64-bit
- **Contrôles supportés** : Tous les contrôles Windows acceptant WM_CHAR et WM_KEYDOWN
  - TEdit
  - TMemo
  - TRichEdit
  - Contrôles Windows standards (Edit, RichEdit, etc.)
  - Contrôles tiers compatibles

## Architecture technique

### Communication avec les contrôles

La DLL utilise les messages Windows standard pour envoyer les caractères :
- `WM_CHAR` : Pour les caractères normaux
- `WM_KEYDOWN` / `WM_KEYUP` : Pour les touches spéciales (Backspace, Enter, Tab)

### Gestion de la mémoire

- Le formulaire du clavier est créé à la première utilisation
- Il persiste jusqu'à la décharge de la DLL
- Pas de fuites mémoire (destructeurs appropriés)

### Thread-safety

La DLL est thread-safe pour une utilisation normale (un clavier par processus).

## Notes importantes

1. **Placement de la DLL** : La DLL doit être :
   - Dans le même répertoire que votre application, ou
   - Dans un répertoire du PATH système, ou
   - Chargée avec un chemin absolu

2. **Dépendances** : La DLL nécessite les runtimes VCL de C++ Builder

3. **Formulaire non modal** : Le clavier reste toujours au premier plan (fsStayOnTop)

4. **Ciblage des contrôles** : Vous devez passer le HWND du contrôle à chaque appel à ShowKeyboard()

## Dépannage

### La DLL ne se charge pas
- Vérifiez que la DLL est bien dans le PATH
- Vérifiez que les runtimes C++ Builder sont installés
- Utilisez un outil comme Dependency Walker pour identifier les DLL manquantes

### Les caractères ne sont pas envoyés
- Vérifiez que le HWND passé est valide
- Vérifiez que le contrôle cible accepte les messages WM_CHAR
- Le contrôle doit avoir le focus ou accepter les messages même sans focus

### Le clavier ne s'affiche pas
- Vérifiez que ShowKeyboard() retourne sans erreur
- Le formulaire peut être caché derrière d'autres fenêtres (utilisez BringToFront)

## Licence

Ce projet est un exemple de code pour C++ Builder 13.

## Auteur

Projet de démonstration - Clavier Virtuel DLL

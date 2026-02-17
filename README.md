# Virtual Keyboard DLL - C++ Builder 13

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++ Builder](https://img.shields.io/badge/C%2B%2B%20Builder-13-blue.svg)](https://www.embarcadero.com/products/cbuilder)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)

**[English](#english) | [Français](#français)**

---

## English

Simple virtual keyboard implementation as a DLL for C++ Builder 13 with a test application.

## Description

This project provides a simple virtual keyboard DLL that can be integrated into any C++ Builder or Win32 application. The keyboard features a basic AZERTY layout with essential keys.

## Features

- AZERTY keyboard layout (French)
- Numbers 0-9
- Letters A-Z
- Shift key for uppercase
- Special keys: Space, Backspace, Enter
- Stays on top of other windows
- Easy integration via DLL

## Project Structure

```
testclaviervirtuel/
├── VirtualKeyboardDLL/          # DLL Project
│   ├── VirtualKeyboard.h        # Export declarations
│   ├── VirtualKeyboard.cpp      # DLL implementation
│   ├── KeyboardForm.h           # Form header
│   ├── KeyboardForm.cpp         # Keyboard implementation
│   ├── KeyboardForm.dfm         # VCL design
│   └── VirtualKeyboardDLL.cbproj # C++ Builder project
│
├── TestApp/                     # Test Application
│   ├── TestApp.cpp              # Entry point
│   ├── MainForm.h               # Form header
│   ├── MainForm.cpp             # Implementation
│   ├── MainForm.dfm             # VCL design
│   └── TestApp.cbproj           # C++ Builder project
│
└── README.md                    # This file
```

## Requirements

- C++ Builder 13 (RAD Studio 12 Athens) or compatible version
- VCL Framework (included with C++ Builder)
- Windows SDK (included with RAD Studio)
- Windows 32-bit or 64-bit

## Building

### 1. Build the DLL

```bash
cd VirtualKeyboardDLL
# Open VirtualKeyboardDLL.cbproj in C++ Builder
# Menu: Project → Build VirtualKeyboardDLL
```

The DLL will be generated in `VirtualKeyboardDLL/Win32/Debug/` or `Win32/Release/`

### 2. Build the Test Application

```bash
cd TestApp
# Open TestApp.cbproj in C++ Builder
# Menu: Project → Build TestApp
```

The executable will be generated in `TestApp/Win32/Debug/` or `Win32/Release/`

### 3. Deployment

Copy `VirtualKeyboardDLL.dll` to the same directory as `TestApp.exe` or to the system PATH.

## Usage

### Testing

1. Launch `TestApp.exe`
2. Click **"Show Keyboard"**
3. The virtual keyboard appears
4. Click keys to type in the memo
5. Click **"Hide Keyboard"** to close it

### DLL Integration

#### Exported Functions

```cpp
// Show the keyboard
extern "C" __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle);

// Hide the keyboard
extern "C" __declspec(dllexport) void __stdcall HideKeyboard();

// Check if keyboard is visible
extern "C" __declspec(dllexport) bool __stdcall IsKeyboardVisible();
```

#### Integration Example

```cpp
#include <windows.h>

// Function types
typedef void (__stdcall *TShowKeyboardProc)(HWND targetHandle);
typedef void (__stdcall *THideKeyboardProc)();

// Load the DLL
HINSTANCE hDll = LoadLibrary(L"VirtualKeyboardDLL.dll");
if (hDll) {
    auto ShowKeyboard = (TShowKeyboardProc)GetProcAddress(hDll, "ShowKeyboard");
    auto HideKeyboard = (THideKeyboardProc)GetProcAddress(hDll, "HideKeyboard");
    
    // Show the keyboard
    if (ShowKeyboard) {
        ShowKeyboard(MyEdit->Handle);
    }
    
    // Hide the keyboard
    if (HideKeyboard) {
        HideKeyboard();
    }
    
    // Unload the DLL
    FreeLibrary(hDll);
}
```

## Keyboard Layout

```
[1] [2] [3] [4] [5] [6] [7] [8] [9] [0]
[A] [Z] [E] [R] [T] [Y] [U] [I] [O] [P]
  [Q] [S] [D] [F] [G] [H] [J] [K] [L] [M]
    [W] [X] [C] [V] [B] [N]
[Shift] [     Space     ] [←] [Enter]
```

## Technical Notes

- The keyboard sends characters using Windows messages (WM_CHAR, WM_KEYDOWN, WM_KEYUP)
- Compatible with TEdit, TMemo, TRichEdit and all standard Windows controls
- Thread-safe for single-threaded usage per process
- Requires VCL runtimes from C++ Builder

## Troubleshooting

### DLL not found
- Ensure `VirtualKeyboardDLL.dll` is in the same directory as your executable
- Or add the DLL's directory to your system PATH

### Keyboard doesn't show
- Verify you're passing the correct window handle to `ShowKeyboard()`
- Check that the DLL is properly loaded (no missing dependencies)

### Characters not appearing
- The target control must have focus
- Verify the target control supports WM_CHAR messages

## Contributing

Contributions are welcome! Please feel free to:
- Report bugs via issues
- Suggest new features
- Submit pull requests

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Free to use for personal and commercial projects.

---

## Français

Implémentation simple d'un clavier virtuel sous forme de DLL pour C++ Builder 13 avec une application de test.

## Description

Ce projet fournit une DLL de clavier virtuel simple qui peut être intégrée dans n'importe quelle application C++ Builder ou Win32. Le clavier dispose d'une disposition AZERTY de base avec les touches essentielles.

## Fonctionnalités

- Disposition de clavier AZERTY (Français)
- Chiffres 0-9
- Lettres A-Z
- Touche Shift pour les majuscules
- Touches spéciales : Espace, Retour arrière, Entrée
- Reste au-dessus des autres fenêtres
- Intégration facile via DLL

## Structure du Projet

```
testclaviervirtuel/
├── VirtualKeyboardDLL/          # Projet DLL
│   ├── VirtualKeyboard.h        # Déclarations d'export
│   ├── VirtualKeyboard.cpp      # Implémentation DLL
│   ├── KeyboardForm.h           # En-tête du formulaire
│   ├── KeyboardForm.cpp         # Implémentation du clavier
│   ├── KeyboardForm.dfm         # Design VCL
│   └── VirtualKeyboardDLL.cbproj # Projet C++ Builder
│
├── TestApp/                     # Application de Test
│   ├── TestApp.cpp              # Point d'entrée
│   ├── MainForm.h               # En-tête du formulaire
│   ├── MainForm.cpp             # Implémentation
│   ├── MainForm.dfm             # Design VCL
│   └── TestApp.cbproj           # Projet C++ Builder
│
└── README.md                    # Ce fichier
```

## Prérequis

- C++ Builder 13 (RAD Studio 12 Athens) ou version compatible
- Framework VCL (inclus avec C++ Builder)
- Windows SDK (inclus avec RAD Studio)
- Windows 32 bits ou 64 bits

## Compilation

### 1. Compiler la DLL

```bash
cd VirtualKeyboardDLL
# Ouvrir VirtualKeyboardDLL.cbproj dans C++ Builder
# Menu : Projet → Compiler VirtualKeyboardDLL
```

La DLL sera générée dans `VirtualKeyboardDLL/Win32/Debug/` ou `Win32/Release/`

### 2. Compiler l'Application de Test

```bash
cd TestApp
# Ouvrir TestApp.cbproj dans C++ Builder
# Menu : Projet → Compiler TestApp
```

L'exécutable sera généré dans `TestApp/Win32/Debug/` ou `Win32/Release/`

### 3. Déploiement

Copier `VirtualKeyboardDLL.dll` dans le même répertoire que `TestApp.exe` ou dans le PATH système.

## Utilisation

### Test

1. Lancer `TestApp.exe`
2. Cliquer sur **"Show Keyboard"**
3. Le clavier virtuel apparaît
4. Cliquer sur les touches pour taper dans le mémo
5. Cliquer sur **"Hide Keyboard"** pour le fermer

### Intégration de la DLL

#### Fonctions Exportées

```cpp
// Afficher le clavier
extern "C" __declspec(dllexport) void __stdcall ShowKeyboard(HWND targetHandle);

// Masquer le clavier
extern "C" __declspec(dllexport) void __stdcall HideKeyboard();

// Vérifier si le clavier est visible
extern "C" __declspec(dllexport) bool __stdcall IsKeyboardVisible();
```

#### Exemple d'Intégration

```cpp
#include <windows.h>

// Types de fonction
typedef void (__stdcall *TShowKeyboardProc)(HWND targetHandle);
typedef void (__stdcall *THideKeyboardProc)();

// Charger la DLL
HINSTANCE hDll = LoadLibrary(L"VirtualKeyboardDLL.dll");
if (hDll) {
    auto ShowKeyboard = (TShowKeyboardProc)GetProcAddress(hDll, "ShowKeyboard");
    auto HideKeyboard = (THideKeyboardProc)GetProcAddress(hDll, "HideKeyboard");
    
    // Afficher le clavier
    if (ShowKeyboard) {
        ShowKeyboard(MyEdit->Handle);
    }
    
    // Masquer le clavier
    if (HideKeyboard) {
        HideKeyboard();
    }
    
    // Décharger la DLL
    FreeLibrary(hDll);
}
```

## Disposition du Clavier

```
[1] [2] [3] [4] [5] [6] [7] [8] [9] [0]
[A] [Z] [E] [R] [T] [Y] [U] [I] [O] [P]
  [Q] [S] [D] [F] [G] [H] [J] [K] [L] [M]
    [W] [X] [C] [V] [B] [N]
[Shift] [     Espace     ] [←] [Entrée]
```

## Notes Techniques

- Le clavier envoie des caractères en utilisant les messages Windows (WM_CHAR, WM_KEYDOWN, WM_KEYUP)
- Compatible avec TEdit, TMemo, TRichEdit et tous les contrôles Windows standard
- Thread-safe pour une utilisation mono-thread par processus
- Nécessite les runtimes VCL de C++ Builder

## Dépannage

### DLL non trouvée
- Assurez-vous que `VirtualKeyboardDLL.dll` est dans le même répertoire que votre exécutable
- Ou ajoutez le répertoire de la DLL à votre PATH système

### Le clavier ne s'affiche pas
- Vérifiez que vous passez le bon handle de fenêtre à `ShowKeyboard()`
- Vérifiez que la DLL est correctement chargée (pas de dépendances manquantes)

### Les caractères n'apparaissent pas
- Le contrôle cible doit avoir le focus
- Vérifiez que le contrôle cible supporte les messages WM_CHAR

## Contribuer

Les contributions sont les bienvenues ! N'hésitez pas à :
- Signaler des bugs via les issues
- Suggérer de nouvelles fonctionnalités
- Soumettre des pull requests

## Licence

Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.

Libre d'utilisation pour les projets personnels et commerciaux.

---

**Version**: 2.0 (Simplifié)  
**Date**: 2026  
**Compatible avec**: C++ Builder 13 (RAD Studio 12 Athens)

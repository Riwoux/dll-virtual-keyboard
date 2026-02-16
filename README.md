# Clavier Virtuel DLL - C++ Builder 13

Projet complet de clavier virtuel en DLL pour C++ Builder 13 avec deux modes d'affichage.

## 📋 Description

Ce projet fournit une DLL de clavier virtuel professionnel avec interface VCL, conçue pour être intégrée dans n'importe quelle application C++ Builder ou Win32. Le clavier supporte deux modes d'affichage :

- **Mode 0 (Simple)** : Clavier AZERTY complet avec touches spéciales
- **Mode 1 (Avec pavé numérique)** : Clavier complet + pavé numérique intégré

## ✨ Fonctionnalités principales

### Clavier complet AZERTY
- Toutes les lettres (disposition AZERTY française)
- Chiffres et caractères spéciaux (&, é, ", ', (, -, è, _, ç, à, =, +)
- Symboles additionnels (^, $, ù, *, ;, :)

### Gestion des majuscules
- **Maj (Shift)** : Majuscule temporaire (une seule touche)
- **Caps Lock** : Verrouillage permanent des majuscules
- Indication visuelle de l'état (boutons verts quand actifs)

### Touches spéciales
- **Backspace** : Suppression du caractère précédent
- **Entrée** : Nouvelle ligne ou validation
- **Espace** : Insertion d'un espace
- **Tab** : Insertion d'une tabulation

### Pavé numérique (Mode 1)
- Chiffres 0-9 organisés en pavé
- Opérateurs mathématiques : +, -, *, /
- Point décimal (.)
- Touche Entrée dédiée

### Basculement de mode dynamique
- Bouton pour basculer entre les deux modes
- Redimensionnement automatique de la fenêtre
- Conservation de l'état pendant le basculement

## 🏗️ Structure du projet

```
testclaviervirtuel/
├── VirtualKeyboardDLL/          # Projet de la DLL
│   ├── VirtualKeyboard.h        # Déclarations des exports
│   ├── VirtualKeyboard.cpp      # Implémentation de la DLL
│   ├── KeyboardForm.h           # Header du formulaire
│   ├── KeyboardForm.cpp         # Implémentation du clavier
│   ├── KeyboardForm.dfm         # Design VCL
│   ├── VirtualKeyboardDLL.cbproj # Projet C++ Builder
│   └── README.md                # Documentation de la DLL
│
├── TestApp/                     # Application de test
│   ├── TestApp.cpp              # Point d'entrée
│   ├── MainForm.h               # Header du formulaire
│   ├── MainForm.cpp             # Implémentation
│   ├── MainForm.dfm             # Design VCL
│   ├── TestApp.cbproj           # Projet C++ Builder
│   └── README.md                # Documentation de test
│
└── README.md                    # Ce fichier
```

## 🚀 Démarrage rapide

### Prérequis

- **C++ Builder 13** (RAD Studio 12 Athens) ou version compatible
- **VCL Framework** (inclus avec C++ Builder)
- **Windows SDK** (inclus avec RAD Studio)
- **Windows 32-bit ou 64-bit**

### Compilation

#### 1. Compiler la DLL

```bash
cd VirtualKeyboardDLL
# Ouvrir VirtualKeyboardDLL.cbproj dans C++ Builder
# Menu: Project → Build VirtualKeyboardDLL
```

La DLL sera générée dans `VirtualKeyboardDLL/Win32/Debug/` ou `Win32/Release/`

#### 2. Compiler l'application de test

```bash
cd TestApp
# Ouvrir TestApp.cbproj dans C++ Builder
# Menu: Project → Build TestApp
```

L'exécutable sera généré dans `TestApp/Win32/Debug/` ou `Win32/Release/`

#### 3. Déploiement

Copiez `VirtualKeyboardDLL.dll` dans le même répertoire que `TestApp.exe` ou dans le PATH système.

### Premier test

1. Lancez `TestApp.exe`
2. Cliquez sur **"Afficher Clavier Simple"**
3. Le clavier virtuel s'affiche
4. Cliquez sur les touches pour saisir du texte dans le Memo
5. Testez le bouton **"Afficher Clavier avec Pavé"** pour voir le mode avec pavé numérique

## 📖 Utilisation de la DLL

### Fonctions exportées

```cpp
// Afficher le clavier (mode: 0=simple, 1=avec pavé)
extern "C" __declspec(dllexport) void __stdcall ShowKeyboard(int mode, HWND targetHandle);

// Masquer le clavier
extern "C" __declspec(dllexport) void __stdcall HideKeyboard();

// Vérifier si le clavier est visible
extern "C" __declspec(dllexport) bool __stdcall IsKeyboardVisible();

// Changer le mode du clavier
extern "C" __declspec(dllexport) void __stdcall SetKeyboardMode(int mode);
```

### Exemple d'intégration

```cpp
#include <windows.h>

// Types des fonctions
typedef void (__stdcall *TShowKeyboardProc)(int mode, HWND targetHandle);
typedef void (__stdcall *THideKeyboardProc)();

// Charger la DLL
HINSTANCE hDll = LoadLibrary(L"VirtualKeyboardDLL.dll");
if (hDll) {
    auto ShowKeyboard = (TShowKeyboardProc)GetProcAddress(hDll, "ShowKeyboard");
    auto HideKeyboard = (THideKeyboardProc)GetProcAddress(hDll, "HideKeyboard");
    
    // Afficher le clavier en mode simple
    if (ShowKeyboard) {
        ShowKeyboard(0, MyEdit->Handle);
    }
    
    // Masquer le clavier
    if (HideKeyboard) {
        HideKeyboard();
    }
    
    // Décharger la DLL
    FreeLibrary(hDll);
}
```

Pour plus de détails, consultez [VirtualKeyboardDLL/README.md](VirtualKeyboardDLL/README.md)

## 🎨 Caractéristiques de l'interface

### Design
- Formulaire VCL non modal (reste au premier plan)
- Bordure de style `bsToolWindow` (compacte)
- Boutons de taille appropriée (40x40 pixels minimum)
- Espacement optimal pour faciliter le clic
- Redimensionnement automatique selon le mode

### Couleurs
- **Boutons normaux** : Couleur système standard (clBtnFace)
- **Boutons actifs** : Vert clair (clLime) pour Maj et Caps Lock
- **Touches spéciales** : Beige clair (clInfoBk) pour différenciation

### Comportement
- Clavier toujours au premier plan (fsStayOnTop)
- Compatible avec tous les contrôles Windows standards
- Envoi des caractères via messages Windows (WM_CHAR)
- Gestion propre des majuscules temporaires et permanentes

## 🔧 Architecture technique

### Communication avec les contrôles

La DLL utilise l'API Windows standard :
- **WM_CHAR** : Pour envoyer les caractères normaux
- **WM_KEYDOWN/WM_KEYUP** : Pour les touches spéciales (Backspace, Enter, Tab)

### Compatibilité

**Contrôles supportés** :
- TEdit, TMemo, TRichEdit (VCL)
- Edit Control, RichEdit Control (Win32)
- Tout contrôle acceptant les messages WM_CHAR

**Plateformes** :
- Windows 32-bit (Win32)
- Windows 64-bit (Win64)

### Gestion de la mémoire

- Formulaire créé à la première utilisation
- Persiste pendant toute la durée de vie du processus
- Nettoyage automatique à la décharge de la DLL
- Pas de fuites mémoire

## 📚 Documentation

Consultez les README spécifiques pour plus de détails :

- [Documentation de la DLL](VirtualKeyboardDLL/README.md) - Guide complet de la DLL
- [Documentation de l'application de test](TestApp/README.md) - Guide de l'application de test

## 🎯 Tests suggérés

1. **Saisie de texte basique** - Lettres, chiffres, caractères spéciaux
2. **Majuscules** - Maj temporaire et Caps Lock permanent
3. **Touches spéciales** - Backspace, Enter, Espace, Tab
4. **Pavé numérique** - Chiffres, opérateurs, point décimal
5. **Basculement de mode** - Changement dynamique entre les modes
6. **Compatibilité** - Test avec différents contrôles (Edit, Memo, RichEdit)

## ⚙️ Configuration de compilation

### Debug vs Release

- **Debug** : Avec symboles de débogage, optimisations désactivées
- **Release** : Optimisé pour la performance, taille réduite

### Win32 vs Win64

- **Win32** : Compatible avec applications 32-bit
- **Win64** : Compatible avec applications 64-bit

**Important** : La DLL et l'application doivent être compilées pour la même plateforme.

## 🐛 Dépannage

### La DLL ne se charge pas
- Vérifiez que la DLL est dans le même répertoire que l'application
- Vérifiez que la plateforme correspond (Win32 ou Win64)
- Utilisez Dependency Walker pour identifier les DLL manquantes

### Les caractères ne sont pas envoyés
- Vérifiez que le HWND est valide avec `IsWindow(handle)`
- Assurez-vous que le contrôle accepte WM_CHAR
- Testez avec un contrôle simple comme TEdit

### Le clavier ne reste pas au premier plan
- C'est normal, le formulaire utilise `fsStayOnTop`
- Si ce n'est pas le cas, vérifiez la propriété FormStyle

## 📝 Notes techniques

1. **Thread-safety** : La DLL est conçue pour un usage mono-thread par processus
2. **Dépendances** : Nécessite les runtimes VCL de C++ Builder
3. **Encodage** : Support complet Unicode (wchar_t)
4. **Performances** : Optimisé pour une latence minimale

## 📄 Licence

Ce projet est un exemple de démonstration pour C++ Builder 13.
Libre d'utilisation pour des projets personnels et commerciaux.

## 👤 Auteur

Projet de démonstration - Clavier Virtuel DLL pour C++ Builder 13

## 🔗 Ressources

- [Documentation C++ Builder](https://www.embarcadero.com/products/cbuilder)
- [VCL Documentation](https://docwiki.embarcadero.com/RADStudio/en/VCL)
- [Windows API Reference](https://docs.microsoft.com/en-us/windows/win32/)

---

**Version** : 1.0.0  
**Date** : 2026  
**Compatible avec** : C++ Builder 13 (RAD Studio 12 Athens)
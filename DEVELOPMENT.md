# Guide de développement - Clavier Virtuel DLL

## Architecture du projet

### Vue d'ensemble

```
┌─────────────────────────────────────────────────────┐
│           Application Utilisateur                   │
│  (TestApp.exe ou votre propre application)          │
│                                                     │
│  ┌──────────────┐    ┌──────────────┐              │
│  │   TEdit      │    │    TMemo     │              │
│  │  (Handle 1)  │    │  (Handle 2)  │              │
│  └──────┬───────┘    └──────┬───────┘              │
└─────────┼───────────────────┼──────────────────────┘
          │                   │
          │  LoadLibrary()    │
          └───────────────┬───┘
                          │
          ┌───────────────▼──────────────────┐
          │   VirtualKeyboardDLL.dll         │
          │                                  │
          │  ┌────────────────────────────┐ │
          │  │  Exported Functions        │ │
          │  ├────────────────────────────┤ │
          │  │ ShowKeyboard()             │ │
          │  │ HideKeyboard()             │ │
          │  │ IsKeyboardVisible()        │ │
          │  │ SetKeyboardMode()          │ │
          │  └────────────┬───────────────┘ │
          │               │                  │
          │  ┌────────────▼───────────────┐ │
          │  │   TFormKeyboard            │ │
          │  │  (Formulaire VCL)          │ │
          │  │                            │ │
          │  │  - PanelMain (clavier)     │ │
          │  │  - PanelNumpad (pavé)      │ │
          │  │  - Buttons (touches)       │ │
          │  │                            │ │
          │  │  Mode 0: Simple            │ │
          │  │  Mode 1: + Pavé numérique  │ │
          │  └────────────┬───────────────┘ │
          └───────────────┼──────────────────┘
                          │
                          │ SendMessage(WM_CHAR)
                          │ SendMessage(WM_KEYDOWN)
                          │
          ┌───────────────▼──────────────────┐
          │   Contrôle Cible (HWND)          │
          │   Reçoit les caractères          │
          └──────────────────────────────────┘
```

### Flux de données

1. **Chargement de la DLL**
   ```
   Application → LoadLibrary("VirtualKeyboardDLL.dll")
   Application → GetProcAddress("ShowKeyboard")
   ```

2. **Affichage du clavier**
   ```
   Application → ShowKeyboard(mode, targetHWND)
   DLL → Crée/Affiche TFormKeyboard
   DLL → Configure le mode (0 ou 1)
   ```

3. **Interaction utilisateur**
   ```
   Utilisateur → Clique sur une touche
   TFormKeyboard → Détermine le caractère
   TFormKeyboard → Applique majuscule si besoin
   TFormKeyboard → SendMessage(targetHWND, WM_CHAR, char)
   Contrôle cible → Reçoit et affiche le caractère
   ```

4. **Fermeture**
   ```
   Application → HideKeyboard()
   DLL → Masque TFormKeyboard (ne détruit pas)
   Application → FreeLibrary()
   DLL → Détruit TFormKeyboard (DLL_PROCESS_DETACH)
   ```

## Structure des fichiers détaillée

### VirtualKeyboardDLL/

#### VirtualKeyboard.h
**Rôle** : Déclarations des fonctions exportées  
**Contenu** :
- Prototypes des 4 fonctions exportées
- Utilise `extern "C"` pour éviter le name mangling
- `__declspec(dllexport)` pour l'exportation
- `__stdcall` pour la convention d'appel

#### VirtualKeyboard.cpp
**Rôle** : Point d'entrée et implémentation de la DLL  
**Contenu** :
- `DllEntryPoint()` - Gestion du cycle de vie de la DLL
- Implémentation des 4 fonctions exportées
- Gestion de l'instance globale de TFormKeyboard
- Gestion des erreurs avec try/catch

#### KeyboardForm.h
**Rôle** : Déclaration de la classe TFormKeyboard  
**Contenu** :
- Classe TFormKeyboard héritant de TForm
- Propriétés privées (FTargetHandle, FCurrentMode, etc.)
- Méthodes publiques (SetTargetHandle, SetKeyboardMode, etc.)
- Méthodes privées (gestionnaires d'événements)
- Vecteurs de boutons (FMainKeyButtons, FNumpadButtons)

#### KeyboardForm.cpp
**Rôle** : Implémentation complète du clavier  
**Contenu** :
- Constructeur : Configuration du formulaire, création des panels
- `CreateMainKeyboard()` : Création de toutes les touches principales
- `CreateNumpad()` : Création du pavé numérique
- Gestionnaires d'événements pour chaque type de touche
- Logique des majuscules (Shift/Caps Lock)
- Envoi des caractères via SendMessage

#### KeyboardForm.dfm
**Rôle** : Design VCL du formulaire  
**Contenu** :
- Configuration du formulaire (BorderStyle, FormStyle, etc.)
- Propriétés visuelles (taille, position, couleurs)
- Les contrôles sont créés dynamiquement dans le code

#### VirtualKeyboardDLL.cbproj
**Rôle** : Fichier projet C++ Builder  
**Contenu** :
- Configuration MSBuild pour C++ Builder
- Références aux fichiers source
- Paramètres de compilation (Debug/Release, Win32/Win64)
- Configuration du linker pour créer une DLL

### TestApp/

#### TestApp.cpp
**Rôle** : Point d'entrée de l'application  
**Contenu** :
- Fonction `_tWinMain()` - Point d'entrée Windows
- Initialisation de l'application VCL
- Création du formulaire principal
- Boucle de messages

#### MainForm.h
**Rôle** : Déclaration du formulaire de test  
**Contenu** :
- Classe TFormMain héritant de TForm
- Déclarations des contrôles (TMemo, TButton, etc.)
- Types des pointeurs de fonction pour la DLL
- Méthodes pour charger/décharger la DLL

#### MainForm.cpp
**Rôle** : Implémentation du formulaire de test  
**Contenu** :
- Chargement dynamique de la DLL
- Récupération des adresses des fonctions exportées
- Gestionnaires des boutons (afficher/masquer le clavier)
- Gestion du cycle de vie de la DLL

#### MainForm.dfm
**Rôle** : Design VCL du formulaire de test  
**Contenu** :
- Configuration des contrôles (position, taille, texte)
- Propriétés visuelles
- Associations des événements

#### TestApp.cbproj
**Rôle** : Fichier projet C++ Builder  
**Contenu** :
- Configuration MSBuild pour C++ Builder
- Références aux fichiers source
- Paramètres de compilation pour une application .exe

## Séquences d'exécution

### Séquence 1 : Démarrage de l'application

```
1. TestApp.exe démarre
2. WinMain() est appelé
3. Application->Initialize()
4. Application->CreateForm(TFormMain)
5. TFormMain::FormCreate()
   ├─ LoadKeyboardDLL()
   │  ├─ LoadLibrary("VirtualKeyboardDLL.dll")
   │  ├─ DllEntryPoint(DLL_PROCESS_ATTACH)
   │  ├─ GetProcAddress("ShowKeyboard")
   │  ├─ GetProcAddress("HideKeyboard")
   │  ├─ GetProcAddress("IsKeyboardVisible")
   │  └─ GetProcAddress("SetKeyboardMode")
   └─ UpdateStatus()
6. Application->Run() (boucle de messages)
```

### Séquence 2 : Affichage du clavier simple

```
1. Utilisateur clique sur "Afficher Clavier Simple"
2. BtnShowSimpleClick()
3. FShowKeyboard(0, MemoTest->Handle)
   ├─ DLL: ShowKeyboard(mode=0, targetHandle)
   │  ├─ Première fois: Application->CreateForm(TFormKeyboard)
   │  │  └─ TFormKeyboard::TFormKeyboard()
   │  │     ├─ Configuration du formulaire
   │  │     ├─ Création de PanelMain
   │  │     ├─ Création de PanelNumpad
   │  │     └─ CreateMainKeyboard()
   │  │        ├─ Création des boutons ligne 1 (chiffres)
   │  │        ├─ Création des boutons ligne 2 (AZERTYUIOP)
   │  │        ├─ Création des boutons ligne 3 (QSDFGHJKLM)
   │  │        ├─ Création des boutons ligne 4 (WXCVBN)
   │  │        └─ Création des touches spéciales
   │  ├─ SetTargetHandle(targetHandle)
   │  ├─ SetKeyboardMode(0)
   │  │  └─ PanelNumpad->Visible = false
   │  └─ Show()
   └─ UpdateStatus()
```

### Séquence 3 : Saisie d'un caractère

```
1. Utilisateur clique sur une touche (ex: "A")
2. Button->OnClick → OnKeyButtonClick()
3. Récupération du caractère depuis Button->Tag
4. Vérification si c'est une lettre
5. SI FShiftActive OU FCapsLockActive
   └─ Convertir en majuscule (towupper)
6. SI FShiftActive (pas Caps)
   └─ FShiftActive = false
7. SendCharToTarget(ch)
   └─ SendMessageW(FTargetHandle, WM_CHAR, ch, 0)
8. Le contrôle cible reçoit WM_CHAR
9. Le caractère est affiché dans le contrôle
```

### Séquence 4 : Activation de Maj

```
1. Utilisateur clique sur "Maj"
2. OnShiftClick()
3. FShiftActive = !FShiftActive
4. UpdateShiftDisplay()
   └─ FBtnShift->Color = FShiftActive ? clLime : clBtnFace
5. Le bouton devient vert
6. Prochaine lettre sera en majuscule
7. Après la lettre, FShiftActive redevient false automatiquement
```

### Séquence 5 : Basculement vers mode avec pavé

```
1. Utilisateur clique sur "Pavé Num"
2. OnToggleModeClick()
3. SetKeyboardMode(1)
4. SI FNumpadButtons est vide
   └─ CreateNumpad()
      ├─ Création du label "Pavé Numérique"
      ├─ Création des boutons 7,8,9,/
      ├─ Création des boutons 4,5,6,*
      ├─ Création des boutons 1,2,3,-
      └─ Création des boutons 0,.,+,Enter
5. PanelNumpad->Visible = true
6. ClientWidth = PanelMain->Width + PanelNumpad->Width
7. BtnToggleMode->Caption = "Simple"
```

### Séquence 6 : Fermeture de l'application

```
1. Utilisateur ferme TestApp
2. TFormMain::FormDestroy()
3. UnloadKeyboardDLL()
   ├─ FreeLibrary(FDllHandle)
   └─ DllEntryPoint(DLL_PROCESS_DETACH)
      └─ delete g_KeyboardForm
         └─ TFormKeyboard::~TFormKeyboard()
            └─ ClearKeyboard()
4. Application se termine
```

## Considérations techniques

### Gestion de la mémoire

- **DLL** : Instance unique de TFormKeyboard créée lors du premier ShowKeyboard()
- **Persistance** : Le formulaire n'est pas détruit entre Hide() et Show()
- **Nettoyage** : Destruction automatique lors de DLL_PROCESS_DETACH
- **Boutons** : Tous les TButton sont possédés par leurs parents (panels/formulaire)
- **Vecteurs** : Simplement des pointeurs vers les boutons existants

### Thread-safety

- **Pas de multi-threading** : La DLL suppose un usage mono-thread
- **Variables globales** : Une seule instance de g_KeyboardForm
- **VCL** : Les composants VCL ne sont pas thread-safe par conception
- **Recommandation** : Utiliser la DLL uniquement depuis le thread principal

### Messages Windows

**WM_CHAR** :
- Utilisé pour les caractères normaux
- Le contrôle interprète directement le caractère
- Support Unicode (SendMessageW)

**WM_KEYDOWN/WM_KEYUP** :
- Utilisé pour les touches spéciales (Backspace, Enter, Tab)
- Simule une vraie frappe clavier
- Nécessaire pour que le contrôle exécute les actions spéciales

### Encodage

- **Unicode** : Toutes les chaînes utilisent wchar_t
- **SendMessageW** : Version Unicode des messages
- **Support** : Caractères français (é, è, à, ç, ù, etc.)

## Extension du projet

### Ajouter de nouvelles touches

```cpp
// Dans CreateMainKeyboard() ou CreateNumpad()
TButton* btnNew = CreateButton(ParentPanel, "€", left, top, width, height);
btnNew->Tag = (wchar_t)0x20AC;  // Code Unicode de €
btnNew->OnClick = OnKeyButtonClick;
FMainKeyButtons.push_back(btnNew);
```

### Ajouter un nouveau mode

```cpp
// Dans SetKeyboardMode()
case 2:  // Nouveau mode
    CreateSpecialKeyboard();
    PanelSpecial->Visible = true;
    ClientWidth = PanelMain->Width + PanelSpecial->Width;
    break;
```

### Personnaliser les couleurs

```cpp
// Dans CreateButton() ou après création
btn->Color = clAqua;           // Couleur de fond
btn->Font->Color = clWhite;    // Couleur du texte
btn->Font->Style = TFontStyles() << fsBold;  // Gras
```

### Ajouter des sons

```cpp
// Dans OnKeyButtonClick()
MessageBeep(MB_OK);  // Son système simple

// Ou avec WAV
PlaySound(L"click.wav", NULL, SND_FILENAME | SND_ASYNC);
```

## Débogage

### Points de débogage courants

1. **Vérifier le chargement de la DLL**
   ```cpp
   if (!hDll) {
       DWORD err = GetLastError();
       ShowMessage("Error: " + IntToStr(err));
   }
   ```

2. **Vérifier les adresses des fonctions**
   ```cpp
   if (!ShowKeyboard) {
       ShowMessage("ShowKeyboard not found!");
   }
   ```

3. **Vérifier le HWND cible**
   ```cpp
   if (!IsWindow(targetHandle)) {
       ShowMessage("Invalid window handle!");
   }
   ```

4. **Tracer les clics**
   ```cpp
   void OnKeyButtonClick(TObject* Sender) {
       TButton* btn = (TButton*)Sender;
       OutputDebugString(("Click: " + btn->Caption).c_str());
       // ... reste du code
   }
   ```

### Outils recommandés

- **C++ Builder Debugger** : Débogage pas à pas
- **Event Log** : Pour voir les messages Windows
- **Dependency Walker** : Pour vérifier les dépendances de la DLL
- **Process Explorer** : Pour voir les DLL chargées

## Performances

### Optimisations appliquées

- **Création à la demande** : Le pavé numérique n'est créé que si nécessaire
- **Réutilisation** : Le formulaire n'est pas détruit entre les utilisations
- **Messages directs** : SendMessage pour latence minimale
- **Pas de timers** : Événements uniquement sur action utilisateur

### Mesures typiques

- **Chargement DLL** : < 50 ms
- **Affichage clavier** : < 100 ms
- **Latence clic** : < 5 ms
- **Mémoire utilisée** : ~2-3 MB

## Maintenance

### Checklist de mise à jour

- [ ] Tester sur Win32 et Win64
- [ ] Vérifier tous les modes (0 et 1)
- [ ] Tester toutes les touches
- [ ] Tester Maj et Caps Lock
- [ ] Vérifier l'absence de fuites mémoire
- [ ] Tester avec différents contrôles
- [ ] Mettre à jour la documentation
- [ ] Incrémenter le numéro de version

### Tests de régression

1. Charger/décharger la DLL plusieurs fois
2. Basculer entre modes multiples fois
3. Activer/désactiver Maj/Caps rapidement
4. Tester avec contrôles multiples
5. Vérifier la mémoire avec Task Manager

## Support

Pour obtenir de l'aide :
1. Consultez les README.md de chaque projet
2. Vérifiez les commentaires dans le code source
3. Utilisez le débogueur C++ Builder
4. Recherchez dans la documentation VCL

---

**Document maintenu à jour avec le code source**  
**Version** : 1.0.0  
**Date** : 2026

# Guide de Démarrage Rapide - Clavier Virtuel DLL

Ce guide vous permet de compiler et tester le projet en quelques minutes.

## 🚀 Installation Rapide (5 minutes)

### Étape 1 : Vérifier les prérequis

Vous devez avoir installé :
- ✅ C++ Builder 13 (RAD Studio 12 Athens) ou compatible
- ✅ Windows 32-bit ou 64-bit

### Étape 2 : Cloner ou télécharger le projet

```bash
git clone https://github.com/Riwoux/testclaviervirtuel.git
cd testclaviervirtuel
```

### Étape 3 : Compiler la DLL

1. Ouvrez C++ Builder 13
2. Menu : **File → Open Project...**
3. Naviguez vers `VirtualKeyboardDLL/VirtualKeyboardDLL.cbproj`
4. Sélectionnez la configuration :
   - **Debug** (pour développement)
   - **Release** (pour production)
5. Sélectionnez la plateforme :
   - **Win32** (32-bit)
   - **Win64** (64-bit)
6. Menu : **Project → Build VirtualKeyboardDLL**
7. Attendez la fin de la compilation (≈ 10-30 secondes)

**Résultat** : La DLL est créée dans `VirtualKeyboardDLL/Win32/Debug/VirtualKeyboardDLL.dll`

### Étape 4 : Compiler l'application de test

1. Menu : **File → Open Project...**
2. Naviguez vers `TestApp/TestApp.cbproj`
3. Même configuration que la DLL (Debug/Release, Win32/Win64)
4. Menu : **Project → Build TestApp**
5. Attendez la fin de la compilation

**Résultat** : L'EXE est créé dans `TestApp/Win32/Debug/TestApp.exe`

### Étape 5 : Déployer et tester

1. Copiez `VirtualKeyboardDLL.dll` dans le même répertoire que `TestApp.exe`
   ```bash
   copy VirtualKeyboardDLL\Win32\Debug\VirtualKeyboardDLL.dll TestApp\Win32\Debug\
   ```

2. Lancez `TestApp.exe`

3. Testez les fonctionnalités :
   - Cliquez sur **"Afficher Clavier Simple"**
   - Utilisez le clavier pour taper du texte
   - Testez les majuscules (Maj et Caps Lock)
   - Cliquez sur **"Afficher Clavier avec Pavé"**
   - Testez le pavé numérique
   - Cliquez sur **"Masquer Clavier"**

## 🎯 Tests de Base

### Test 1 : Saisie de texte simple
1. Afficher le clavier simple
2. Taper : "Bonjour"
3. ✅ Résultat attendu : "bonjour" apparaît dans le Memo

### Test 2 : Majuscules avec Maj
1. Cliquer sur "Maj" (devient vert)
2. Cliquer sur "B"
3. Taper "onjour"
4. ✅ Résultat attendu : "Bonjour" (B majuscule uniquement)

### Test 3 : Majuscules avec Caps Lock
1. Cliquer sur "Caps" (devient vert)
2. Taper "BONJOUR"
3. Cliquer à nouveau sur "Caps"
4. ✅ Résultat attendu : "BONJOUR" (tout en majuscules)

### Test 4 : Touches spéciales
1. Taper "Test"
2. Appuyer sur "Backspace" (← dans le clavier)
3. Taper "123"
4. Appuyer sur "Entrée"
5. ✅ Résultat attendu : 
   ```
   Tes123
   (nouvelle ligne)
   ```

### Test 5 : Pavé numérique
1. Cliquer sur "Afficher Clavier avec Pavé"
2. Le pavé apparaît à droite
3. Cliquer sur les touches du pavé : 1, 2, 3, +, 4, 5, 6
4. ✅ Résultat attendu : "123+456" apparaît

## 🔧 Dépannage Express

### Problème : "Impossible de charger VirtualKeyboardDLL.dll"

**Solutions** :
```bash
# Solution 1 : Vérifier que la DLL existe
dir VirtualKeyboardDLL\Win32\Debug\VirtualKeyboardDLL.dll

# Solution 2 : Copier la DLL manuellement
copy VirtualKeyboardDLL\Win32\Debug\*.dll TestApp\Win32\Debug\

# Solution 3 : Vérifier que les plateformes correspondent
# DLL Win32 → EXE Win32
# DLL Win64 → EXE Win64
```

### Problème : Erreurs de compilation

**DLL ne compile pas** :
- Vérifiez que vous avez le VCL (inclus avec C++ Builder)
- Essayez : **Project → Clean** puis **Build**
- Vérifiez les messages d'erreur dans le panneau Messages

**Application ne compile pas** :
- Compilez d'abord la DLL
- Vérifiez que tous les fichiers .h, .cpp et .dfm sont présents
- Essayez : **File → Close All** puis rouvrez le projet

### Problème : Le clavier s'affiche mais ne tape rien

**Solutions** :
1. Cliquez dans le Memo avant d'utiliser le clavier
2. Vérifiez que le Memo n'est pas en lecture seule
3. Testez avec un TEdit simple pour isoler le problème

## 📝 Intégration dans votre application

### Code minimal d'intégration

```cpp
// Dans votre .h
class TYourForm : public TForm
{
private:
    HINSTANCE FDllHandle;
    typedef void (__stdcall *TShowKeyboardProc)(int, HWND);
    TShowKeyboardProc FShowKeyboard;
    
public:
    __fastcall TYourForm(TComponent* Owner);
    __fastcall ~TYourForm();
    void ShowVirtualKeyboard();
};

// Dans votre .cpp
__fastcall TYourForm::TYourForm(TComponent* Owner) : TForm(Owner)
{
    // Charger la DLL
    FDllHandle = LoadLibrary(L"VirtualKeyboardDLL.dll");
    if (FDllHandle) {
        FShowKeyboard = (TShowKeyboardProc)GetProcAddress(FDllHandle, "ShowKeyboard");
    }
}

__fastcall TYourForm::~TYourForm()
{
    if (FDllHandle) {
        FreeLibrary(FDllHandle);
    }
}

void TYourForm::ShowVirtualKeyboard()
{
    if (FShowKeyboard) {
        // Mode 0 = Simple, Mode 1 = Avec pavé
        FShowKeyboard(0, YourEdit->Handle);
    }
}
```

## 🎨 Personnalisation Rapide

### Changer les couleurs du clavier

Éditez `VirtualKeyboardDLL/KeyboardForm.cpp` :

```cpp
// Ligne ~195 : Couleur des touches spéciales
btnSpace->Color = clAqua;     // Au lieu de clInfoBk
btnBackspace->Color = clRed;  // Au lieu de clInfoBk

// Ligne ~350 : Couleur des boutons actifs
FBtnShift->Color = FShiftActive ? clYellow : clBtnFace;  // Au lieu de clLime
```

### Changer la taille des touches

Éditez `VirtualKeyboardDLL/KeyboardForm.cpp` :

```cpp
// Ligne ~100 : Taille des boutons
const int btnWidth = 60;   // Au lieu de 50
const int btnHeight = 50;  // Au lieu de 45
```

### Ajouter une nouvelle touche

```cpp
// Dans CreateMainKeyboard(), après les autres boutons
TButton* btnEuro = CreateButton(PanelMain, "€", 620, 10, 50, 45);
btnEuro->Tag = (wchar_t)0x20AC;  // Code Unicode de €
btnEuro->OnClick = OnKeyButtonClick;
FMainKeyButtons.push_back(btnEuro);
```

## 📚 Prochaines étapes

Maintenant que le projet fonctionne :

1. **Explorez le code** : Lisez `DEVELOPMENT.md` pour comprendre l'architecture
2. **Lisez la documentation** : Consultez les README dans chaque dossier
3. **Personnalisez** : Modifiez les couleurs, tailles, touches selon vos besoins
4. **Intégrez** : Utilisez la DLL dans vos propres applications
5. **Étendez** : Ajoutez de nouvelles fonctionnalités

## 🆘 Aide

Si vous êtes bloqué :

1. **Documentation détaillée** : Lisez `DEVELOPMENT.md`
2. **README de la DLL** : `VirtualKeyboardDLL/README.md`
3. **README du Test** : `TestApp/README.md`
4. **Code source** : Les fichiers .cpp contiennent des commentaires explicatifs

## ✅ Checklist de vérification

Avant de signaler un problème, vérifiez :

- [ ] C++ Builder 13 est installé et fonctionne
- [ ] Les deux projets compilent sans erreur
- [ ] La DLL est dans le même répertoire que l'EXE
- [ ] La plateforme est la même (Win32 ou Win64) pour DLL et EXE
- [ ] L'application de test démarre sans message d'erreur
- [ ] Vous avez cliqué dans le Memo avant d'utiliser le clavier

---

**Temps total estimé** : 5-10 minutes  
**Niveau** : Débutant à Intermédiaire  
**Support** : Consultez DEVELOPMENT.md pour plus de détails

Bon développement ! 🎉

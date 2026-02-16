# Application de Test - Clavier Virtuel DLL

Application de démonstration pour tester la DLL du clavier virtuel.

## Description

Cette application simple permet de tester les fonctionnalités de la DLL `VirtualKeyboardDLL.dll`. Elle contient :
- Un contrôle TMemo pour la saisie de texte
- Des boutons pour afficher le clavier en mode simple ou avec pavé numérique
- Un bouton pour masquer le clavier
- Un indicateur d'état

## Compilation

### Prérequis

- C++ Builder 13 (RAD Studio 12 Athens) ou version compatible
- VCL Framework
- La DLL VirtualKeyboardDLL.dll compilée

### Instructions

1. Compilez d'abord la DLL (voir `../VirtualKeyboardDLL/README.md`)
2. Ouvrez le projet `TestApp.cbproj` dans C++ Builder 13
3. Sélectionnez la configuration (Debug ou Release)
4. Choisissez la plateforme (Win32 ou Win64)
5. Menu : Project → Build TestApp
6. L'exécutable sera généré dans `Win32\Debug\` ou `Win32\Release\`

### Déploiement

Pour exécuter l'application :
1. Copiez `VirtualKeyboardDLL.dll` dans le même répertoire que `TestApp.exe`
2. Ou ajoutez le répertoire de la DLL au PATH système
3. Lancez `TestApp.exe`

## Utilisation

1. Lancez l'application
2. Cliquez dans la zone de texte (Memo)
3. Cliquez sur un des boutons :
   - **"Afficher Clavier Simple"** : Affiche le clavier en mode simple (Mode 0)
   - **"Afficher Clavier avec Pavé"** : Affiche le clavier avec pavé numérique (Mode 1)
   - **"Masquer Clavier"** : Cache le clavier
4. Utilisez le clavier virtuel pour saisir du texte
5. Le texte apparaît dans le Memo

## Fonctionnalités testées

### Mode Simple
- Toutes les lettres de l'alphabet (AZERTY)
- Chiffres et caractères spéciaux
- Majuscules (Maj et Caps Lock)
- Touches spéciales (Espace, Tab, Backspace, Entrée)

### Mode avec Pavé Numérique
- Toutes les fonctionnalités du mode simple
- Pavé numérique avec chiffres 0-9
- Opérateurs mathématiques (+, -, *, /)
- Point décimal
- Touche Entrée du pavé

### Basculement de mode
- Bouton pour passer d'un mode à l'autre
- Redimensionnement automatique de la fenêtre du clavier

## Structure des fichiers

```
TestApp/
├── TestApp.cbproj        # Fichier projet C++ Builder
├── TestApp.cpp           # Point d'entrée de l'application
├── MainForm.h            # Header du formulaire principal
├── MainForm.cpp          # Implémentation du formulaire
├── MainForm.dfm          # Design VCL du formulaire
└── README.md             # Ce fichier
```

## Code source

### Chargement de la DLL

Le formulaire principal charge dynamiquement la DLL au démarrage :

```cpp
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    if (!LoadKeyboardDLL()) {
        ShowMessage("Erreur: Impossible de charger VirtualKeyboardDLL.dll");
        // Désactiver les boutons
    }
}
```

### Affichage du clavier

```cpp
void __fastcall TFormMain::BtnShowSimpleClick(TObject *Sender)
{
    if (FShowKeyboard) {
        FShowKeyboard(0, MemoTest->Handle);  // Mode 0 = Simple
    }
}

void __fastcall TFormMain::BtnShowWithNumpadClick(TObject *Sender)
{
    if (FShowKeyboard) {
        FShowKeyboard(1, MemoTest->Handle);  // Mode 1 = Avec pavé
    }
}
```

### Nettoyage

La DLL est automatiquement déchargée à la fermeture :

```cpp
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    UnloadKeyboardDLL();
}
```

## Tests suggérés

1. **Test de saisie basique**
   - Saisir des lettres minuscules
   - Saisir des lettres majuscules avec Maj
   - Saisir des lettres majuscules avec Caps Lock
   - Vérifier que Maj se désactive après une lettre
   - Vérifier que Caps Lock reste actif

2. **Test des chiffres et caractères spéciaux**
   - Saisir les chiffres 0-9
   - Saisir les caractères spéciaux (&, é, ", ', etc.)
   - Tester les symboles (, -, è, _, ç, à, =, +)

3. **Test des touches spéciales**
   - Backspace : Supprimer des caractères
   - Entrée : Créer de nouvelles lignes
   - Espace : Insérer des espaces
   - Tab : Insérer des tabulations

4. **Test du pavé numérique** (Mode 1)
   - Saisir des chiffres du pavé
   - Tester les opérateurs (+, -, *, /)
   - Tester le point décimal
   - Utiliser la touche Entrée du pavé

5. **Test de basculement de mode**
   - Passer du mode simple au mode avec pavé
   - Passer du mode avec pavé au mode simple
   - Vérifier le redimensionnement de la fenêtre

6. **Test de visibilité**
   - Afficher et masquer le clavier plusieurs fois
   - Changer de mode pendant que le clavier est visible
   - Fermer l'application avec le clavier visible

## Problèmes connus

### La DLL ne se charge pas
**Symptôme** : Message d'erreur au démarrage de l'application

**Solutions** :
1. Vérifiez que `VirtualKeyboardDLL.dll` est dans le même répertoire que `TestApp.exe`
2. Vérifiez que la DLL est compilée pour la même plateforme (Win32 ou Win64)
3. Vérifiez que les runtimes C++ Builder sont installés

### Les caractères ne s'affichent pas
**Symptôme** : Le clavier s'affiche mais rien ne se passe quand on clique

**Solutions** :
1. Vérifiez que le Memo a le focus
2. Essayez de cliquer dans le Memo avant d'utiliser le clavier
3. Vérifiez les logs pour les erreurs de SendMessage

## Extension de l'application

Pour étendre cette application de test, vous pouvez :

1. **Ajouter d'autres contrôles**
   ```cpp
   TEdit* Edit1 = new TEdit(this);
   // ... configuration ...
   FShowKeyboard(0, Edit1->Handle);
   ```

2. **Tester avec d'autres types de contrôles**
   - TRichEdit
   - Contrôles tiers
   - Contrôles personnalisés

3. **Ajouter des options de configuration**
   - Taille du clavier
   - Position du clavier
   - Thème de couleurs

4. **Monitorer les événements**
   - Logger les caractères envoyés
   - Mesurer les performances
   - Détecter les erreurs

## Support

Pour plus d'informations sur la DLL, consultez `../VirtualKeyboardDLL/README.md`

## Licence

Application de démonstration - Gratuite pour usage personnel et commercial.

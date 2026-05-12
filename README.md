# dll-virtual-keyboard

Ce dépôt contient plusieurs **essais de clavier virtuel** (approches légèrement différentes), plus une appli de test.

## Dossiers

- **`touchkeyboard/`**  
  Premier essai basé sur `TTouchKeyboard` (VCL), avec affichage clavier standard ou pavé numérique.

- **`superv_keyboard/`**  
  Variante DLL proche de `touchkeyboard`, avec ajustements de comportement/focus et usage en contexte applicatif.

- **`VirtualKeyboard/`**  
  Version DLL plus avancée (auto-positionnement, ratio de taille, gestion du focus plus robuste, mode auto).

- **`VirtualKeyboardDLL/`**  
  Essai alternatif avec un clavier construit de façon plus personnalisée (boutons, layouts/langues, logique propre), sans dépendre uniquement du composant standard.

- **`TestApp/`**  
  Petite application de test pour vérifier que la DLL clavier se charge bien et que les fonctions d’affichage/masquage marchent.

## Différence globale

Les dossiers `touchkeyboard`, `superv_keyboard`, `VirtualKeyboard` et `VirtualKeyboardDLL` représentent des **itérations différentes du clavier virtuel**.  
`TestApp` sert uniquement à **valider rapidement le fonctionnement** de ces DLL.

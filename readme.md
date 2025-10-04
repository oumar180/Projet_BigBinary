# Projet C – Manipulation de grands entiers binaires

## 📘 Présentation

Ce projet a pour objectif d’implémenter une bibliothèque en langage **C** permettant de manipuler des **grands entiers binaires** (`BigBinary`) et de réaliser des opérations arithmétiques de base sans utiliser les types numériques standards (`int`, `long`, etc.).  
Il s’agit d’un travail d’apprentissage portant sur la représentation des nombres binaires, la gestion de la mémoire et l’implémentation d’opérations arithmétiques bit à bit.

Le projet repose sur trois fichiers principaux :
- **`bigbinary.h`** : contient la définition de la structure `BigBinary` et les prototypes de toutes les fonctions.
- **`bigbinary.c`** : contient l’implémentation des fonctions (création, affichage, addition, soustraction, etc.).
- **`main.c`** : programme de test principal pour vérifier le bon fonctionnement de chaque opération.

---

## 🧩 Structure du projet

untitled2/
├── CMakeLists.txt
├── main.c
├── bigbinary.c
├── bigbinary.h
└── README.md



---

## ⚙️ Fonctionnalités réalisées

### 🔹 Phase 1 – Manipulation de base
- Création d’un `BigBinary` à partir d’une chaîne binaire (`"1011"` → 11 en décimal).
- Affichage d’un nombre binaire (avec ou sans zéros de tête).
- Addition binaire bit à bit (avec gestion de la retenue).
- Soustraction binaire bit à bit (avec gestion de l’emprunt).

✅ Ces fonctionnalités ont été testées dans `main.c` et fonctionnent correctement.

**Exemple d’exécution :**
A = 1011
B = 110
A + B = 10001
A - B = 0101



### 🔹 Phase 2 – Fonctions arithmétiques avancées (en préparation)
Les fonctions suivantes sont définies mais encore à optimiser :
- `PGCD()` : calcul du plus grand commun diviseur (version naïve).
- `Modulo()` : soustraction répétée pour obtenir le reste.
- `expMod()` : exponentiation modulaire (version à corriger pour RSA).

### 🔹 Phase 3 – Chiffrement RSA (à venir)
- Implémentation du chiffrement et du déchiffrement RSA à l’aide de l’exponentiation modulaire rapide.

---

## 🏗️ Compilation et exécution

### ▶️ Depuis CLion
1. Ouvrir le projet dans **JetBrains CLion**.
2. Vérifier que le fichier `CMakeLists.txt` contient :
   ```cmake
   add_executable(untitled1
           main.c
           bigbinary.c
   )
En haut à droite, sélectionner la cible untitled2 

Appuyer sur Run ▶ pour exécuter le programme.

💻 Depuis un terminal (hors CLion)
bash
Copier le code
gcc main.c bigbinary.c -o projet
./projet
🧠 Détails techniques
Structure principale :


typedef struct {
int *Tdigits; // Tableau de bits (0 ou 1)
int Taille;   // Taille du tableau
int Signe;    // +1, 0 ou -1
} BigBinary;
Les nombres binaires sont manipulés directement en mémoire sous forme de tableaux dynamiques.

Le signe du nombre est géré manuellement (Signe = +1 pour positif, -1 pour négatif, 0 pour nul).

Une fonction de libération (libereBigBinary) permet d’éviter toute fuite mémoire.

🚀 Améliorations prévues
Optimiser le calcul du PGCD et du Modulo (algorithme d’Euclide rapide).

Ajouter une fonction de multiplication binaire.

Corriger et valider l’implémentation de l’exponentiation modulaire (expMod).

Intégrer un chiffrement RSA fonctionnel avec clés publiques et privées.

Ajouter des tests unitaires automatiques (via CTest ou assertions).

🧩 Environnement de développement
IDE : JetBrains CLion 2025.2.1

Compilateur : MinGW (gcc 13.x)

Standard C : C11

Système : Windows 11 (x64)
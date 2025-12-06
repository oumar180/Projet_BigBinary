/**
 * @file bigbinary.c
 * @brief Implémentation de la bibliothèque BigBinary
 * 
 * Ce fichier contient l'implémentation de toutes les fonctions permettant
 * de manipuler des grands entiers binaires. Les algorithmes sont conformes
 * au cahier des charges des phases 1 et 2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================================================================
// STRUCTURE DE DONNÉES
// ============================================================================

/**
 * @struct BigBinary
 * @brief Structure représentant un grand entier binaire
 * 
 * Les bits sont stockés du MSB (Most Significant Bit, index 0) 
 * au LSB (Least Significant Bit, index Taille-1).
 */
typedef struct {
    int *Tdigits;  /**< Tableau dynamique de bits (0 ou 1). Index 0 = bit de poids fort */
    int Taille;    /**< Nombre de bits dans le tableau */
    int Signe;     /**< Signe : 0 = nul, +1 = positif, -1 = négatif */
} BigBinary;

// ============================================================================
// PHASE 1 : CRÉATION ET INITIALISATION
// ============================================================================

/**
 * @brief Crée un BigBinary avec une taille donnée
 * 
 * Alloue la mémoire pour un tableau de bits de la taille spécifiée.
 * Le signe est initialisé à 0 (nul).
 * 
 * @param size Taille du tableau de bits à allouer
 * @return BigBinary avec la mémoire allouée
 */
BigBinary createBigBinary(int size) {
    BigBinary bb;
    bb.Tdigits = malloc(sizeof(int) * size);
    bb.Taille = size;
    bb.Signe = 0;  // Initialisé à nul par défaut
    return bb;
}

/**
 * @brief Initialise un BigBinary avec une taille et un signe
 * 
 * Alloue la mémoire et initialise tous les bits à 0.
 * 
 * @param taille Nombre de bits à allouer
 * @param signe Signe du nombre (0, +1, ou -1)
 * @return BigBinary initialisé avec tous les bits à 0
 */
BigBinary initBigBinary(int taille, int signe) {
    BigBinary nb;
    nb.Taille = taille;
    nb.Signe = signe;
    nb.Tdigits = malloc(sizeof(int) * taille);
    // Initialiser tous les bits à 0
    for (int i = 0; i < taille; ++i) nb.Tdigits[i] = 0;
    return nb;
}

/**
 * @brief Crée un BigBinary à partir d'une chaîne de caractères binaire
 * 
 * Parse une chaîne contenant des '0' et '1' et crée un BigBinary correspondant.
 * Les caractères autres que '0' et '1' sont ignorés (espaces, etc.).
 * 
 * Exemple : creerBigBinaryDepuisChaine("1011") crée le nombre binaire 1011
 * 
 * @param chaine Chaîne de caractères contenant la représentation binaire
 * @return BigBinary créé à partir de la chaîne
 */
BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int n = strlen(chaine);
    nb.Taille = 0;

    // Étape 1 : Compter le nombre de bits valides ('0' ou '1') dans la chaîne
    for (int i = 0; i < n; ++i)
        if (chaine[i] == '0' || chaine[i] == '1') nb.Taille++;

    // Étape 2 : Allouer la mémoire pour le tableau de bits
    nb.Tdigits = malloc(sizeof(int) * nb.Taille);
    nb.Signe = +1;  // Par défaut, le nombre est positif
    int index = 0;
    int tousZeros = 1;  // Flag pour détecter si tous les bits sont à 0

    // Étape 3 : Copier les bits de la chaîne dans le tableau
    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            // Convertir le caractère '0' ou '1' en entier 0 ou 1
            nb.Tdigits[index] = chaine[i] - '0';
            // Si on trouve au moins un bit à 1, le nombre n'est pas nul
            if (nb.Tdigits[index] == 1) tousZeros = 0;
            index++;
        }
    }

    // Si tous les bits sont à 0, le nombre est nul
    if (tousZeros) nb.Signe = 0;
    return nb;
}

/**
 * @brief Copie un BigBinary
 * 
 * Crée une copie indépendante d'un BigBinary (alloue une nouvelle mémoire).
 * 
 * @param src BigBinary source à copier
 * @return Nouveau BigBinary copié
 */
BigBinary copyBigBinary(BigBinary src) {
    BigBinary dest = initBigBinary(src.Taille, src.Signe);
    // Copier tous les bits
    for (int i = 0; i < src.Taille; i++) dest.Tdigits[i] = src.Tdigits[i];
    return dest;
}

// ============================================================================
// PHASE 1 : AFFICHAGE ET LIBÉRATION
// ============================================================================

/**
 * @brief Affiche un BigBinary sur la sortie standard
 * 
 * Affiche le signe (si négatif) puis tous les bits du nombre binaire.
 * Affiche "0" si le nombre est nul.
 * 
 * Format d'affichage : 
 * - Si négatif : "-" suivi des bits
 * - Si nul : "0"
 * - Sinon : les bits directement
 * 
 * @param nb Le BigBinary à afficher
 */
void afficheBigBinary(BigBinary nb) {
    // Afficher le signe moins si le nombre est négatif
    if (nb.Signe == -1) printf("-");
    
    // Si le nombre est nul ou vide, afficher "0"
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0\n");
        return;
    }
    
    // Afficher tous les bits du nombre binaire
    for (int i = 0; i < nb.Taille; ++i) printf("%d", nb.Tdigits[i]);
    printf("\n");
}

/**
 * @brief Libère la mémoire allouée pour un BigBinary
 * 
 * Cette fonction doit être appelée pour chaque BigBinary créé
 * afin d'éviter les fuites mémoire. Après l'appel, le BigBinary
 * est réinitialisé (Tdigits = NULL, Taille = 0, Signe = 0).
 * 
 * @param nb Pointeur vers le BigBinary à libérer
 */
void libereBigBinary(BigBinary *nb) {
    free(nb->Tdigits);      // Libérer le tableau de bits
    nb->Tdigits = NULL;     // Sécurité : mettre le pointeur à NULL
    nb->Taille = 0;         // Réinitialiser la taille
    nb->Signe = 0;          // Réinitialiser le signe
}

// ============================================================================
// PHASE 1 : COMPARAISONS
// ============================================================================

/**
 * @brief Teste si deux BigBinary sont égaux
 * 
 * Deux nombres sont égaux s'ils ont :
 * - La même taille
 * - Le même signe
 * - Les mêmes bits à chaque position
 * 
 * @param A Premier nombre
 * @param B Deuxième nombre
 * @return true si A == B, false sinon
 */
bool Egal(BigBinary A, BigBinary B) {
    // Si les tailles ou les signes diffèrent, les nombres ne sont pas égaux
    if (A.Taille != B.Taille || A.Signe != B.Signe) return false;
    
    // Comparer bit par bit
    for (int i = 0; i < A.Taille; i++)
        if (A.Tdigits[i] != B.Tdigits[i]) return false;
    
    return true;
}

/**
 * @brief Teste si A est strictement inférieur à B
 * 
 * Comparaison lexicographique :
 * 1. Si les tailles diffèrent, le plus petit est celui avec la plus petite taille
 * 2. Sinon, on compare bit par bit du MSB au LSB
 * 
 * @param A Premier nombre
 * @param B Deuxième nombre
 * @return true si A < B, false sinon
 */
bool Inferieur(BigBinary A, BigBinary B) {
    // Si les tailles diffèrent, le nombre avec la plus petite taille est plus petit
    if (A.Taille != B.Taille) return A.Taille < B.Taille;
    
    // Si les tailles sont égales, comparer bit par bit du MSB au LSB
    for (int i = 0; i < A.Taille; i++) {
        if (A.Tdigits[i] < B.Tdigits[i]) return true;   // A < B
        if (A.Tdigits[i] > B.Tdigits[i]) return false;  // A > B
        // Si égaux, continuer à la position suivante
    }
    
    // Si tous les bits sont égaux, A n'est pas strictement inférieur à B
    return false;
}

// ============================================================================
// PHASE 1 : OPÉRATIONS ARITHMÉTIQUES DE BASE
// ============================================================================

/**
 * @brief Additionne deux BigBinary
 * 
 * Effectue l'addition binaire bit à bit avec gestion de la retenue (carry).
 * L'algorithme parcourt les bits de droite à gauche (du LSB au MSB).
 * 
 * Principe :
 * - Pour chaque position, on additionne : bitA + bitB + retenue
 * - Le résultat à cette position = (bitA + bitB + retenue) mod 2
 * - La nouvelle retenue = (bitA + bitB + retenue) / 2
 * 
 * Le résultat peut avoir un bit de plus que le plus grand des deux opérandes
 * (en cas de retenue finale).
 * 
 * @param A Premier opérande
 * @param B Deuxième opérande
 * @return BigBinary contenant A + B
 */
BigBinary Addition(BigBinary A, BigBinary B) {
    // La taille du résultat est au maximum max(A.Taille, B.Taille) + 1
    // (pour gérer la retenue finale)
    int maxTaille = (A.Taille > B.Taille) ? A.Taille : B.Taille;
    BigBinary res = initBigBinary(maxTaille + 1, +1);

    int carry = 0;  // Retenue initialisée à 0
    
    // Parcourir les bits de droite à gauche (du LSB au MSB)
    // i = index dans le résultat, j = index dans A, k = index dans B
    for (int i = res.Taille - 1, j = A.Taille - 1, k = B.Taille - 1; i >= 0; i--, j--, k--) {
        // Récupérer les bits (0 si on dépasse les limites)
        int bitA = (j >= 0) ? A.Tdigits[j] : 0;
        int bitB = (k >= 0) ? B.Tdigits[k] : 0;
        
        // Calculer la somme : bitA + bitB + retenue
        int sum = bitA + bitB + carry;
        
        // Le bit du résultat = somme mod 2
        res.Tdigits[i] = sum % 2;
        
        // La nouvelle retenue = somme / 2
        carry = sum / 2;
    }

    // Ajuster le signe si le résultat est nul (tous les bits à 0)
    int tousZeros = 1;
    for (int i = 0; i < res.Taille; i++) 
        if (res.Tdigits[i] == 1) tousZeros = 0;
    if (tousZeros) res.Signe = 0;

    return res;
}

/**
 * @brief Soustrait B de A (calcule A - B)
 * 
 * Effectue la soustraction binaire bit à bit avec gestion de l'emprunt (borrow).
 * L'algorithme parcourt les bits de droite à gauche (du LSB au MSB).
 * 
 * Principe :
 * - Pour chaque position, on soustrait : bitA - bitB - emprunt
 * - Si bitA < bitB + emprunt, on emprunte 2 (en binaire) et on met borrow = 1
 * - Sinon, on fait la soustraction normalement
 * 
 * ATTENTION : Cette fonction suppose que A >= B. Pour A < B, le résultat
 * peut être incorrect (bits négatifs non gérés).
 * 
 * @param A Premier opérande (doit être >= B)
 * @param B Deuxième opérande
 * @return BigBinary contenant A - B
 */
BigBinary Soustraction(BigBinary A, BigBinary B) {
    // Le résultat a la même taille que A
    BigBinary res = initBigBinary(A.Taille, +1);
    int borrow = 0;  // Emprunt initialisé à 0
    int offset = A.Taille - B.Taille;  // Décalage pour aligner B avec A

    // Parcourir les bits de droite à gauche (du LSB au MSB)
    for (int i = A.Taille - 1; i >= 0; i--) {
        // Soustraire l'emprunt précédent de bitA
        int bitA = A.Tdigits[i] - borrow;
        
        // Récupérer le bit correspondant de B (0 si on dépasse)
        int bitB = (i - offset >= 0) ? B.Tdigits[i - offset] : 0;

        // Si bitA < bitB, on doit emprunter
        if (bitA < bitB) {
            bitA += 2;  // Emprunter 2 (en binaire)
            borrow = 1; // Marquer qu'on a emprunté
        } else {
            borrow = 0; // Pas besoin d'emprunter
        }
        
        // Calculer le bit du résultat
        res.Tdigits[i] = bitA - bitB;
    }

    // Vérifier si le résultat est nul (tous les bits à 0)
    int tousZeros = 1;
    for (int i = 0; i < res.Taille; i++) 
        if (res.Tdigits[i] == 1) tousZeros = 0;
    if (tousZeros) res.Signe = 0;

    return res;
}


// ============================================================================
// FONCTIONS UTILITAIRES
// ============================================================================

/**
 * @brief Supprime les zéros en tête (leading zeros) d'un BigBinary
 * 
 * Cette fonction optimise la représentation en supprimant les zéros
 * non significatifs au début du nombre. Par exemple, "0001011" devient "1011".
 * 
 * Si tous les bits sont à 0, le signe est mis à 0 (nul).
 * 
 * @param nb Pointeur vers le BigBinary à optimiser
 */
void trimLeadingZeros(BigBinary *nb) {
    // Trouver la position du premier bit à 1
    int firstOne = 0;
    while (firstOne < nb->Taille && nb->Tdigits[firstOne] == 0) 
        firstOne++;
    
    // Si tous les bits sont à 0, le nombre est nul
    if (firstOne == nb->Taille) {
        nb->Signe = 0;
        return;
    }
    
    // Si on a des zéros en tête, les supprimer en décalant les bits
    if (firstOne > 0) {
        int newSize = nb->Taille - firstOne;
        // Décaler tous les bits vers la gauche
        for (int i = 0; i < newSize; i++) 
            nb->Tdigits[i] = nb->Tdigits[i + firstOne];
        nb->Taille = newSize;
    }
}

/**
 * @brief Multiplie deux BigBinary (multiplication classique)
 * 
 * Utilise l'algorithme de multiplication binaire classique (shift-and-add).
 * 
 * Principe :
 * - Pour chaque bit de B (de droite à gauche) :
 *   - Si le bit est 1, on décale A vers la gauche et on l'ajoute au résultat
 *   - Si le bit est 0, on ne fait rien
 * - Le décalage correspond à la position du bit dans B
 * 
 * Exemple : A = 101, B = 110
 * - Bit 0 de B (0) : rien
 * - Bit 1 de B (1) : ajouter 1010 (A décalé de 1)
 * - Bit 2 de B (1) : ajouter 10100 (A décalé de 2)
 * Résultat : 1010 + 10100 = 11110
 * 
 * @param A Premier opérande
 * @param B Deuxième opérande
 * @return BigBinary contenant A * B
 */
BigBinary Multiplication(BigBinary A, BigBinary B) {
    // Le résultat final commence à 0
    BigBinary resultat = creerBigBinaryDepuisChaine("0");

    // Parcourir les bits de B de droite à gauche (du LSB au MSB)
    // i = position du bit dans B (de droite à gauche)
    for (int i = B.Taille - 1; i >= 0; i--) {
        // Si le bit actuel de B est '1', on doit ajouter A décalé
        if (B.Tdigits[i] == 1) {
            // Calculer le décalage nécessaire pour A
            // Le bit à la position i dans B correspond à un décalage de (B.Taille - 1 - i)
            int decalage = B.Taille - 1 - i;

            // Créer une version de A décalée vers la gauche (ajouter des zéros à droite)
            BigBinary a_decale = initBigBinary(A.Taille + decalage, A.Signe);

            // Copier les bits de A au début du nouveau tableau
            for (int j = 0; j < A.Taille; j++) {
                a_decale.Tdigits[j] = A.Tdigits[j];
            }
            // Les zéros à la fin pour le décalage sont déjà là grâce à initBigBinary

            // Additionner ce nombre décalé au résultat cumulé
            BigBinary nouvelle_somme = Addition(resultat, a_decale);

            // Nettoyer la mémoire et mettre à jour le résultat
            libereBigBinary(&resultat);
            libereBigBinary(&a_decale);
            resultat = nouvelle_somme;
        }
    }

    // Gestion du signe du résultat final
    // Si l'un des opérandes est nul, le résultat est nul
    if (A.Signe == 0 || B.Signe == 0) {
        resultat.Signe = 0;
    } else {
        // Sinon, le signe est le produit des signes
        resultat.Signe = A.Signe * B.Signe;
    }

    // Supprimer les zéros en tête pour optimiser
    trimLeadingZeros(&resultat);
    return resultat;
}

// ============================================================================
// FONCTIONS UTILITAIRES POUR LES ALGORITHMES AVANCÉS
// ============================================================================

/**
 * @brief Vérifie si un BigBinary est pair
 * 
 * Un nombre binaire est pair si son bit de poids faible (LSB, dernier bit) est 0.
 * Le nombre 0 est considéré comme pair.
 * 
 * @param nb Le BigBinary à tester
 * @return true si nb est pair, false sinon
 */
bool estPair(BigBinary nb) {
    // Le nombre 0 est pair
    if (nb.Taille == 0 || nb.Signe == 0) return true;
    
    // Un nombre est pair si son dernier bit (LSB) est 0
    return (nb.Tdigits[nb.Taille - 1] == 0);
}

/**
 * @brief Divise un BigBinary par 2 (décalage à droite)
 * 
 * En binaire, diviser par 2 équivaut à un décalage à droite (shift right).
 * On retire simplement le bit de poids faible (LSB).
 * 
 * Exemple : 1010 (10) / 2 = 101 (5)
 * 
 * @param A Le BigBinary à diviser
 * @return BigBinary contenant A / 2
 */
BigBinary divisionPar2(BigBinary A) {
    // Si A est nul ou vide, A/2 = 0
    if (A.Taille == 0 || A.Signe == 0) {
        return creerBigBinaryDepuisChaine("0");
    }
    
    // Si A n'a qu'un seul bit et c'est 1, alors A/2 = 0
    if (A.Taille == 1 && A.Tdigits[0] == 1) {
        return creerBigBinaryDepuisChaine("0");
    }
    
    // Sinon, on décale à droite en retirant le dernier bit
    BigBinary res = initBigBinary(A.Taille - 1, A.Signe);
    // Copier tous les bits sauf le dernier
    for (int i = 0; i < res.Taille; i++) {
        res.Tdigits[i] = A.Tdigits[i];
    }
    trimLeadingZeros(&res);
    return res;
}

/**
 * @brief Multiplie un BigBinary par 2^k (décalage à gauche k fois)
 * 
 * En binaire, multiplier par 2^k équivaut à un décalage à gauche de k positions.
 * On ajoute k zéros à droite.
 * 
 * Exemple : 101 (5) * 2^2 = 10100 (20)
 * 
 * @param A Le BigBinary à multiplier
 * @param k La puissance de 2 (nombre de décalages)
 * @return BigBinary contenant A * 2^k
 */
BigBinary multiplicationPar2k(BigBinary A, int k) {
    // Si k = 0, A * 2^0 = A
    if (k == 0) return copyBigBinary(A);
    
    // Si A est nul, A * 2^k = 0
    if (A.Signe == 0) return creerBigBinaryDepuisChaine("0");
    
    // Créer un résultat avec k bits supplémentaires à droite
    BigBinary res = initBigBinary(A.Taille + k, A.Signe);
    
    // Copier A au début
    for (int i = 0; i < A.Taille; i++) {
        res.Tdigits[i] = A.Tdigits[i];
    }
    // Les k bits à droite sont déjà à 0 grâce à initBigBinary
    return res;
}

// ============================================================================
// PHASE 2 : MULTIPLICATION ÉGYPTIENNE
// ============================================================================

/**
 * @brief Multiplie deux BigBinary avec l'algorithme de Multiplication Égyptienne
 * 
 * Algorithme ancien et efficace, particulièrement adapté aux grands entiers binaires.
 * 
 * Principe de l'algorithme :
 * 1. On double A (A = A + A, équivalent à A * 2)
 * 2. On divise B par 2 (B = B / 2, décalage à droite)
 * 3. Si B est impair (dernier bit = 1), on ajoute A au résultat
 * 4. On continue jusqu'à ce que B = 0
 * 
 * Exemple : A = 5 (101), B = 6 (110)
 * Itération 1: B=110 (pair) → A=1010, B=11, résultat=0
 * Itération 2: B=11 (impair) → A=10100, B=1, résultat=1010
 * Itération 3: B=1 (impair) → A=101000, B=0, résultat=1010+101000=110010 (30)
 * 
 * Avantages :
 * - N'utilise que des additions et des décalages (très rapide)
 * - Pas de multiplications complexes
 * - Parfaitement adapté aux grands entiers binaires
 * 
 * @param A Premier opérande
 * @param B Deuxième opérande
 * @return BigBinary contenant A * B
 */
BigBinary MultiplicationEgyptienne(BigBinary A, BigBinary B) {
    // Si l'un des opérandes est nul, le résultat est nul
    if (A.Signe == 0 || B.Signe == 0) {
        return creerBigBinaryDepuisChaine("0");
    }
    
    // Initialiser le résultat à 0
    BigBinary resultat = creerBigBinaryDepuisChaine("0");
    BigBinary a = copyBigBinary(A);  // Copie de A pour pouvoir la modifier
    BigBinary b = copyBigBinary(B);  // Copie de B pour pouvoir la modifier
    
    // Boucle principale : continuer tant que B n'est pas nul
    while (b.Signe != 0) {
        // Si B est impair (dernier bit = 1), ajouter A au résultat
        // C'est le principe de la multiplication égyptienne
        if (!estPair(b)) {
            BigBinary temp = Addition(resultat, a);
            libereBigBinary(&resultat);
            resultat = temp;
        }
        
        // Doubler A (A = A + A, équivalent à A * 2 en binaire)
        // En binaire, doubler = décalage à gauche de 1 bit = addition A + A
        BigBinary a_double = Addition(a, a);
        libereBigBinary(&a);
        a = a_double;
        
        // Diviser B par 2 (B = B / 2, décalage à droite de 1 bit)
        BigBinary b_div2 = divisionPar2(b);
        libereBigBinary(&b);
        b = b_div2;
    }
    
    // Libérer les copies temporaires
    libereBigBinary(&a);
    libereBigBinary(&b);
    
    // Gestion du signe du résultat
    // Si les signes sont différents, le résultat est négatif
    if (A.Signe * B.Signe < 0) {
        resultat.Signe = -1;
    } else {
        resultat.Signe = +1;
    }
    
    // Supprimer les zéros en tête pour optimiser
    trimLeadingZeros(&resultat);
    return resultat;
}

// ============================================================================
// PHASE 2 : MODULO "DIVISION-FREE MOD"
// ============================================================================

/**
 * @brief Calcule A modulo B avec l'algorithme "Division-free mod"
 * 
 * Algorithme conforme au cahier des charges (phase 2.pdf) :
 * 
 * Principe :
 * - Si A = B × q + r avec 2^k ≤ q < 2^(k+1), alors :
 *   Modulo(A, B) = Modulo(A - 2^k × B, B)
 * - On trouve le plus grand k tel que A >= 2^k × B
 * - On soustrait 2^k × B de A
 * - On répète jusqu'à ce que A < B
 * 
 * Exemple du document : A=192, B=33
 * - k=2 : 2^2 × 33 = 132 ≤ 192 < 264 = 2^3 × 33
 * - On soustrait : 192 - 132 = 60
 * - On continue : Modulo(60, 33) = 27
 * 
 * Avantages :
 * - Évite les divisions (conforme au cahier des charges)
 * - Utilise uniquement des additions et soustractions
 * - Utilise des puissances de 2 (faciles à calculer en binaire)
 * 
 * @param A Dividende
 * @param B Diviseur (doit être non nul)
 * @return BigBinary contenant A mod B
 */
BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    // Cas d'erreur : division par zéro
    if (B.Taille == 0 || (B.Taille == 1 && B.Tdigits[0] == 0) || B.Signe == 0) {
        return creerBigBinaryDepuisChaine("0");
    }
    
    // Cas de base : si A < B, alors A mod B = A
    if (Inferieur(A, B)) {
        return copyBigBinary(A);
    }
    
    // Cas de base : si A = B, alors A mod B = 0
    if (Egal(A, B)) {
        return creerBigBinaryDepuisChaine("0");
    }
    
    // Copie de A pour pouvoir la modifier
    BigBinary a = copyBigBinary(A);
    
    // Boucle principale : tant que a >= B, on soustrait des puissances de 2 * B
    while (!Inferieur(a, B) && !Egal(a, B)) {
        // ÉTAPE 1 : Trouver le plus grand k tel que a >= 2^k * B
        // On cherche k tel que 2^k * B <= a < 2^(k+1) * B
        int k = 0;
        BigBinary deux_puissance_k_B = copyBigBinary(B);  // Commence avec 2^0 * B = B
        
        // On cherche le plus grand k tel que 2^(k+1) * B <= a
        // On double progressivement jusqu'à dépasser a
        while (true) {
            // Calculer 2^(k+1) * B = 2 * (2^k * B) = (2^k * B) + (2^k * B)
            BigBinary deux_puissance_k_plus_1_B = Addition(deux_puissance_k_B, deux_puissance_k_B);
            
            // Si 2^(k+1) * B <= a, on peut continuer à augmenter k
            if (Inferieur(deux_puissance_k_plus_1_B, a) || Egal(deux_puissance_k_plus_1_B, a)) {
                libereBigBinary(&deux_puissance_k_B);
                deux_puissance_k_B = deux_puissance_k_plus_1_B;
                k++;  // On peut augmenter k
            } else {
                // On a dépassé a, donc on s'arrête
                // Maintenant on a : 2^k * B <= a < 2^(k+1) * B
                libereBigBinary(&deux_puissance_k_plus_1_B);
                break;
            }
        }
        
        // ÉTAPE 2 : Soustraire 2^k * B de a
        // Maintenant on a 2^k * B <= a < 2^(k+1) * B
        // On soustrait 2^k * B de a
        BigBinary temp = Soustraction(a, deux_puissance_k_B);
        libereBigBinary(&a);
        libereBigBinary(&deux_puissance_k_B);
        a = temp;
        trimLeadingZeros(&a);
        
        // Si a est devenu nul, le reste est 0
        if (a.Signe == 0) {
            libereBigBinary(&a);
            return creerBigBinaryDepuisChaine("0");
        }
    }
    
    // À ce stade, a < B, donc a est le reste de la division
    return a;
}

// ============================================================================
// PHASE 2 : PGCD BINAIRE D'EUCLIDE
// ============================================================================

/**
 * @brief Calcule le PGCD de A et B avec l'algorithme binaire d'Euclide
 * 
 * Algorithme binaire conforme au cahier des charges (phase 2.pdf) :
 * 
 * Principe de l'algorithme binaire :
 * 1. Si A et B sont pairs : PGCD(A,B) = 2 × PGCD(A/2, B/2)
 * 2. Si A est pair et B impair : PGCD(A,B) = PGCD(A/2, B)
 * 3. Si A est impair et B pair : PGCD(A,B) = PGCD(A, B/2)
 * 4. Si A et B sont impairs et A >= B : PGCD(A,B) = PGCD((A-B)/2, B)
 * 5. Si A et B sont impairs et A < B : PGCD(A,B) = PGCD((B-A)/2, A)
 * 6. Cas de base : PGCD(A, 0) = A
 * 
 * Avantages de l'algorithme binaire :
 * - Évite les divisions/modulo (conforme au cahier des charges)
 * - Utilise uniquement :
 *   - Des soustractions
 *   - Des multiplications/divisions par 2 (décalages, très rapides en binaire)
 * - Plus efficace que l'algorithme classique pour les grands nombres
 * 
 * @param A Premier nombre
 * @param B Deuxième nombre
 * @return BigBinary contenant PGCD(A, B)
 */
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    // Cas de base : PGCD(A, 0) = A
    if (B.Signe == 0 || (B.Taille == 1 && B.Tdigits[0] == 0)) {
        return copyBigBinary(A);
    }
    // Cas de base : PGCD(0, B) = B
    if (A.Signe == 0 || (A.Taille == 1 && A.Tdigits[0] == 0)) {
        return copyBigBinary(B);
    }
    
    // OPTIMISATION : S'assurer que a >= b au début
    // Cela évite des échanges inutiles au début
    BigBinary a, b;
    if (Inferieur(A, B)) {
        a = copyBigBinary(B);  // a = max(A, B)
        b = copyBigBinary(A);  // b = min(A, B)
    } else {
        a = copyBigBinary(A);
        b = copyBigBinary(B);
    }
    
    // Facteur pour compter les facteurs 2 communs extraits
    // On multipliera le résultat final par ce facteur
    BigBinary facteur = creerBigBinaryDepuisChaine("1");
    
    // ========================================================================
    // ÉTAPE 1 : Extraire les facteurs 2 communs
    // ========================================================================
    // Si A et B sont tous les deux pairs, alors :
    // PGCD(A, B) = 2 × PGCD(A/2, B/2)
    // On extrait tous les facteurs 2 communs pour accélérer l'algorithme
    while (estPair(a) && estPair(b)) {
        // Diviser a et b par 2
        BigBinary a_div2 = divisionPar2(a);
        BigBinary b_div2 = divisionPar2(b);
        libereBigBinary(&a);
        libereBigBinary(&b);
        a = a_div2;
        b = b_div2;
        
        // Multiplier le facteur par 2 (on a extrait un facteur 2)
        BigBinary facteur_double = Addition(facteur, facteur);
        libereBigBinary(&facteur);
        facteur = facteur_double;
    }
    
    // ========================================================================
    // ÉTAPE 2 : Algorithme principal
    // ========================================================================
    // Maintenant, au moins un des deux nombres (a ou b) est impair
    // On continue jusqu'à ce que b = 0
    while (b.Signe != 0 && !(b.Taille == 1 && b.Tdigits[0] == 0)) {
        // Si b est pair, diviser par 2
        // PGCD(a, b) = PGCD(a, b/2) si b est pair et a impair
        while (estPair(b)) {
            BigBinary b_div2 = divisionPar2(b);
            libereBigBinary(&b);
            b = b_div2;
        }
        
        // Si a est pair, diviser par 2
        // PGCD(a, b) = PGCD(a/2, b) si a est pair et b impair
        while (estPair(a)) {
            BigBinary a_div2 = divisionPar2(a);
            libereBigBinary(&a);
            a = a_div2;
        }
        
        // Maintenant a et b sont tous les deux impairs
        // Si a >= b, alors PGCD(a, b) = PGCD((a-b)/2, b)
        // Car (a-b) est pair (différence de deux impairs)
        if (!Inferieur(a, b)) {
            // Calculer a - b
            BigBinary diff = Soustraction(a, b);
            libereBigBinary(&a);
            a = diff;
            trimLeadingZeros(&a);
            
            // Si a est devenu nul, b est le PGCD
            if (a.Signe == 0) {
                libereBigBinary(&a);
                // Le PGCD final = b × facteur
                BigBinary resultat = MultiplicationEgyptienne(b, facteur);
                libereBigBinary(&b);
                libereBigBinary(&facteur);
                return resultat;
            }
            
            // Diviser par 2 (car a et b étaient impairs, a-b est pair)
            BigBinary a_div2 = divisionPar2(a);
            libereBigBinary(&a);
            a = a_div2;
        } else {
            // Si a < b, échanger a et b
            // PGCD(a, b) = PGCD(b, a)
            BigBinary temp = a;
            a = b;
            b = temp;
        }
    }
    
    // À ce stade, b = 0, donc le PGCD est a
    // Mais il faut multiplier par le facteur des 2 extraits
    BigBinary resultat = MultiplicationEgyptienne(a, facteur);
    libereBigBinary(&a);
    libereBigBinary(&b);
    libereBigBinary(&facteur);
    
    return resultat;
}

// ============================================================================
// PHASE 2 : EXPONENTIATION MODULAIRE RAPIDE
// ============================================================================

/**
 * @brief Calcule base^exp mod mod (exponentiation modulaire rapide)
 * 
 * Utilise l'algorithme "Square and Multiply" pour calculer efficacement
 * l'exponentiation modulaire. L'exposant est de type int (limité à 64 bits).
 * 
 * Principe de l'algorithme "Square and Multiply" :
 * - On décompose l'exposant en binaire
 * - Pour chaque bit de l'exposant (de droite à gauche) :
 *   - Si le bit est 1 : multiplier le résultat par la base courante
 *   - Toujours : mettre la base au carré
 * - À chaque étape, on prend le modulo pour éviter les nombres trop grands
 * 
 * Exemple : calculer 3^13 mod 7
 * 13 = 1101 (binaire)
 * - Bit 0 (1) : résultat = 1 * 3 = 3, base = 3^2 = 9 mod 7 = 2
 * - Bit 1 (0) : résultat = 3, base = 2^2 = 4 mod 7 = 4
 * - Bit 2 (1) : résultat = 3 * 4 = 12 mod 7 = 5, base = 4^2 = 16 mod 7 = 2
 * - Bit 3 (1) : résultat = 5 * 2 = 10 mod 7 = 3, base = 2^2 = 4 mod 7 = 4
 * Résultat final : 3
 * 
 * @param base Base de l'exponentiation
 * @param exp Exposant (type int, < 64 bits)
 * @param mod Module
 * @return BigBinary contenant base^exp mod mod
 */
BigBinary BigBinary_expMod(BigBinary base, int exp, BigBinary mod) {
    // Initialiser le résultat à 1 (élément neutre de la multiplication)
    BigBinary result = creerBigBinaryDepuisChaine("1");
    BigBinary b = copyBigBinary(base);  // Copie de la base pour pouvoir la modifier

    // Algorithme "Square and Multiply" :
    // On décompose l'exposant en binaire et on traite chaque bit
    while (exp > 0) {
        // Si le bit de poids faible de l'exposant est 1, multiplier le résultat par la base
        if (exp % 2 == 1) {
            // result = (result * b) % mod
            BigBinary tmp = Multiplication(result, b);
            BigBinary resMod = BigBinary_mod(tmp, mod);
            libereBigBinary(&tmp);
            libereBigBinary(&result);
            result = resMod;
        }
        
        // Toujours mettre la base au carré pour la prochaine itération
        // b = (b * b) % mod
        BigBinary tmp2 = Multiplication(b, b);
        BigBinary baseMod = BigBinary_mod(tmp2, mod);
        libereBigBinary(&tmp2);
        libereBigBinary(&b);
        b = baseMod;
        
        // Diviser l'exposant par 2 (décalage à droite, on passe au bit suivant)
        exp /= 2;
    }

    // Libérer la mémoire
    libereBigBinary(&b);
    return result;
}

// ============================================================================
// PHASE 3 : CHIFFREMENT RSA (BONUS)
// ============================================================================

/**
 * @brief Chiffre un message avec RSA
 * 
 * Calcule C = M^e mod n où :
 * - M est le message à chiffrer (BigBinary)
 * - e est la clé publique (exposant de chiffrement, type int < 64 bits)
 * - n est le module RSA (BigBinary)
 * 
 * Principe RSA :
 * - Le message M est chiffré en calculant M^e mod n
 * - Seule la clé privée d peut déchiffrer : M = C^d mod n
 * - La sécurité repose sur la difficulté de factoriser n
 * 
 * @param message Message à chiffrer (BigBinary)
 * @param e Exposant de chiffrement public (int, < 64 bits)
 * @param n Module RSA (BigBinary)
 * @return BigBinary contenant le message chiffré
 */
BigBinary BigBinary_RSA_encrypt(BigBinary message, int e, BigBinary n) {
    // Le chiffrement RSA est simplement une exponentiation modulaire
    return BigBinary_expMod(message, e, n);
}

/**
 * @brief Calcule base^exp mod mod avec exp de type BigBinary
 * 
 * Version étendue de BigBinary_expMod où l'exposant peut être un BigBinary
 * de taille arbitraire. Utilise l'algorithme "Square and Multiply" en parcourant
 * les bits de l'exposant.
 * 
 * Cette fonction est nécessaire pour le déchiffrement RSA où l'exposant privé d
 * peut être très grand (plus de 64 bits).
 * 
 * Principe :
 * - Parcourt les bits de l'exposant (de droite à gauche, du LSB au MSB)
 * - Pour chaque bit :
 *   - Si le bit est 1 : multiplier le résultat par la base courante
 *   - Toujours : mettre la base au carré
 * - À chaque étape, prendre le modulo
 * 
 * @param base Base de l'exponentiation
 * @param exp Exposant (BigBinary, taille arbitraire)
 * @param mod Module
 * @return BigBinary contenant base^exp mod mod
 */
BigBinary BigBinary_expMod_Big(BigBinary base, BigBinary exp, BigBinary mod) {
    // Initialiser le résultat à 1 (élément neutre de la multiplication)
    BigBinary resultat = creerBigBinaryDepuisChaine("1");
    
    // Réduire la base modulo mod (au cas où base > mod)
    // Cela évite des calculs inutiles
    BigBinary b = BigBinary_mod(base, mod);

    // Parcourir les bits de l'exposant de droite à gauche (du LSB au MSB)
    // Dans notre structure, Tdigits[0] est le MSB et Tdigits[Taille-1] est le LSB
    // On parcourt donc de Taille-1 vers 0
    for (int i = exp.Taille - 1; i >= 0; i--) {
        // Si le bit actuel de l'exposant est 1, multiplier le résultat par la base courante
        if (exp.Tdigits[i] == 1) {
            // resultat = (resultat * b) % mod
            BigBinary temp_mul = Multiplication(resultat, b);
            BigBinary temp_mod = BigBinary_mod(temp_mul, mod);
            
            libereBigBinary(&resultat);
            libereBigBinary(&temp_mul);
            resultat = temp_mod;
        }
        
        // Toujours mettre la base au carré pour la prochaine itération
        // b = (b * b) % mod
        BigBinary temp_square = Multiplication(b, b);
        BigBinary base_mod = BigBinary_mod(temp_square, mod);
        
        libereBigBinary(&b);
        libereBigBinary(&temp_square);
        b = base_mod;
    }

    // Libérer la mémoire
    libereBigBinary(&b);
    return resultat;
}

/**
 * @brief Déchiffre un message chiffré avec RSA
 * 
 * Calcule M = C^d mod n où :
 * - C est le message chiffré (BigBinary)
 * - d est la clé privée (exposant de déchiffrement, BigBinary, peut être très grand)
 * - n est le module RSA (BigBinary)
 * 
 * Principe RSA :
 * - Le message chiffré C est déchiffré en calculant C^d mod n
 * - La clé privée d est calculée telle que e × d ≡ 1 (mod φ(n))
 * - Seule la clé privée d peut déchiffrer un message chiffré avec e
 * 
 * @param cipher Message chiffré (BigBinary)
 * @param d Exposant de déchiffrement privé (BigBinary, peut être très grand)
 * @param n Module RSA (BigBinary)
 * @return BigBinary contenant le message déchiffré
 */
BigBinary BigBinary_RSA_decrypt(BigBinary cipher, BigBinary d, BigBinary n) {
    // Le déchiffrement RSA est une exponentiation modulaire avec un exposant BigBinary
    return BigBinary_expMod_Big(cipher, d, n);
}
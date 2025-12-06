#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// === Structure BigBinary ===
typedef struct {
    int *Tdigits;  // tableau de bits (0 ou 1)
    int Taille;    // nombre de bits
    int Signe;     // -1, 0 ou +1
} BigBinary;

// === Création et initialisation ===
BigBinary createBigBinary(int size) {
    BigBinary bb;
    bb.Tdigits = malloc(sizeof(int) * size);
    bb.Taille = size;
    bb.Signe = 0;
    return bb;
}

BigBinary initBigBinary(int taille, int signe) {
    BigBinary nb;
    nb.Taille = taille;
    nb.Signe = signe;
    nb.Tdigits = malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; ++i) nb.Tdigits[i] = 0;
    return nb;
}

BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int n = strlen(chaine);
    nb.Taille = 0;

    for (int i = 0; i < n; ++i)
        if (chaine[i] == '0' || chaine[i] == '1') nb.Taille++;

    nb.Tdigits = malloc(sizeof(int) * nb.Taille);
    nb.Signe = +1;
    int index = 0;
    int tousZeros = 1;

    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Tdigits[index] = chaine[i] - '0';
            if (nb.Tdigits[index] == 1) tousZeros = 0;
            index++;
        }
    }

    if (tousZeros) nb.Signe = 0;
    return nb;
}

// === Copie d'un BigBinary ===
BigBinary copyBigBinary(BigBinary src) {
    BigBinary dest = initBigBinary(src.Taille, src.Signe);
    for (int i = 0; i < src.Taille; i++) dest.Tdigits[i] = src.Tdigits[i];
    return dest;
}

// === Affichage et libération ===
void afficheBigBinary(BigBinary nb) {
    if (nb.Signe == -1) printf("-");
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0\n");
        return;
    }
    for (int i = 0; i < nb.Taille; ++i) printf("%d", nb.Tdigits[i]);
    printf("\n");
}

void libereBigBinary(BigBinary *nb) {
    free(nb->Tdigits);
    nb->Tdigits = NULL;
    nb->Taille = 0;
    nb->Signe = 0;
}

// === Comparaisons ===
bool Egal(BigBinary A, BigBinary B) {
    if (A.Taille != B.Taille || A.Signe != B.Signe) return false;
    for (int i = 0; i < A.Taille; i++)
        if (A.Tdigits[i] != B.Tdigits[i]) return false;
    return true;
}

bool Inferieur(BigBinary A, BigBinary B) {
    if (A.Taille != B.Taille) return A.Taille < B.Taille;
    for (int i = 0; i < A.Taille; i++) {
        if (A.Tdigits[i] < B.Tdigits[i]) return true;
        if (A.Tdigits[i] > B.Tdigits[i]) return false;
    }
    return false;
}

// === Addition ===
BigBinary Addition(BigBinary A, BigBinary B) {
    int maxTaille = (A.Taille > B.Taille) ? A.Taille : B.Taille;
    BigBinary res = initBigBinary(maxTaille + 1, +1);

    int carry = 0;
    for (int i = res.Taille - 1, j = A.Taille - 1, k = B.Taille - 1; i >= 0; i--, j--, k--) {
        int bitA = (j >= 0) ? A.Tdigits[j] : 0;
        int bitB = (k >= 0) ? B.Tdigits[k] : 0;
        int sum = bitA + bitB + carry;
        res.Tdigits[i] = sum % 2;
        carry = sum / 2;
    }

    // Ajuster le signe si tout est zéro
    int tousZeros = 1;
    for (int i = 0; i < res.Taille; i++) if (res.Tdigits[i] == 1) tousZeros = 0;
    if (tousZeros) res.Signe = 0;

    return res;
}

// === Soustraction (A >= B) ===
BigBinary Soustraction(BigBinary A, BigBinary B) {
    BigBinary res = initBigBinary(A.Taille, +1);
    int borrow = 0;
    int offset = A.Taille - B.Taille;

    for (int i = A.Taille - 1; i >= 0; i--) {
        int bitA = A.Tdigits[i] - borrow;
        int bitB = (i - offset >= 0) ? B.Tdigits[i - offset] : 0;

        if (bitA < bitB) {
            bitA += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.Tdigits[i] = bitA - bitB;
    }

    // Vérification pour tous zéros → signe = 0
    int tousZeros = 1;
    for (int i = 0; i < res.Taille; i++) if (res.Tdigits[i] == 1) tousZeros = 0;
    if (tousZeros) res.Signe = 0;

    return res;
}


// Supprime les zéros en tête
void trimLeadingZeros(BigBinary *nb) {
    int firstOne = 0;
    while (firstOne < nb->Taille && nb->Tdigits[firstOne] == 0) firstOne++;
    if (firstOne == nb->Taille) {
        nb->Signe = 0;
        return;
    }
    if (firstOne > 0) {
        int newSize = nb->Taille - firstOne;
        for (int i = 0; i < newSize; i++) nb->Tdigits[i] = nb->Tdigits[i + firstOne];
        nb->Taille = newSize;
    }
}

// === Multiplication binaire ===
BigBinary Multiplication(BigBinary A, BigBinary B) {
    // Le résultat final commence à 0
    BigBinary resultat = creerBigBinaryDepuisChaine("0");

    // On parcourt les bits de B de droite à gauche (du bit de poids faible au plus fort)
    for (int i = B.Taille - 1; i >= 0; i--) {
        // Si le bit actuel de B est '1'
        if (B.Tdigits[i] == 1) {
            // On calcule le décalage nécessaire pour A
            int decalage = B.Taille - 1 - i;

            // On crée une version de A décalée, avec des zéros à droite
            BigBinary a_decale = initBigBinary(A.Taille + decalage, A.Signe);

            // On copie les bits de A au début du nouveau tableau
            for (int j = 0; j < A.Taille; j++) {
                a_decale.Tdigits[j] = A.Tdigits[j];
            }
            // Les zéros à la fin pour le décalage sont déjà là grâce à initBigBinary

            // On additionne ce nombre décalé au résultat cumulé
            BigBinary nouvelle_somme = Addition(resultat, a_decale);

            // On nettoie la mémoire et on met à jour le résultat
            libereBigBinary(&resultat);
            libereBigBinary(&a_decale);
            resultat = nouvelle_somme;
        }
    }

    // Gestion du signe du résultat final
    if (A.Signe == 0 || B.Signe == 0) {
        resultat.Signe = 0;
    } else {
        resultat.Signe = A.Signe * B.Signe;
    }

    trimLeadingZeros(&resultat);
    return resultat;
}
// === Modulo Optimisé (Division Euclidienne) ===
BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    // Si B est nul, c'est une erreur (division par zéro), on retourne 0 ou on gère l'erreur
    if (B.Taille == 0 || (B.Taille == 1 && B.Tdigits[0] == 0)) {
        return creerBigBinaryDepuisChaine("0");
    }

    // On commence avec un reste R = 0
    BigBinary R = creerBigBinaryDepuisChaine("0");

    // On parcourt les bits de A du poids fort (index 0) au poids faible
    for (int i = 0; i < A.Taille; i++) {
        // 1. Décalage à gauche de R (équivalent à R = R * 2)
        // On peut utiliser l'addition : R = R + R
        BigBinary R_shifted = Addition(R, R);
        libereBigBinary(&R); // On libère l'ancienne valeur
        R = R_shifted;

        // 2. On ajoute le bit actuel de A (A.Tdigits[i]) à la position la moins significative
        // Si le bit est 1, on ajoute 1. Si c'est 0, on ne fait rien.
        if (A.Tdigits[i] == 1) {
            BigBinary un = creerBigBinaryDepuisChaine("1");
            BigBinary R_plus_1 = Addition(R, un);
            libereBigBinary(&R);
            libereBigBinary(&un);
            R = R_plus_1;
        }

        // 3. Si R >= B, alors R = R - B
        // Note: !Inferieur(R, B) équivaut à R >= B
        if (!Inferieur(R, B)) {
            BigBinary tmp = Soustraction(R, B);
            libereBigBinary(&R);
            R = tmp;
            trimLeadingZeros(&R); // Important pour garder la taille correcte
        }
    }
    return R;
}

// === PGCD binaire ===
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    BigBinary a = copyBigBinary(A);
    BigBinary b = copyBigBinary(B);

    while (!(b.Signe == 0)) {
        BigBinary R = BigBinary_mod(a, b);
        libereBigBinary(&a);
        a = b;
        b = R;
    }

    libereBigBinary(&b);
    return a;
}

// === Exponentiation modulaire rapide ===
BigBinary BigBinary_expMod(BigBinary base, int exp, BigBinary mod) {
    BigBinary result = creerBigBinaryDepuisChaine("1");
    BigBinary b = copyBigBinary(base);

    while (exp > 0) {
        if (exp % 2 == 1) {
            BigBinary tmp = Multiplication(result, b);
            BigBinary resMod = BigBinary_mod(tmp, mod);
            libereBigBinary(&tmp);
            libereBigBinary(&result);
            result = resMod;
        }
        BigBinary tmp2 = Multiplication(b, b);
        BigBinary baseMod = BigBinary_mod(tmp2, mod);
        libereBigBinary(&tmp2);
        libereBigBinary(&b);
        b = baseMod;
        exp /= 2;
    }

    libereBigBinary(&b);
    return result;
}

BigBinary BigBinary_RSA_encrypt(BigBinary message, int e, BigBinary n) {
    // On utilise directement la fonction d'exponentiation modulaire existante.
    return BigBinary_expMod(message, e, n);
}

// === Exponentiation Modulaire Rapide (BigInt) ===
// Algorithme "Square and Multiply"
BigBinary BigBinary_expMod_Big(BigBinary base, BigBinary exp, BigBinary mod) {
    BigBinary resultat = creerBigBinaryDepuisChaine("1");
    BigBinary b = BigBinary_mod(base, mod); // Au cas où base > mod

    // On parcourt les bits de l'exposant (ici on suppose BigEndian : Tdigits[0] est MSB)
    // Pour l'algo classique gauche-droite :
    // On part du bit de poids fort vers le faible.
    
    // ATTENTION : L'implémentation ci-dessous parcourt de la droite (LSB) vers la gauche (MSB)
    // car c'est plus simple avec la structure actuelle si on ne veut pas gérer les index compliqués.
    // Index: A.Taille-1 est le LSB (dernier bit du tableau).
    
    for (int i = exp.Taille - 1; i >= 0; i--) {
        if (exp.Tdigits[i] == 1) {
            // resultat = (resultat * b) % mod
            BigBinary temp_mul = Multiplication(resultat, b);
            BigBinary temp_mod = BigBinary_mod(temp_mul, mod);
            
            libereBigBinary(&resultat);
            libereBigBinary(&temp_mul);
            resultat = temp_mod;
        }
        
        // b = (b * b) % mod
        BigBinary temp_square = Multiplication(b, b);
        BigBinary base_mod = BigBinary_mod(temp_square, mod);
        
        libereBigBinary(&b);
        libereBigBinary(&temp_square);
        b = base_mod;
    }

    libereBigBinary(&b);
    return resultat;
}

BigBinary BigBinary_RSA_decrypt(BigBinary cipher, BigBinary d, BigBinary n) {
    return BigBinary_expMod_Big(cipher, d, n);
}
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

// === Multiplication binaire ===
BigBinary Multiplication(BigBinary A, BigBinary B) {
    BigBinary res = creerBigBinaryDepuisChaine("0");
    for (int i = B.Taille - 1; i >= 0; i--) {
        if (B.Tdigits[i] == 1) {
            BigBinary tmp = initBigBinary(res.Taille + (B.Taille - i), +1);
            for (int j = 0; j < res.Taille; j++)
                tmp.Tdigits[j + (B.Taille - i - 1)] = res.Tdigits[j];
            BigBinary sum = Addition(tmp, A);
            libereBigBinary(&res);
            libereBigBinary(&tmp);
            res = sum;
        }
    }
    return res;
}

// === Modulo ===

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

// Modulo binaire sécurisé
BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    BigBinary R = copyBigBinary(A);

    while (!Inferieur(R, B) && R.Signe != 0) {
        BigBinary tmp = Soustraction(R, B);
        libereBigBinary(&R);
        R = tmp;
        trimLeadingZeros(&R);
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

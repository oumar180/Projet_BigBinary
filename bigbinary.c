#include "bigbinary.h"

// Création d’un BigBinary vide
BigBinary createBigBinary(int size) {
    BigBinary bb;
    bb.Tdigits = malloc(sizeof(int) * size);
    bb.Taille = size;
    bb.Signe = 0; // nul par défaut
    return bb;
}

// Initialisation d’un BigBinary (tout à 0)
BigBinary initBigBinary(int taille, int signe) {
    BigBinary nb;
    nb.Taille = taille;
    nb.Signe = signe;
    nb.Tdigits = malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; ++i) nb.Tdigits[i] = 0;
    return nb;
}

// Affichage
void afficheBigBinary(BigBinary nb) {
    if (nb.Signe == -1) printf("-");
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0\n");
        return;
    }
    for (int i = 0; i < nb.Taille; ++i) printf("%d", nb.Tdigits[i]);
    printf("\n");
}

// Libération mémoire
void libereBigBinary(BigBinary *nb) {
    free(nb->Tdigits);
    nb->Tdigits = NULL;
    nb->Taille = 0;
    nb->Signe = 0;
}

// Création depuis une chaîne binaire
BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int n = strlen(chaine);
    nb.Taille = 0;

    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') nb.Taille++;
    }

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

// === Comparaisons ===
bool Egal(BigBinary A, BigBinary B) {
    if (A.Taille != B.Taille || A.Signe != B.Signe) return false;
    for (int i = 0; i < A.Taille; i++) {
        if (A.Tdigits[i] != B.Tdigits[i]) return false;
    }
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
    for (int i = res.Taille-1, j = A.Taille-1, k = B.Taille-1; i >= 0; i--, j--, k--) {
        int bitA = (j >= 0) ? A.Tdigits[j] : 0;
        int bitB = (k >= 0) ? B.Tdigits[k] : 0;
        int sum = bitA + bitB + carry;
        res.Tdigits[i] = sum % 2;
        carry = sum / 2;
    }
    return res;
}

// === Soustraction (A >= B) ===
BigBinary Soustraction(BigBinary A, BigBinary B) {
    BigBinary res = initBigBinary(A.Taille, +1);
    int borrow = 0;
    for (int i = A.Taille-1, j = B.Taille-1; i >= 0; i--, j--) {
        int bitA = A.Tdigits[i] - borrow;
        int bitB = (j >= 0) ? B.Tdigits[j] : 0;
        if (bitA < bitB) {
            bitA += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.Tdigits[i] = bitA - bitB;
    }
    return res;
}

// === PGCD binaire simplifié ===
BigBinary PGCD(BigBinary A, BigBinary B) {
    while (!(B.Signe == 0)) {
        while (Inferieur(B, A)) A = Soustraction(A, B);
        while (Inferieur(A, B)) B = Soustraction(B, A);
        if (Egal(A, B)) return A;
    }
    return A;
}

// === Modulo ===
BigBinary Modulo(BigBinary A, BigBinary B) {
    while (Inferieur(B, A) || Egal(A, B)) {
        A = Soustraction(A, B);
    }
    return A;
}

// === Exponentiation modulaire rapide ===
BigBinary expMod(BigBinary base, int exp, BigBinary mod) {
    BigBinary result = creerBigBinaryDepuisChaine("1");
    while (exp > 0) {
        if (exp % 2 == 1) result = Modulo(Addition(result, base), mod);
        base = Modulo(Addition(base, base), mod);
        exp /= 2;
    }
    return result;
}

// === RSA ===
BigBinary RSA_encrypt(BigBinary message, int e, BigBinary n) {
    return expMod(message, e, n);
}

BigBinary RSA_decrypt(BigBinary cipher, int d, BigBinary n) {
    return expMod(cipher, d, n);
}

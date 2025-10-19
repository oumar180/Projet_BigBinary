#ifndef BIGBINARY_H
#define BIGBINARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int *Tdigits;
    int Taille;
    int Signe; // 0 = nul, +1 = positif, -1 = négatif
} BigBinary;

// Création et gestion
BigBinary createBigBinary(int size);
BigBinary initBigBinary(int taille, int signe);
BigBinary creerBigBinaryDepuisChaine(const char *chaine);
void afficheBigBinary(BigBinary nb);
void libereBigBinary(BigBinary *nb);

// Comparaisons
bool Egal(BigBinary A, BigBinary B);
bool Inferieur(BigBinary A, BigBinary B);

// Opérations de base
BigBinary Addition(BigBinary A, BigBinary B);
BigBinary Soustraction(BigBinary A, BigBinary B);
BigBinary Multiplication(BigBinary A, BigBinary B);

// Phase 2
BigBinary BigBinary_mod(BigBinary A, BigBinary B);
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B);
BigBinary BigBinary_expMod(BigBinary base, int exp, BigBinary mod);

#endif

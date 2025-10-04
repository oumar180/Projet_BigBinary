#ifndef BIGBINARY_H
#define BIGBINARY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BASE 2

// Définition de la structure
typedef struct {
    int *Tdigits;  // Tableau de bits (MSB à gauche, LSB à droite)
    int Taille;    // Nombre de bits
    int Signe;     // +1 pour positif, -1 pour négatif, 0 pour nul
} BigBinary;

// Fonctions de base
BigBinary createBigBinary(int size);
BigBinary initBigBinary(int taille, int signe);
void afficheBigBinary(BigBinary nb);
void libereBigBinary(BigBinary *nb);
BigBinary creerBigBinaryDepuisChaine(const char *chaine);

// Comparaisons
bool Egal(BigBinary A, BigBinary B);
bool Inferieur(BigBinary A, BigBinary B);

// Opérations
BigBinary Addition(BigBinary A, BigBinary B);
BigBinary Soustraction(BigBinary A, BigBinary B);

// Avancées
BigBinary PGCD(BigBinary A, BigBinary B);
BigBinary Modulo(BigBinary A, BigBinary B);
BigBinary expMod(BigBinary base, int exp, BigBinary mod);

// RSA
BigBinary RSA_encrypt(BigBinary message, int e, BigBinary n);
BigBinary RSA_decrypt(BigBinary cipher, int d, BigBinary n);

#endif

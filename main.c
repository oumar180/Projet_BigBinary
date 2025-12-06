/**
 * @file main.c
 * @brief Programme de test pour la bibliothèque BigBinary
 * 
 * Ce programme teste toutes les fonctionnalités implémentées :
 * - Phase 1 : Opérations arithmétiques de base
 * - Phase 2 : Fonctions avancées (modulo, PGCD, exponentiation modulaire)
 * - Phase 3 : Chiffrement RSA simplifié
 */

#include "bigbinary.h"

/**
 * @brief Fonction principale de test
 * 
 * Cette fonction teste toutes les opérations de la bibliothèque BigBinary
 * avec des exemples concrets pour vérifier le bon fonctionnement.
 * 
 * @return 0 si tout s'est bien passé
 */
int main() {
    // ========================================================================
    // PHASE 1 : OPÉRATIONS BINAIRES DE BASE
    // ========================================================================
    printf("=== PHASE 1 : Operations binaires de base ===\n\n");

    // Test avec des nombres plus petits pour voir les résultats clairement
    // A = 10101010 (binaire) = 170 (décimal)
    // B = 11001100 (binaire) = 204 (décimal)
    BigBinary A = creerBigBinaryDepuisChaine("10101010");
    BigBinary B = creerBigBinaryDepuisChaine("11001100");

    // Afficher les nombres de test
    printf("A = "); afficheBigBinary(A);
    printf("B = "); afficheBigBinary(B);
    printf("\n");

    // ------------------------------------------------------------------------
    // Test des fonctions de comparaison
    // ------------------------------------------------------------------------
    printf("--- Comparaisons ---\n");
    printf("A == B ? %s\n", Egal(A, B) ? "Oui" : "Non");
    printf("A < B ? %s\n", Inferieur(A, B) ? "Oui" : "Non");
    printf("A > B ? %s\n", Inferieur(B, A) ? "Oui" : "Non");
    printf("\n");

    // ------------------------------------------------------------------------
    // Test de l'addition binaire
    // ------------------------------------------------------------------------
    printf("--- Addition ---\n");
    BigBinary sum = Addition(A, B);
    printf("A + B = "); afficheBigBinary(sum);
    libereBigBinary(&sum);  // Libérer la mémoire
    printf("\n");

    // ------------------------------------------------------------------------
    // Test de la soustraction binaire
    // ------------------------------------------------------------------------
    printf("--- Soustraction ---\n");
    BigBinary diff = Soustraction(A, B);
    printf("A - B = "); afficheBigBinary(diff);
    libereBigBinary(&diff);
    
    // Test dans l'autre sens
    BigBinary diff2 = Soustraction(B, A);
    printf("B - A = "); afficheBigBinary(diff2);
    libereBigBinary(&diff2);
    printf("\n");

    // ------------------------------------------------------------------------
    // Test de la multiplication classique (shift-and-add)
    // ------------------------------------------------------------------------
    printf("--- Multiplication (classique) ---\n");
    BigBinary prod = Multiplication(A, B);
    printf("A * B = "); afficheBigBinary(prod);
    libereBigBinary(&prod);
    printf("\n");

    // ------------------------------------------------------------------------
    // Test de la multiplication égyptienne (Phase 2)
    // ------------------------------------------------------------------------
    printf("--- Multiplication Égyptienne ---\n");
    BigBinary prod_egypt = MultiplicationEgyptienne(A, B);
    printf("A * B (Égyptienne) = "); afficheBigBinary(prod_egypt);
    libereBigBinary(&prod_egypt);
    printf("\n");

    // ========================================================================
    // PHASE 2 : PGCD ET MODULO
    // ========================================================================
    printf("=== PHASE 2 : PGCD et Modulo ===\n\n");

    // ------------------------------------------------------------------------
    // Test du modulo avec l'algorithme "Division-free mod"
    // ------------------------------------------------------------------------
    printf("--- Modulo (Division-free mod) ---\n");
    BigBinary R = BigBinary_mod(A, B);
    printf("A %% B = "); afficheBigBinary(R);
    libereBigBinary(&R);
    
    // Test dans l'autre sens
    BigBinary R2 = BigBinary_mod(B, A);
    printf("B %% A = "); afficheBigBinary(R2);
    libereBigBinary(&R2);
    printf("\n");

    // ------------------------------------------------------------------------
    // Test du PGCD avec l'algorithme binaire d'Euclide
    // ------------------------------------------------------------------------
    printf("--- PGCD (Algorithme Binaire d'Euclide) ---\n");
    BigBinary G = BigBinary_PGCD(A, B);
    printf("PGCD(A,B) = "); afficheBigBinary(G);
    libereBigBinary(&G);
    printf("\n");

    // ------------------------------------------------------------------------
    // Test avec des grands nombres (pour tester les performances)
    // ------------------------------------------------------------------------
    printf("=== TEST AVEC GRANDS NOMBRES ===\n\n");
    // Nombres binaires de ~80 bits pour tester les algorithmes sur de grands entiers
    BigBinary A_grand = creerBigBinaryDepuisChaine("10101010101001110011101000111110100001011101001000101100011010110000111000000110100011101001");
    BigBinary B_grand = creerBigBinaryDepuisChaine("11001011011111111000110000111010000000110101011000000100000010110101101001100011110001011000");
    
    printf("A (grand) = "); afficheBigBinary(A_grand);
    printf("B (grand) = "); afficheBigBinary(B_grand);
    printf("\n");
    
    // Test du modulo avec grands nombres
    BigBinary R_grand = BigBinary_mod(A_grand, B_grand);
    printf("A %% B (grand) = "); afficheBigBinary(R_grand);
    libereBigBinary(&R_grand);
    
    // Test du PGCD avec grands nombres (peut prendre du temps)
    printf("Calcul du PGCD en cours...\n");
    BigBinary G_grand = BigBinary_PGCD(A_grand, B_grand);
    printf("PGCD(A,B) (grand) = "); afficheBigBinary(G_grand);
    libereBigBinary(&G_grand);
    printf("\n");

    // Libérer la mémoire des grands nombres
    libereBigBinary(&A);
    libereBigBinary(&B);
    libereBigBinary(&A_grand);
    libereBigBinary(&B_grand);

    // ========================================================================
    // PHASE 3 : CHIFFREMENT RSA SIMPLIFIÉ (BONUS)
    // ========================================================================
    printf("\n=== PHASE 3 : RSA Simplifier ===\n");

    // ------------------------------------------------------------------------
    // Définition des clés RSA et du message
    // ------------------------------------------------------------------------
    // Exemple RSA simplifié :
    // - n = 3233 (110010100001 en binaire) : module RSA (produit de deux nombres premiers)
    // - e = 17 : exposant de chiffrement public
    // - d = 2753 (101011000001 en binaire) : exposant de déchiffrement privé
    // - message = 82 (1010010 en binaire) : message à chiffrer
    BigBinary n = creerBigBinaryDepuisChaine("110010100001");  // n = 3233
    int e = 17;  // Exposant public (type int, < 64 bits)
    BigBinary d = creerBigBinaryDepuisChaine("101011000001");  // d = 2753
    BigBinary message = creerBigBinaryDepuisChaine("1010010");  // M = 82

    // Afficher les paramètres RSA
    printf("Message original : ");
    afficheBigBinary(message);
    printf("n = "); afficheBigBinary(n);
    printf("e = %d\n", e);
    printf("d = "); afficheBigBinary(d);

    // ------------------------------------------------------------------------
    // Chiffrement RSA : C = M^e mod n
    // ------------------------------------------------------------------------
    BigBinary chiffre = BigBinary_RSA_encrypt(message, e, n);
    printf("\nMessage chiffrer : ");
    afficheBigBinary(chiffre);

    // ------------------------------------------------------------------------
    // Déchiffrement RSA : M = C^d mod n
    // ------------------------------------------------------------------------
    BigBinary dechiffre = BigBinary_RSA_decrypt(chiffre, d, n);
    printf("Message dechiffrer : ");
    afficheBigBinary(dechiffre);
    
    // Vérification : le message déchiffré doit être égal au message original
    if (Egal(message, dechiffre)) {
        printf("✓ RSA fonctionne correctement : message déchiffré = message original\n");
    } else {
        printf("✗ ERREUR : Le message déchiffré ne correspond pas au message original\n");
    }
    
    // ------------------------------------------------------------------------
    // Libération de toute la mémoire allouée
    // ------------------------------------------------------------------------
    libereBigBinary(&n);
    libereBigBinary(&d);
    libereBigBinary(&message);
    libereBigBinary(&chiffre);
    libereBigBinary(&dechiffre);
    
    return 0;
}

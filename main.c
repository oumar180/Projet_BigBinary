#include "bigbinary.h"

int main() {
    printf("=== PHASE 1 : Operations binaires de base ===\n");

    BigBinary A = creerBigBinaryDepuisChaine("1011"); // 11
    BigBinary B = creerBigBinaryDepuisChaine("110");  // 6

    printf("A = "); afficheBigBinary(A);
    printf("B = "); afficheBigBinary(B);

    BigBinary sum = Addition(A, B);
    printf("A + B = "); afficheBigBinary(sum);

    BigBinary diff = Soustraction(A, B);
    printf("A - B = "); afficheBigBinary(diff);

    BigBinary prod = Multiplication(A, B);
    printf("A * B = "); afficheBigBinary(prod);

    libereBigBinary(&sum);
    libereBigBinary(&diff);
    libereBigBinary(&prod);

    printf("\n=== PHASE 2 : PGCD et Modulo ===\n");

    BigBinary R = BigBinary_mod(A, B);
    printf("A %% B = "); afficheBigBinary(R);

    BigBinary G = BigBinary_PGCD(A, B);
    printf("PGCD(A,B) = "); afficheBigBinary(G);

    libereBigBinary(&A);
    libereBigBinary(&B);
    libereBigBinary(&R);
    libereBigBinary(&G);

    printf("\n=== PHASE 3 : RSA Simplifier ===\n");

    // Définition des clés RSA et du message
    BigBinary n = creerBigBinaryDepuisChaine("110010100001"); // n = 3233
    int e = 17;
    BigBinary d = creerBigBinaryDepuisChaine("101011000001"); // d = 2753
    BigBinary message = creerBigBinaryDepuisChaine("1010010");   // M = 82

    printf("Message original : ");
    afficheBigBinary(message);
    printf("n = "); afficheBigBinary(n);
    printf("e = %d\n", e);
    printf("d = "); afficheBigBinary(d);

    // Chiffrement du message
    BigBinary chiffre = BigBinary_RSA_encrypt(message, e, n);
    printf("\nMessage chiffrer : ");
    afficheBigBinary(chiffre);

    // Déchiffrement du message
    BigBinary dechiffre = BigBinary_RSA_decrypt(chiffre, d, n);
    printf("Message dechiffrer : ");
    afficheBigBinary(dechiffre);
    
    // Libération de la mémoire
    libereBigBinary(&n);
    libereBigBinary(&d);
    libereBigBinary(&message);
    libereBigBinary(&chiffre);
    libereBigBinary(&dechiffre);
    return 0;
}

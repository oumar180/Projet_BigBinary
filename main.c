#include "bigbinary.h"

int main() {
    // === Phase 1 : Test affichage et opérations de base ===
    BigBinary A = creerBigBinaryDepuisChaine("1011"); // 11
    BigBinary B = creerBigBinaryDepuisChaine("110");  // 6

    printf("A = "); afficheBigBinary(A);
    printf("B = "); afficheBigBinary(B);

    BigBinary C = Addition(A, B);
    printf("A + B = "); afficheBigBinary(C);

    BigBinary D = Soustraction(A, B);
    printf("A - B = "); afficheBigBinary(D);

    // === Phase 2 : Test PGCD et modulo ===
    BigBinary G = PGCD(A, B);
    printf("PGCD(A,B) = "); afficheBigBinary(G);

    BigBinary M = Modulo(A, B);
    printf("A mod B = "); afficheBigBinary(M);

    // === Phase 3 : Test RSA simplifié ===
    int e = 3; // exposant public
    int d = 7; // exposant privé
    BigBinary n = creerBigBinaryDepuisChaine("10111"); // petit n = 23

    BigBinary msg = creerBigBinaryDepuisChaine("101"); // message = 5
    BigBinary cipher = RSA_encrypt(msg, e, n);
    printf("Message chiffre = "); afficheBigBinary(cipher);

    BigBinary clear = RSA_decrypt(cipher, d, n);
    printf("Message dechiffre = "); afficheBigBinary(clear);

    // Libération mémoire
    libereBigBinary(&A);
    libereBigBinary(&B);
    libereBigBinary(&C);
    libereBigBinary(&D);
    libereBigBinary(&G);
    libereBigBinary(&M);
    libereBigBinary(&n);
    libereBigBinary(&msg);
    libereBigBinary(&cipher);
    libereBigBinary(&clear);

    return 0;
}

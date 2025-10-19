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

    return 0;
}

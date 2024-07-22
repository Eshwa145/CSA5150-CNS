#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int power(int a, unsigned int b, int c) {
    int result = 1;
    a = a % c;
    while (b > 0) {
        if (b & 1)
            result = (result * a) % c;
        a = (a * a) % c;
        if (b % 2 == 0)
            b = b >> 1;
        else
            b--;
    }
    return result;
}
void generate_key_pairs(int p, int q, int *e, int *d, int *n) {
    *n = p * q;
    int totient = (p - 1) * (q - 1);
    *e = 2;
    while (gcd(*e, totient) != 1) {
        (*e)++;
    }
    *d = 0;
    while (((*d) * (*e) % totient) != 1) {
        (*d)++;
    }
}
int encrypt(int plaintext, int e, int n) {
    return power(plaintext, e, n);
} 
int decrypt(int ciphertext, int d, int n) {
    return power(ciphertext, d, n);
}
int main() {
    int p, q, e, d, n;
    long long plaintext, ciphertext, decrypted_text;
    printf("Enter prime number p: ");
    scanf("%d", &p);
    printf("Enter prime number q: ");
    scanf("%d", &q);
    generate_key_pairs(p, q, &e, &d, &n);
    printf("Enter plaintext: ");
    scanf("%lld", &plaintext);
    ciphertext = encrypt(plaintext, e, n);
    printf("Ciphertext: %lld\n", ciphertext);
    decrypted_text = decrypt(ciphertext, d, n);
    printf("Decrypted Text: %lld\n", decrypted_text);
    return 0;
}
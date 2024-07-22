#include <stdio.h>
#include <math.h>
long long int power(long long int base, long long int exp, long long int mod) {
    if (exp == 0)
        return 1;
    else if (exp % 2 == 0)
        return power((base * base) % mod, exp / 2, mod);
    else
        return (base * power(base, exp - 1, mod)) % mod;
}
long long int getSharedKey(long long int base, long long int private_key, long long int prime) {
    return power(base, private_key, prime);
}
int main() {
    long long int prime, base, alice_private, bob_private, alice_public, bob_public;
    printf("Enter the prime number (shared prime modulus): ");
    scanf("%lld", &prime);
    printf("Enter the base (primitive root modulo prime): ");
    scanf("%lld", &base);
    printf("Enter Alice's private key: ");
    scanf("%lld", &alice_private);
    printf("Enter Bob's private key: ");
    scanf("%lld", &bob_private);
    alice_public = power(base, alice_private, prime);
    bob_public = power(base, bob_private, prime);
    long long int alice_shared_key = getSharedKey(bob_public, alice_private, prime);
    long long int bob_shared_key = getSharedKey(alice_public, bob_private, prime);
    printf("\nShared secret key for Alice: %lld\n", alice_shared_key);
    printf("Shared secret key for Bob: %lld\n", bob_shared_key);
    return 0;
}
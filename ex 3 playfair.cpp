#include <stdio.h>
#include <math.h>
unsigned long long factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}
int main() {
    int n = 25;
    unsigned long long fact = factorial(n);
    double log2_fact = log2(fact);
    printf("Factorial of %d is approximately %.2e\n", n, (double)fact);
    printf("Approximate power of 2: 2^%.2f\n", log2_fact);
    double unique_keys = log2_fact - log2(100);
    printf("Effectively unique keys: 2^%.2f\n", unique_keys);
    return 0;
}

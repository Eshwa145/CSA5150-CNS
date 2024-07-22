#include <stdio.h>
void encrypt(char *plaintext, int key) {
    while (*plaintext != '\0') {
        if (*plaintext >= 'A' && *plaintext <= 'Z')
            *plaintext = ((*plaintext - 'A' + key) % 26) + 'A';
        else if (*plaintext >= 'a' && *plaintext <= 'z')
            *plaintext = ((*plaintext - 'a' + key) % 26) + 'a';
        plaintext++;
    }
}
int main() {
    char plaintext[100];
    int key;
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the encryption key: ");
    scanf("%d", &key);
    encrypt(plaintext, key);
    printf("Encrypted text: %s\n", plaintext);
    return 0;
}
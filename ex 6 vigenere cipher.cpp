#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TEXT_LENGTH 1000

// Function to encrypt the plaintext using the one-time pad Vigenère cipher
void encrypt(char plaintext[], int key[], int key_length) {
    int i;
    for (i = 0; plaintext[i] != '\0'; ++i) {
        // Determine the current key value (wrap around if necessary)
        int current_key = key[i % key_length];
        
        // Encrypt uppercase letters (A-Z)
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = ((plaintext[i] - 'A' + current_key) % 26) + 'A';
        }
        // Encrypt lowercase letters (a-z)
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = ((plaintext[i] - 'a' + current_key) % 26) + 'a';
        }
        // Ignore non-alphabet characters
    }
}

int main() {
    char plaintext[MAX_TEXT_LENGTH];
    int key[MAX_TEXT_LENGTH]; // key as an array of integers
    int key_length = 0;
    int i;

    // Seed for random number generation
    srand(time(NULL));

    // Input plaintext
    printf("Enter plaintext: ");
    fgets(plaintext, MAX_TEXT_LENGTH, stdin);

    // Generate random key values (between 0 and 26)
    for (i = 0; plaintext[i] != '\0'; ++i) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            key[key_length++] = rand() % 26;
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            key[key_length++] = rand() % 26;
        }
        // Ignore non-alphabet characters
    }

    // Encrypt the plaintext using the generated key
    encrypt(plaintext, key, key_length);

    // Output the encrypted text
    printf("\nEncrypted text: %s\n", plaintext);

    return 0;
}
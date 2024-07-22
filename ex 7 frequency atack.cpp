#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHER_LENGTH 1000

// Function to count occurrences of each letter in the ciphertext
void count_letter_frequencies(const char *ciphertext, int *freq) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            freq[index]++;
        }
    }
}

// Function to perform frequency analysis and attempt to decrypt the ciphertext
void frequency_attack(const char *ciphertext, int top_results) {
    int freq[ALPHABET_SIZE] = {0};
    count_letter_frequencies(ciphertext, freq);

    // Find the most frequent letter in the ciphertext (assumed to be 'e')
    int max_freq = 0;
    int max_index = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_index = i;
        }
    }

    // Calculate the shift amount assuming the most frequent letter in English is 'e'
    int shift = (max_index + ALPHABET_SIZE - ('e' - 'a')) % ALPHABET_SIZE;

    // Decrypt the ciphertext using the calculated shift
    printf("\nDecrypted messages (top %d possibilities):\n", top_results);
    for (int count = 0; count < top_results; ++count) {
        printf("Possibility %d: ", count + 1);
        for (int i = 0; ciphertext[i] != '\0'; ++i) {
            if (isalpha(ciphertext[i])) {
                char decrypted_char = ciphertext[i] - shift;
                if (islower(ciphertext[i]) && decrypted_char < 'a') {
                    decrypted_char += ALPHABET_SIZE;
                } else if (isupper(ciphertext[i]) && decrypted_char < 'A') {
                    decrypted_char += ALPHABET_SIZE;
                }
                printf("%c", decrypted_char);
            } else {
                printf("%c", ciphertext[i]);
            }
        }
        printf("\n");
        // Prepare for the next possibility by shifting
        shift = (shift + 1) % ALPHABET_SIZE;
    }
}

int main() {
    char ciphertext[MAX_CIPHER_LENGTH];
    int top_results;

    // Input ciphertext
    printf("Enter ciphertext: ");
    fgets(ciphertext, MAX_CIPHER_LENGTH, stdin);

    // Remove trailing newline character if present
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    // Input number of top possible plaintexts to display
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_results);

    // Perform frequency analysis and decryption
    frequency_attack(ciphertext, top_results);

    return 0;
}

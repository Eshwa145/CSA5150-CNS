#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a message using Hill cipher with a 2x2 key matrix
void hillCipherEncrypt(char *message, int key[2][2]) {
    int len = strlen(message);
    int i, j;

    // Convert message to uppercase (assuming we work with uppercase letters)
    for (i = 0; i < len; ++i) {
        message[i] = toupper(message[i]);
    }

    // Remove non-alphabetic characters
    int index = 0;
    for (i = 0; i < len; ++i) {
        if (isalpha(message[i])) {
            message[index++] = message[i];
        }
    }
    message[index] = '\0';
    len = index;

    // Pad message with 'X' if length is odd
    if (len % 2 != 0) {
        message[len++] = 'X';
        message[len] = '\0';
    }

    // Encrypt the message using the key matrix
    for (i = 0; i < len; i += 2) {
        int num1 = message[i] - 'A';
        int num2 = message[i + 1] - 'A';

        // Calculate encrypted values
        int enc1 = (key[0][0] * num1 + key[0][1] * num2) % 26;
        int enc2 = (key[1][0] * num1 + key[1][1] * num2) % 26;

        // Convert back to letters
        message[i] = enc1 + 'A';
        message[i + 1] = enc2 + 'A';
    }
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight o clock";
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    // Encrypt the message
    hillCipherEncrypt(message, key);

    // Print the encrypted message
    printf("Encrypted message: %s\n", message);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encryptVigenere(char message[], char key[]) {
    int messageLength = strlen(message);
    int keyLength = strlen(key);
    char encryptedMessage[messageLength];
    for (int i = 0, j = 0; i < messageLength; ++i) {
        char currentChar = message[i];
        if (isalpha(currentChar)) {
            char caseModifier = isupper(currentChar) ? 'A' : 'a';
            encryptedMessage[i] = (currentChar + key[j] - 2 * caseModifier) % 26 + caseModifier;
            j = (j + 1) % keyLength;
        } else {
            encryptedMessage[i] = currentChar;
        }
    }
    encryptedMessage[messageLength] = '\0';
    printf("Encrypted Message: %s\n", encryptedMessage);
}
int main() {
    char message[100];
    char key[100];
    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    message[strcspn(message, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    encryptVigenere(message, key);

    return 0;
}
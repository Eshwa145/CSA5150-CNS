

#include <stdio.h>
#include <string.h>

// 3DES encryption function
void encrypt3DESCBC(unsigned char *input, unsigned char *output, int input_length, unsigned char *key, unsigned char *iv) {
    // Define 3DES keys
    unsigned char key1[8], key2[8], key3[8];
    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);

    // Define IV schedule
    unsigned char iv_schedule[8];
    memcpy(iv_schedule, iv, 8);

    // Perform 3DES encryption
    for (int i = 0; i < input_length; i += 8) {
        // First DES encryption
        unsigned char temp[8];
        for (int j = 0; j < 8; j++) {
            temp[j] = input[i + j] ^ iv_schedule[j];
        }
        for (int j = 0; j < 8; j++) {
            temp[j] = ((key1[j / 2] >> ((j % 2) * 4)) & 0xF) ^ temp[j];
        }
        for (int j = 0; j < 8; j++) {
            output[i + j] = temp[j] ^ iv_schedule[j];
        }

        // Second DES decryption
        for (int j = 0; j < 8; j++) {
            temp[j] = output[i + j] ^ iv_schedule[j];
        }
        for (int j = 0; j < 8; j++) {
            temp[j] = ((key2[j / 2] >> ((j % 2) * 4)) & 0xF) ^ temp[j];
        }
        for (int j = 0; j < 8; j++) {
            output[i + j] = temp[j] ^ iv_schedule[j];
        }

        // Third DES encryption
        for (int j = 0; j < 8; j++) {
            temp[j] = output[i + j] ^ iv_schedule[j];
        }
        for (int j = 0; j < 8; j++) {
            temp[j] = ((key3[j / 2] >> ((j % 2) * 4)) & 0xF) ^ temp[j];
        }
        for (int j = 0; j < 8; j++) {
            output[i + j] = temp[j] ^ iv_schedule[j];
        }
    }
}

int main() {
    unsigned char plaintext[64];
    unsigned char ciphertext[64];
    int input_length;

    printf("Enter plaintext: ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    input_length = strlen((char *)plaintext);
    if (plaintext[input_length - 1] == '\n') {
        plaintext[input_length - 1] = '\0';
        input_length--;
    }

    unsigned char key[25] = "MYSECRETKEY12345678901234";
    unsigned char iv[9] = "INITVEC";

    encrypt3DESCBC(plaintext, ciphertext, input_length, key, iv);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < input_length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}


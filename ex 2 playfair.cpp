#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find the position of a character in the Playfair matrix
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Handling 'J' as 'I'
    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (matrix[*row][*col] == ch) {
                return;
            }
        }
    }
}

// Function to encrypt a message using the Playfair cipher
void encryptMessage(char matrix[5][5], char* message) {
    int len = strlen(message);
    
    // Remove spaces and punctuation from message and convert to uppercase
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            message[index++] = toupper(message[i]);
        }
    }
    message[index] = '\0';
    len = index;

    // Handle pairs of characters and encrypt
    for (int i = 0; i < len; i += 2) {
        char first = message[i];
        char second = (i + 1 < len) ? message[i + 1] : 'X'; // Use 'X' if message length is odd
        
        // If both letters are the same, insert filler character 'X'
        if (first == second) {
            second = 'X';
            i--; // Process the same pair again
            len++; // Adjust length since we added 'X'
        }
        
        int row1, col1, row2, col2;
        findPosition(matrix, first, &row1, &col1);
        findPosition(matrix, second, &row2, &col2);

        char encryptedFirst, encryptedSecond;
        // Same row
        if (row1 == row2) {
            encryptedFirst = matrix[row1][(col1 + 1) % 5];
            encryptedSecond = matrix[row2][(col2 + 1) % 5];
        }
        // Same column
        else if (col1 == col2) {
            encryptedFirst = matrix[(row1 + 1) % 5][col1];
            encryptedSecond = matrix[(row2 + 1) % 5][col2];
        }
        // Forming a rectangle
        else {
            encryptedFirst = matrix[row1][col2];
            encryptedSecond = matrix[row2][col1];
        }

        // Print encrypted digraph
        printf("%c%c", encryptedFirst, encryptedSecond);
    }
}

int main() {
    // Define the Playfair matrix
    char playfairMatrix[5][5] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'K', 'U', 'N', 'O', 'P'},
        {'O', 'Z', 'V', 'W', 'X'},
        {'Y', 'E', 'L', 'A', 'R'},
        {'G', 'D', 'S', 'T', 'B'}
    };

    // Message to encrypt
    char message[] = "Must sec you over Cadogan West. Coming at once.";

    printf("Original Message:\n%s\n\n", message);
    printf("Encrypted Message:\n");
    encryptMessage(playfairMatrix, message);
    printf("\n");

    return 0;
}
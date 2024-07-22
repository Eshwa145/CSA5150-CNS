#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5

// Function to find the position of a character in the key square
void findPosition(char keySquare[SIZE][SIZE], char letter, int *row, int *col)
{
    if (letter == 'J')
        letter = 'I';
    
    for (*row = 0; *row < SIZE; (*row)++)
    {
        for (*col = 0; *col < SIZE; (*col)++)
        {
            if (keySquare[*row][*col] == letter)
                return;
        }
    }
}

// Function to decrypt the message using the Playfair cipher
void decryptPlayfair(char *ciphertext, char keySquare[SIZE][SIZE])
{
    int len = strlen(ciphertext);
    char plaintext[len];
    
    // Prepare the ciphertext by removing spaces and converting to uppercase
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (ciphertext[i] != ' ')
            plaintext[j++] = toupper(ciphertext[i]);
    }
    plaintext[j] = '\0';
    
    // Decrypt pairs of letters
    for (int i = 0; i < j; i += 2)
    {
        int row1, col1, row2, col2;
        findPosition(keySquare, plaintext[i], &row1, &col1);
        findPosition(keySquare, plaintext[i + 1], &row2, &col2);
        
        // Same row
        if (row1 == row2)
        {
            printf("%c%c", keySquare[row1][(col1 - 1 + SIZE) % SIZE], 
                            keySquare[row2][(col2 - 1 + SIZE) % SIZE]);
        }
        // Same column
        else if (col1 == col2)
        {
            printf("%c%c", keySquare[(row1 - 1 + SIZE) % SIZE][col1],
                            keySquare[(row2 - 1 + SIZE) % SIZE][col2]);
        }
        // Rectangle rule
        else
        {
            printf("%c%c", keySquare[row1][col2], keySquare[row2][col1]);
        }
    }
    printf("\n");
}

int main()
{
    // The Playfair key square used for decryption
    char keySquare[SIZE][SIZE] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'E', 'B', 'Z'},
        {'W', 'H', 'R', 'Y', 'T'},
        {'U', 'H', 'E', 'Y', 'F'},
        {'S', 'K', 'R', 'E', 'H'}
    };
    
    // Ciphertext received
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WITTU OLKSY CAJPO BOTEI ZONIX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDO";
    
    // Decrypt the ciphertext
    decryptPlayfair(ciphertext, keySquare);
    
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to remove spaces and convert to lowercase
int cleanText(char text[]) {
    int i, j = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ') {
            text[j++] = tolower(text[i]);
        }
    }
    text[j] = '\0';
    return j;
}

// Function to create 5x5 key matrix
void createKeyMatrix(char key[], char matrix[SIZE][SIZE]) {
    int dict[26] = {0};  // Track used letters
    int i = 0, j = 0;

    // Replace 'j' with 'i'
    for (int k = 0; key[k]; k++)
        if (key[k] == 'j')
            key[k] = 'i';

    // Add letters from key
    for (int k = 0; key[k]; k++) {
        int index = key[k] - 'a';
        if (!dict[index]) {
            matrix[i][j++] = key[k];
            dict[index] = 1;
            if (j == 5) { i++; j = 0; }
        }
    }

    // Add remaining alphabets
    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue;  // skip j
        if (!dict[ch - 'a']) {
            matrix[i][j++] = ch;
            dict[ch - 'a'] = 1;
            if (j == 5) { i++; j = 0; }
        }
    }

    // Display the key matrix
    printf("\nPlayfair Key Matrix:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++)
            printf("%c ", toupper(matrix[i][j]));
        printf("\n");
    }
}

// Function to find position of a letter in key matrix
void findPosition(char matrix[SIZE][SIZE], char letter, int *row, int *col) {
    if (letter == 'j') letter = 'i';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to prepare plaintext (add x if same letters or odd length)
int prepareText(char text[]) {
    int len = strlen(text);

    for (int i = 0; i < len; i += 2) {
        if (text[i] == text[i + 1]) {
            // shift and insert 'x'
            for (int j = len; j > i + 1; j--)
                text[j] = text[j - 1];
            text[i + 1] = 'x';
            len++;
        }
    }

    if (len % 2 != 0) {
        text[len++] = 'x';
    }
    text[len] = '\0';
    return len;
}

// Function to encrypt text using Playfair cipher
void encrypt(char text[], char matrix[SIZE][SIZE]) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(matrix, text[i], &r1, &c1);
        findPosition(matrix, text[i + 1], &r2, &c2);

        if (r1 == r2) {  // same row
            text[i] = matrix[r1][(c1 + 1) % 5];
            text[i + 1] = matrix[r2][(c2 + 1) % 5];
        } 
        else if (c1 == c2) {  // same column
            text[i] = matrix[(r1 + 1) % 5][c1];
            text[i + 1] = matrix[(r2 + 1) % 5][c2];
        } 
        else {  // rectangle swap
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }

    // Convert to uppercase for better readability
    for (int i = 0; i < len; i++)
        text[i] = toupper(text[i]);

    printf("\nEncrypted Text: %s\n", text);
}

// ---------- MAIN FUNCTION ----------
int main() {
    char key[50], text[200];
    char matrix[SIZE][SIZE];

    printf("Enter key: ");
    scanf("%[^\n]%*c", key);

    printf("Enter plaintext: ");
    scanf("%[^\n]%*c", text);

    cleanText(key);
    cleanText(text);
    prepareText(text);

    createKeyMatrix(key, matrix);
    encrypt(text, matrix);

    return 0;
}


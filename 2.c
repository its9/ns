#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
char* encrypt(const char* plaintext, const char* key) {
    int i;
    static char ciphertext[1000];
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(key[plaintext[i] - 'a']);
            } else {
                ciphertext[i] = toupper(key[plaintext[i] - 'A']);
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';

    return ciphertext;
}

char* decrypt(const char* ciphertext, const char* key) {
    int i, j;
    static char plaintext[1000];
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (islower(ciphertext[i])) {
                for (j = 0; j < ALPHABET_SIZE; j++) {
                    if (tolower(key[j]) == tolower(ciphertext[i])) {
                        plaintext[i] = 'a' + j;
                        break;
                    }
                }
            } else {
                for (j = 0; j < ALPHABET_SIZE; j++) {
                    if (toupper(key[j]) == toupper(ciphertext[i])) {
                        plaintext[i] = 'A' + j;
                        break;
                    }
                }
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
    return plaintext;
}
int main() {
    const char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    const char plaintext[] = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
    printf("Original plaintext: %s\n", plaintext);
    char* ciphertext = encrypt(plaintext, key);
    printf("Encrypted ciphertext: %s\n", ciphertext);
    char* decrypted_plaintext = decrypt(ciphertext, key);
    printf("Decrypted plaintext: %s\n", decrypted_plaintext);

    return 0;
}

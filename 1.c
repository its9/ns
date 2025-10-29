#include <stdio.h>

void caesar(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; ++i) {
        if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = 'a' + (26 + (text[i] - 'a' + shift) % 26) % 26;
        else if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = 'A' + (26 + (text[i] - 'A' + shift) % 26) % 26;
    }
}

int main() {
    char message[100];
    int key;

    // Get message from user
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);  // safer than gets()

    // Get key from user
    printf("Enter shift key: ");
    scanf("%d", &key);

    printf("\nOriginal message: %s", message);

    // Encryption
    caesar(message, key);
    printf("Encrypted message: %s", message);

    // Decryption
    caesar(message, -key);
    printf("Decrypted message: %s", message);

    return 0;
}


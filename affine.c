#include <stdio.h>
#include <ctype.h>
#include <string.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // Inverse doesn't exist
}

void affine_encrypt(char *plaintext, int key_a, int key_b) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            plaintext[i] = (key_a * (plaintext[i] - base) + key_b) % 26 + base;
        }
    }
}

void affine_decrypt(char *ciphertext, int key_a, int key_b) {
    int a_inv = mod_inverse(key_a, 26);
    if (a_inv == -1) {
        printf("Inverse does not exist for the given key.\n");
        return;
    }
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            ciphertext[i] = (a_inv * (ciphertext[i] - base - key_b + 26)) % 26 + base;
        }
    }
}

int main() {
    char plaintext[] = "meghana";
    char ciphertext[100];
    int key_a = 5, key_b = 8;

    strcpy(ciphertext, plaintext);
    affine_encrypt(ciphertext, key_a, key_b);
    printf("Affine Cipher - Encryption: %s\n", ciphertext);

    affine_decrypt(ciphertext, key_a, key_b);
    printf("Affine Cipher - Decryption: %s\n", ciphertext);

    return 0;
}

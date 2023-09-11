#include <stdio.h>
#include <math.h>

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate (base^exponent) % modulus using fast exponentiation
long long fastExponentiation(long long base, long long exponent, long long modulus) {
    long long result = 1;

    base %= modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}

// Function to find modular inverse using Extended Euclidean Algorithm
int findModularInverse(int a, int m) {
   for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

int main() {
    int p, q, n, phi, e, d;

    // Step 1: Input two prime numbers p and q
    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    // Step 2: Calculate n = p * q
    n = p * q;

    // Step 3: Calculate φ(n) = (p-1) * (q-1)
    phi = (p - 1) * (q - 1);

    // Step 4: Choose an integer e such that 1 < e < φ(n) and gcd(e, φ(n)) = 1
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }

    // Step 5: Calculate d, the modular multiplicative inverse of e modulo φ(n)
    d = findModularInverse(e, phi);

    // Display public and private keys
    printf("\nPublic Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    // Encryption
    int plaintext;
    printf("\nEnter plaintext to be encrypted: ");
    scanf("%d", &plaintext);

    long long ciphertext = fastExponentiation(plaintext, e, n);
    printf("Ciphertext: %lld\n", ciphertext);

    // Decryption
    long long decryptedText = fastExponentiation(ciphertext, d, n);
    printf("Decrypted Text: %lld\n", decryptedText);

    return 0;
}


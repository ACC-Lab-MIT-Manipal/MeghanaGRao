#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Define the maximum number of iterations to avoid infinite loop
#define MAX_ITERATIONS 10000

// Function to compute the greatest common divisor (GCD) using Euclid's algorithm
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Pollard's Rho algorithm for integer factorization
uint64_t pollardRho(uint64_t n) {
    srand(time(NULL));
    uint64_t x = rand() % (n - 2) + 2;
    uint64_t y = x;
    uint64_t c = rand() % (n - 1) + 1;
    uint64_t d = 1;

    int iterations = 0;
    while (d == 1 && iterations < MAX_ITERATIONS) {
        x = (x * x + c) % n;
        y = (y * y + c) % n;
        y = (y * y + c) % n;
        d = gcd(abs(x - y), n);
        iterations++;
    }

    if (d == n || d == 1) {
        return 0; // Factorization failed
    } else {
        return d; // Found a non-trivial factor
    }
}

int main() {
    uint64_t n;

    printf("Enter an integer to factorize: ");
    scanf("%llu", &n);

    if (n <= 1) {
        printf("Input must be a positive integer greater than 1.\n");
        return 1;
    }

    printf("Prime factors of %llu are:\n", n);
    while (n > 1) {
        uint64_t factor = pollardRho(n);
        if (factor == 0) {
            printf("%llu ", n); // n is prime
            break;
        }
        printf("%llu ", factor);
        n /= factor;
    }
    printf("\n");

    return 0;
}

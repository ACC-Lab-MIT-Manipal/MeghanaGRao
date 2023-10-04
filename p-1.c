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

// Function to perform modular exponentiation (base^exponent % modulus)
uint64_t modExp(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

// Pollard's p-1 algorithm for integer factorization
uint64_t pollardPMinus1(uint64_t n, uint64_t max_iterations) {
    uint64_t a = 2; // Starting value for 'a'

    for (uint64_t i = 2; i <= max_iterations; i++) {
        a = modExp(a, i, n);
        uint64_t d = gcd(a - 1, n);

        if (d > 1 && d < n) {
            return d; // Found a non-trivial factor
        } else if (d == n) {
            return 0; // Factorization failed
        }
    }

    return 0; // Factorization failed
}

int main() {
    uint64_t n, max_iterations;

    printf("Enter an integer to factorize: ");
    scanf("%llu", &n);

    if (n <= 1) {
        printf("Input must be a positive integer greater than 1.\n");
        return 1;
    }

    printf("Enter the maximum number of iterations: ");
    scanf("%llu", &max_iterations);

    printf("Prime factors of %llu are:\n", n);
    uint64_t factor = pollardPMinus1(n, max_iterations);
    if (factor == 0) {
        printf("%llu is prime or factorization failed.\n", n);
    } else {
        printf("%llu ", factor);
        n /= factor;
        while (n > 1) {
            factor = pollardPMinus1(n, max_iterations);
            if (factor == 0) {
                printf("%llu ", n); // n is prime
                break;
            }
            printf("%llu ", factor);
            n /= factor;
        }
        printf("\n");
    }

    return 0;
}

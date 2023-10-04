#include <stdio.h>
#include <math.h>

void fermatFactor(int n) {
    int a, b, x, y;

    if (n % 2 == 0) {
        a = 2;
        b = n / 2;
        printf("%d = %d * %d\n", n, a, b);
        return;
    }

    x = sqrt(n) + 1;
    y = sqrt(x * x - n);

    while (y * y != x * x - n) {
        x++;
        y = sqrt(x * x - n);
    }

    a = x - y;
    b = x + y;

    printf("%d = %d * %d\n", n, a, b);
}

int main() {
    int n;

    printf("Enter an integer to factor: ");
    scanf("%d", &n);

    fermatFactor(n);

    return 0;
}


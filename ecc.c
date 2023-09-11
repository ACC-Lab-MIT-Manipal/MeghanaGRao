#include <stdio.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

int a, b, p; // Curve parameters

// Function to check if a point lies on the curve
int isPointOnCurve(Point point) {
    return (int)(pow(point.y, 2) - (pow(point.x, 3) + a * point.x + b)) % p == 0;
}

int main() {
    printf("Enter the parameters for the elliptic curve (a, b, p): ");
    scanf("%d %d %d", &a, &b, &p);

    printf("Points on the elliptic curve:\n");

    for (int x = 0; x < p; x++) {
        int y_squared = (int)(pow(x, 3) + a * x + b);
        int y = (int)(sqrt(abs(y_squared))) % p;

        if (isPointOnCurve((Point){x, y}) || isPointOnCurve((Point){x, -y})) {
            printf("(%d, %d)\n", x, y);
        }
    }

    return 0;
}

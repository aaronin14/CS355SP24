#include <stdio.h>

int main() {
    float fF, fC;
    printf("F = ");
    scanf("%f", &fF);
    fC = (fF - 32) / 9 * 5;
    printf("%.2f F = %.2f C", fF, fC);
    return 0;
}

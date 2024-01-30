#include <stdio.h>

int main() {
    int iCelsius, iFahrenheit = 98;
    iCelsius = (iFahrenheit - 32) / 9 * 5;
    printf("%dF is %dC\n", iFahrenheit, iCelsius);

    float fCelsius, fFahrenheit = 98.0;
    fCelsius = (fFahrenheit - 32) / 9 * 5;
    printf("%.2fF is %2.2fC\n", fFahrenheit, fCelsius);
    return 0;
}
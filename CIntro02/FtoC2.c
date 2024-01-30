#include <stdio.h>

int main() {
    float fCelsius = 0, fFahrenheit = 0;
    printf("Please enter the tempature in Fahrenheit: ");
    scanf("%f", &fFahrenheit);
    fCelsius = (fFahrenheit - 32) / 9 * 5;
        
    printf("%.2fF is %2.2fC\n", fFahrenheit, fCelsius);
    return 0;
}
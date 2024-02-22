#include <stdio.h>
#include <math.h>

int main() {
    double a,b,c;

    printf("Enter side A and side B:");
    scanf("%lf %lf",&a,&b);
    
    c = sqrt(a*a + b*b);

    printf("Side C: %lf",c);
    return 0;
}
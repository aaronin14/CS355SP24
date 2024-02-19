#include <stdio.h>

int main() {
    const double PI = 3.14159;
    double radius;
    double circumference;
    double area;

    printf("Radius: ");
    scanf("%lf", &radius);

    circumference = 2 * PI * radius;
    area = PI * radius * radius;

    printf("Circumference: %.4lf\n", circumference);
    printf("Area: %.4lf\n", area);
    return 0;
}
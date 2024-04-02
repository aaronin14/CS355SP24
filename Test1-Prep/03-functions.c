#include <stdio.h>

int sum(int a, int b);
int product(int a, int b);
int difference(int a, int *b);

int main() {
    int a, b;
    printf("Please enter 2 integers: ");
    scanf("%d %d", &a, &b);
    printf("You entered %d and %d", a, b);

    printf("Sum of a and b is: %d\n", sum(a,b));
    printf("Product of a and b is: %d\n", product(a, b));
    printf("Difference of a and b is %d\n", difference(a, &b));
    return 0;
}

int sum(int a, int b) {
    return a+b;
}
int product(int a, int b) {
    return a*b;
}
int difference(int a, int *b) {
    return a - *b;
}

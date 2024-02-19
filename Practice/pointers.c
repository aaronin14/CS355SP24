#include <stdio.h>

void printAge(int *pAge) {
    printf("You are %d years old\n", *pAge);
}

int main() {
    int age = 27;
    int *pAge = 0;
    pAge = &age;

    printf("Address of age: %p\n", &age);
    printf("Value of pAge: %p\n", pAge);

    printf("Value at pAge: %d\n", *pAge);
    printf("Value of age: %d\n", age);

    printAge(pAge);

    return 0;
}
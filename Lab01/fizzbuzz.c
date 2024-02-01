//Aaron Nguyen - CS 355-02

#include <stdio.h>

int fizzBuzz(int);

int main() {
    int iNum = 0;
    printf("Please enter an integer: ");
    scanf("%d", &iNum);
    
    for (int i = 0; (iNum>=0) ? i<=iNum : i>=iNum; (iNum>=0) ? i++ : i--)
        fizzBuzz(i);
    return 0;
}

int fizzBuzz(int i) {
    if (i % 3 == 0) printf("Fizz");
    if (i % 5 == 0) printf("Buzz");
    if (i % 3 != 0 && i % 5 != 0) printf("%d", i);
    printf("\n");
    return 0;
}

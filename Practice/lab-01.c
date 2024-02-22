#include <stdio.h>

void fizzbuzz(int n) {
    if (n % 3 == 0 || n % 5 ==0) {
        if (n % 3 == 0) printf("Fizz");
        if (n % 5 == 0) printf("Buzz");
    } else {
        printf("%d", n);
    }
}

int main() {
    int intN;
    printf("Enter an integer: ");
    scanf("%d", &intN);
    if (intN>0) {
        for (int i=0; i<=intN; i++) {
            fizzbuzz(i);
            printf("\n");
        }
    } else {
        for (int i=0; i>=intN; i--) {
            fizzbuzz(i);
            printf("\n");
        }
    }
    return 0;
}

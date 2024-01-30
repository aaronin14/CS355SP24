#include <stdio.h>

int main() {
    int iNum = 0;
    printf("Please enter an integer: "); 
    scanf("%d", &iNum); 
    if (iNum >=0) { 
        for (int i = 0; i <= iNum; i++) {
            if (i % 3 == 0) {
                if (i % 5 == 0)
                    printf("FizzBuzz\n");
                else 
                    printf("Fizz\n");
            } 
            else if (i % 5 == 0)
                printf("Buzz\n"); 
            else 
                printf("%d\n", i);
        }
    }
    else {
        for (int i = 0; i >= iNum; i--) {
            if (i % 3 == 0) {
                if (i % 5 == 0)
                    printf("FizzBuzz\n");
                else 
                    printf("Fizz\n");
            } 
            else if (i % 5 == 0)
                printf("Buzz\n"); 
            else 
                printf("%d\n", i);
        }
    }
    return 0;
}

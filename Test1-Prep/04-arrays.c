#include <stdio.h>

int main() {
    int intArray[10];
    for (int i = 0; i< 10; i++) {
        intArray[i] = i*2+1;
        printf("intArray[%d] = %d\n", i, intArray[i]);
    }
    return 0;
}

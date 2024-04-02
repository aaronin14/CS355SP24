#include <stdio.h>

int main() {
    char strName[50];
    printf("What is your name? ");
    scanf("%s", &strName);
    printf("Hello %s!\n", strName);
    return 0;
}

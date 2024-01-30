#include <stdio.h>

int main(){
    int iAge = 0;
    printf("How old are you? ");
    int iReturnValue = scanf("%d", &iAge);

    if (iReturnValue!=1) {
        printf("scanf() could not interpret your input!\n");
        return 1;
    }

    if (iAge>=0 && iAge<=120){
        if (iAge<21) 
            printf("You cannot legally enjoy alcoholic beverage.\n");
        else
            printf("Your age is %d, you fit right in.\n", iAge);
    }
    else {
        printf("You entered an invalid age: %d\n", iAge);
    }

    return 0;
}
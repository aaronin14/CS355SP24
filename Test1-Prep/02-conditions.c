#include <stdio.h>                              // include the standard input output methods

int main() {                                    // the main function will return an integer value
    int intAge;                                 // Declare an Integer variable
    printf("How old are you? ");                // Ask for input
    int iReturnValue = scanf("%d", &intAge);    // scanf will receive 1 integer value and store it in the box at address of intAge 
    if (iReturnValue != 1) {                    // if success, iReturn will get value 1.
        printf("scanf() couldn't interpret your input\n");
        return 1;                               // intAge doesn't receive a value, end the program
    }
    if (intAge <= 125 && intAge >=0) {          // check the if the age is realistic
        if (intAge>=21) {                       // self-explainatory
            printf("You are over 21, take a sip!");    
        } else if (intAge >= 18) {
            printf("You can hang around but you cannot drink!");
        } else {
            printf("Go home kiddo!!");
        }
    } else {
        printf("Invalid age: %d",intAge);       // if age is unrealistic <0 or > 125
    }
    return 0;                                   
}

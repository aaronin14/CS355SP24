#include <stdio.h>
#include <string.h>

int main() {
    char* string1 = "Hello, world!"; // only declared a pointer variable

    printf("string1 = %s\n", string1);

    //string1[5] = 'X';
    //printf("string1 = %s\n", string1); //"Hello world" is a constant, auto -> code section, which is not allowed
    
    char string2[25] = "Hello, world!"; // declared a whole char array
    printf("string2 = %s\n", string2);

    string2[5] = 'X';
    printf("string2 = %s\n", string2);

    for (int i=0; i<strlen(string2); i++) {
        printf("string2[%d] = %c (%d)\n", i, string2[i], string2[i]);
    }

    for (int i=0; string2[i]!=0; i++) {
        printf("string2[%d] = %c (%d)\n", i, string2[i], string2[i]);
    }


    string1 = string2;
    printf("string1 = %s", string1); 

    return 0;
}

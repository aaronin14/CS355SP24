#include <stdio.h>
#include <string.h>

int main() {
    char* string1 = "Hello World!";
    printf("string1 = %s\n", string1);

    char string2[25] = "Hello World!";
    printf("string2 = %s\n", string2);
    string2[5]='X';
    printf("string2 = %s\n", string2);

    for (int i=0; i<strlen(string2); i++) {
        printf("%c\n",string2[i]);
    }

    for (int i=0; string2[i]!=0; i++) {
        printf("%c\n",string2[i]);
    }

    return 0;
}

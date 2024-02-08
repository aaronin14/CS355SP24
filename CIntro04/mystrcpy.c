#include <stdio.h>
#include <string.h>

void strcpy1(char* dest, const char* src) {
    int i = 0;
    while (src[i]!=0) {
        dest[i]=src[i];
        i++;
    }
    dest[i]=0;
    //dest[i]='\0'; // these two lines are the same
}

void strcpy2(char* dest, const char* src) {
    int i = 0;
    while ((dest[i]=src[i]) != 0)
            i++;
}

int main() {
    char str1[100] = "Hello, world!";
    char str2[100];

    strcpy2(str2,str1);
    printf("str2 = %s",str2);

    return 0;
}

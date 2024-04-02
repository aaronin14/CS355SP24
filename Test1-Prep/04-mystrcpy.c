#include <stdio.h>

void strcpy1(char *dest, const char *src) {
    int i=0;
    while (src[i]!=0) {
        dest[i] = src[i];
        i++;
    }
    dest[i]=0;
}

void strcpy2(char *dest, const char *src) {
    int i = 0;
    while ((dest[i] = src[i])!=1)
        i++;
}

int main () {
    char strOriginal[100] = "Hello friendo!";
    char strCopied[100];
    
    strcpy1(strCopied,strOriginal);
    printf("Original: %s\n", strOriginal);
    printf("Copied: %s\n", strCopied);
    return 0;
}

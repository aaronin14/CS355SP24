#include <stdio.h>

int isAlpha(char c) {
    return ((c>='A' && c<='Z') || (c>='a' && c<='z'));
}
void printStuff(char *str) {
    for (int i=0; str[i]!=0; i++) {
        if (isAlpha(str[i]))
            for (int j=0; j<=i; j++)
                if (isAlpha(str[j]))
                    printf("%c",str[j]);
        printf("\n");
    }
}

int main(int ac, char *av[]) {
    for (int i=1; i<ac;i++) {
    printStuff(av[i]);
    }
    return 0;
}

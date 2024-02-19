#include <stdio.h>
#include <string.h>

int main() {
    char name[25]; // bytes
    int age;

    printf("What is your name?\n");
    //scanf("%s", &name); //scanf function will only read up to any white space 
    fgets(name, 25, stdin); //fgets function will get the whole line (also include the new line character)

    name[strlen(name)-1] = '\0'; //to replace '\n' with '\0', which represent the end of the string.

    printf("How old are you?\n");
    scanf("%d", &age);

    printf("Hello %s!\n", name);
    printf("You are %d years old", age);
    return 0;
}
//qtip search

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxWords 5
#define MaxWordLength 100

int myStringCompare(const void *a, const void *b) {
    return strcmp((const char*)a,(const char*)b);
}

int main() {
    char words[MaxWords][MaxWordLength] = {"oranges", "grapes", "bananas", "apples"};
    qsort(words,MaxWords,MaxWordLength, myStringCompare);
    return 0;
}

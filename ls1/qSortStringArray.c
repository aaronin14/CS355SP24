#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// an example of using qsort with an array of strings
// also see https://man7.org/linux/man-pages/man3qsort.3.html

#define MaxWords 6
#define MaxWordLength 100

int myStringCompare(const void *a, const void *b) {
    return strcmp((const char*)a,(const char*)b);
}

int main() {
    char words[MaxWords][MaxWordLength] = {"oranges", "grapes", "bananas", "apples", "TV", "1234"};

    qsort(words,MaxWords,MaxWordLength, myStringCompare);

    for(int i=0; i<MaxWords; i++)
        printf("%d %s\n", i+1, words[i]);

    return 0;
}

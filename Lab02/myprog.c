#include <stdio.h>

int isLetter(char c) {
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
void printArg(char *str) {
  for (int i = 0; str[i] != 0; i++) {
    if (isLetter(str[i])) {
      for (int j = 0; j <= i; j++) {
        if (isLetter(str[j]))
          printf("%c", str[j]);
      }
      printf("\n");
    }
  }
}

int main(int ac, char *av[]) {
  for (int i = 1; i < ac; i++) {
    printArg(av[i]);
  }
  return 0;
}

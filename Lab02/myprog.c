#include <stdio.h>

int checkChar(char c) {
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    return 1;
  else
    return 0;
}
void printArg(char *str) {
  for (int i = 0; str[i] != 0; i++) {
    // printf("%c - ", str[i]);
    if (checkChar(str[i])) {
      for (int j = 0; j <= i; j++) {
        if (checkChar(str[j]))
          printf("%c", str[j]);
      }
      printf("\n");
    }
  }
}

int main(int ac, char *av[]) {
  if (ac == 1)
    printf("Usage: myprog <argument1> <argument2> ...");
  for (int i = 1; i < ac; i++) {
    printArg(av[i]);
  }
  return 0;
}

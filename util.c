#include "util.h"
#include <stdio.h>

void remove_newl(char *str) {
  int len = strlen(str);

  str[len - 1] = '\0';
}

// if i dont do this, getchar in the prompt may read the previous buffered
// characters
void flush() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

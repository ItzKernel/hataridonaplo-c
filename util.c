#include "util.h"

/*
 * Removes 
 * */
void remove_newl(char *str) {
  int len = strlen(str);

  str[len - 1] = '\0';
}

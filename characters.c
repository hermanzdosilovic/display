#include <stdio.h>

int main(void) {
  char c;
  for (c = ' '; c <= '~'; c++) {
    printf("%c\n", c);
  }
  return 0;
}

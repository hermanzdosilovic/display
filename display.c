/*
compile and run: gcc -std=c99 display.c -o display && ./display
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000000
#define DISPLAY_WIDTH 50

char *message;

char *filename = "message.txt";

int main(void) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file %s\n", filename);
  }

  message = (char *) calloc(MAX_LINE_LENGTH + 1, sizeof(char));
  fgets(message, MAX_LINE_LENGTH + 1, file);

  int length = strlen(message);
  if (message[length - 1] == '\n') {
    message[length - 1] = '\0';
    length--;
  }

  while(1) {
    for (int x = DISPLAY_WIDTH - 1; x >= -length; x--) {
      for (int i = 0; i < x; i++) {
        printf(" ");
      }
      for (int i = -fmin(0, x); x + i < DISPLAY_WIDTH && i <= length; i++) {
        printf("%c", message[i]);
      }
      for (int i = 0; x + i <= DISPLAY_WIDTH; i++) {
        printf(" ");
      }

      clock_t start = clock(), end;
      while(1) {
        end = clock() - start;
        float t = (float) end/CLOCKS_PER_SEC;
        if (fabs(t - 0.16) < 1e-5)
          break;
      }

      printf("\r");
      fflush(stdout);
    }
  }

  return EXIT_SUCCESS;
}

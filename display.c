/*
compile and run: gcc -std=c99 display.c -o display -lm && ./display
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
const char separator = '\\';
#else
#define CLEAR "clear"
const char separator = '/';
#endif

#define MAX_LINE_LENGTH 100
#define DISPLAY_WIDTH 80
#define RIGHT_SPACE 2

int message_length;
char *message;

int text_width, text_height;
char **text;

char *filename = "message.txt";

char *fontfolder = "fonts";
char *fontname = "colossal";
const int font_height = 11;
char ***font;

const int chars = '~' - ' ' + 1; // number of characters that font has

int max(int x, int y) {
  return x > y ? x : y;
}

void load_font() {
  int length = strlen(fontfolder) + strlen(fontname) + 2;
  char *fontpath = (char *) calloc(length, sizeof(char));
  sprintf(fontpath, "fonts%c%s", separator, fontname);

  FILE *file = fopen(fontpath, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file %s\n", fontpath);
    exit(EXIT_FAILURE);
  }

  char **buffer = (char **) calloc(font_height, sizeof(char *));
  for (int i = 0; i < font_height; i++) {
    buffer[i] = (char *) calloc(MAX_LINE_LENGTH + 1, sizeof(char));
  }

  int max_width = 0;
  font = (char ***) calloc(chars, sizeof(char **));
  for (int i = 1; i < chars; i++) {
    font[i] = (char **) calloc(font_height, sizeof(char *));
    int char_width = 0;
    for (int x = 0; x < font_height; x++) {
      fgets(buffer[x], MAX_LINE_LENGTH + 1, file);
      int length = strlen(buffer[x]);
      if (buffer[x][length - 1] == '\n') {
        buffer[x][length - 1] = '\0';
        length--;
      }
      char_width = max(char_width, length);
      max_width = max(max_width, length);

    }
    char_width += RIGHT_SPACE;
    for (int x = 0; x < font_height; x++) {
      font[i][x] = (char *) calloc(char_width + 1, sizeof(char));
      strcat(font[i][x], buffer[x]);
      for (int k = strlen(font[i][x]); k < char_width; k++) {
        font[i][x][k] = ' ';
      }
    }
  }

  int space_width = max_width/2 + RIGHT_SPACE;
  font[0] = (char **) calloc(font_height, sizeof(char *));
  for (int x = 0; x < font_height; x++) {
    font[0][x] = (char *) calloc(space_width + 1, sizeof(char));
    for (int i = 0; i < space_width; i++) {
      font[0][x][i] = ' ';
    }
  }

  free(buffer);
  fclose(file);
}

void create_text() {
  text_height = font_height;
  text_width = 0;
  text = (char **) calloc(text_height, sizeof(char *));
  for (int x = 0; x < font_height; x++) {
    int width = 0;
    for (int i = 0; i < message_length; i++) {
      width += strlen(font[message[i] - ' '][x]);
    }
    text[x] = (char *) calloc(width + 1, sizeof(char));
    text_width = max(text_width, width);
    for (int i = 0; i < message_length; i++) {
      strcat(text[x], font[message[i] - ' '][x]);
    }
  }
}

void frame() {
  printf("+");
  for (int i = 0; i < DISPLAY_WIDTH; i++) {
    printf("-");
  }
  printf("+\n");
}
int main(void) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file %s\n", filename);
    return EXIT_FAILURE;
  }

  load_font();

  message = (char *) calloc(MAX_LINE_LENGTH + 1, sizeof(char));
  fgets(message, MAX_LINE_LENGTH + 1, file);

  message_length = strlen(message);
  if (message[message_length - 1] == '\n') {
    message[message_length - 1] = '\0';
    message_length--;
  }

  create_text();

  system(CLEAR);
  while(1) {
    for (int x = DISPLAY_WIDTH; x > -text_width; x--) {

      frame();

      for (int k = 0; k < text_height; k++) {
        int length = strlen(text[k]);
        int caret = 0;
        printf("|");
        for (int i = 0; i < x; i++) {
          printf(" ");
          caret++;
        }

        for (int i = -fmin(0, x); caret < DISPLAY_WIDTH && i < length; i++) {
          printf("%c", text[k][i]);
          caret++;
        }
        for (; caret < DISPLAY_WIDTH; caret++) {
          printf(" ");
        }

        printf("|\n");
      }

      frame();

      clock_t start = clock(), end;
      while(1) {
        end = clock() - start;
        float t = (float) end/CLOCKS_PER_SEC;
        if (fabs(t - 0.06) < 1e-2) {
          break;
        }
      }

      system(CLEAR);
    }
  }

  return EXIT_SUCCESS;
}

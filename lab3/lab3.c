#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

static void add_to_history(char *history[], int *next, char *line) {
  free(history[*next]);
  history[*next] = line;
  *next = (*next + 1) % HISTORY_SIZE;
}

static void print_history(char *history[], int next) {
  for (int i = 0; i < HISTORY_SIZE; i++) {
    int idx = (next + i) % HISTORY_SIZE;
    if (history[idx] != NULL) {
      printf("%s\n", history[idx]);
    }
  }
}

static void free_history(char *history[]) {
  for (int i = 0; i < HISTORY_SIZE; i++) {
    free(history[i]);
    history[i] = NULL;
  }
}

int main(void) {
  char *history[HISTORY_SIZE] = {NULL};
  int next = 0;

  while (1) {
    char *line = NULL;
    size_t len = 0;

    printf("Enter input: ");
    if (getline(&line, &len, stdin) == -1) {
      free(line);
      break;
    }

    line[strcspn(line, "\n")] = '\0';

    add_to_history(history, &next, line);

    if (strcmp(line, "print") == 0) {
      print_history(history, next);
    }
  }

  free_history(history);
  return 0;
}

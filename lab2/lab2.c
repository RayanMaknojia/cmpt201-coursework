#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t cap = 0;

  while (1) {
    printf("Enter programs to run. \n> ");
    fflush(stdout);

    ssize_t len = getline(&line, &cap, stdin);
    if (len == -1) {
      break;
    }

    if (line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      break;
    }

    if (pid == 0) {
      execlp(line, line, (char *)NULL);
      fprintf(stderr, "Exec failure\n");
      free(line);
      _exit(1);
    }

    if (waitpid(pid, NULL, 0) == -1) {
      perror("waitpid");
      break;
    }
  }

  free(line);
  return 0;
}

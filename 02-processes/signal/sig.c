#define _POSIX_C_SOURCE 200809
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *message = "CTRL-C PRESSED\n";
void handle_sigint(int signum) { write(STDOUT_FILENO, message, strlen(message)); }

int main(void) {

  struct sigaction act;
  act.sa_handler = handle_sigint;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  if (sigaction(SIGINT, &act, NULL) == -1) {
    perror("sigaction() failed");
    exit(EXIT_FAILURE);
  }

  while (true) {
    sleep(1);
  }
}

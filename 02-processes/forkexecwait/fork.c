#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    printf("CHILD, PID: %d, PPID: %d\n", getpid(), getppid());
  } else {
    printf("PARENT, PPID: %d, PID: %d\n", getpid(), pid);
  }
  return 0;
}

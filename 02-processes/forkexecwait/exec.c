#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  pid_t pid = fork();

  if (pid == 0) {
      printf("CHILD: PID= %d, parentpid= %d,\n", getpid(), getppid();
      
      //char *const args[] = {"ls", "-a", 0};
     // execvp("ls",args);

      char *args[] = {"echo","hello", "world"};
      execvp("echo", args);
  } else {
    // execlp("ls", "ls", "-a", Null);
    printf("PARENT: PID= %d, childpid= %d,\n", getpid(), pid);
    execlp("ls", "ls", "-a", "-l", "-h", NULL);
  }
}

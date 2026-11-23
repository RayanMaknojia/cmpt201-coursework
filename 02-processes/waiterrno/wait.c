#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main()
{
  pid_t pid = fork();
  if( pid == 0)
  {
    int wstatus =0;
    if( waitpid(pid, &wstatus, 0) == -1)
    {
      perror("waitpid");
      exit(EXIT_FAILURE);
    };

    if(WIFEXITED(wstatus) ){
      printf("Child process terminated, exit status: %d\n", WEXITSTATUS(wstatus));
    }
    else{
    printf("CHILD did not exit normally. \n");
    };
  }
  else {
    //parent
    if(execlp("ls","ls","-a","-l", NULL) == -1) {
      perror("execl");
      exit(EXIT_FAILURE);
    };
  };
}

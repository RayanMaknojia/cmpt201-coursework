#include <stdio.h>
#include <unistd.h>

// int main () {
//   printf("hello world\n");
// }

int main() {
  fork();
  while ('true') {
    printf("still going\n");
    sleep(1);
  }
}

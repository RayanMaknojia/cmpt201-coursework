#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int Count = 0;

void *my_thread(void *arg) {
  for (int i = 0; i < 10000000; i++) {
    Count = Count + 1;
  }
  return NULL;
}

int main() {

  pthread_t id1;
  pthread_t id2;

  if (pthread_create(&id1, NULL, my_thread, NULL) != 0) {
    perror("Unable to create thread1");
    exit(EXIT_FAILURE);
  }
  if (pthread_join(id1, NULL) != 0) {
    perror("Unable to join1");
    exit(EXIT_FAILURE);
  }

  if (pthread_create(&id2, NULL, my_thread, NULL) != 0) {
    perror("Unable to create thread2");
    exit(EXIT_FAILURE);
  }

  if (pthread_join(id2, NULL) != 0) {
    perror("Unable to join2");
    exit(EXIT_FAILURE);
  }
  printf("the count final is: %d\n", Count);
  return 0;
}

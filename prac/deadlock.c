#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex0 = PTHREAD_MUTEX_INITIALIZER;

static void *thread1(void *arg) {
  sleep(1);
  pthread_mutex_lock(&mutex0);
  printf("thread1: mutex0\n");

  // sleep(1);

  pthread_mutex_lock(&mutex1);
  printf("thread1: mutex1\n");
  pthread_mutex_unlock(&mutex0);
  pthread_mutex_unlock(&mutex1);
  pthread_exit(0);
}

static void *thread2(void *arg) {
  pthread_mutex_lock(&mutex1);
  printf("thread2: mutex1\n");
  pthread_mutex_lock(&mutex0);
  printf("thread2: mutex0\n");
  pthread_mutex_unlock(&mutex0);
  pthread_mutex_unlock(&mutex1);
  pthread_exit(0);
}

int main() {

  pthread_t id1;
  pthread_t id2;

  if (pthread_create(&id1, NULL, thread1, NULL) != 0) {
    perror("Unable to create thread1");
    exit(EXIT_FAILURE);
  }

  if (pthread_create(&id2, NULL, thread2, NULL) != 0) {
    perror("Unable to create thread2");
    exit(EXIT_FAILURE);
  }

  if (pthread_join(id1, NULL) != 0) {
    perror("Unable to join1");
    exit(EXIT_FAILURE);
  }

  if (pthread_join(id2, NULL) != 0) {
    perror("Unable to join2");
    exit(EXIT_FAILURE);
  }
  return 0;
}

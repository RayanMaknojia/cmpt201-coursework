#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int BUF_SIZE = 256;

void handle_error(char *msg) {
  perror(msg);
  exit(1);
}

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

void print_block_data(struct header *block) {
  uint8_t *data = (uint8_t *)block + sizeof(struct header);
  size_t data_size = block->size - sizeof(struct header);

  for (size_t i = 0; i < data_size; i++) {
    uint64_t byte = data[i];
    print_out("%lu\n", &byte, sizeof(byte));
  }
}

int main(void) {
  void *start = sbrk(256);
  if (start == (void *)-1) {
    handle_error("sbrk");
  }

  struct header *first = (struct header *)start;
  struct header *second = (struct header *)((char *)start + 128);

  first->size = 128;
  first->next = NULL;
  second->size = 128;
  second->next = first;

  size_t data_size = 128 - sizeof(struct header);
  memset((char *)first + sizeof(struct header), 0, data_size);
  memset((char *)second + sizeof(struct header), 1, data_size);

  print_out("first block: %p\n", &first, sizeof(&first));
  print_out("second block: %p\n", &second, sizeof(&second));
  print_out("first block size: %lu\n", &first->size, sizeof(first->size));
  print_out("first block next: %p\n", &first->next, sizeof(first->next));
  print_out("second block size: %lu\n", &second->size, sizeof(second->size));
  print_out("second block next: %p\n", &second->next, sizeof(second->next));

  print_block_data(first);
  print_block_data(second);

  return 0;
}

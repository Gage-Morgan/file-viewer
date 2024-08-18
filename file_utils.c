#include <stdio.h>
#include <stdlib.h>

unsigned char* read_file(const char *filename, size_t *size) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("fopen");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  *size = ftell(file);
  fseek(file, 0, SEEK_SET);

  unsigned char *buffer = (unsigned char *)malloc(*size);
  if (!buffer) {
    perror("malloc");
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, *size, file);
  fclose(file);
  return buffer;
}

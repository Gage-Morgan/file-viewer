#include <stdio.h>
#include <stdlib.h>
#include "disassemble.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }

  // Disassemble the file
  if (disassemble_file(argv[1]) != 0) {
    return 1;
  }

  return 0;
}

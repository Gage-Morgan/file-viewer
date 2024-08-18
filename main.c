#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 1024


struct file_t {
  size_t filebytes_s;
  char *cbytes;

  size_t namebuf_s;
  char *file_name;

  FILE *file_ptr;
};

void get_file_size(const FILE *fp, size_t *file_byte_size, struct file_t *fs_t);

int main(int argc, char *argv[]) {
  if (argc < 0 || argc > 1) {
    puts("Useage: ./fv <file_name>");
    return -1;
  }

	// initialize file_t struct 
  struct file_t *fs_t = (struct file_t*)malloc(sizeof(struct file_t));


  // get length of argv[1]
  size_t templen_t = strlen(argv[1]);
  if (templen_t > MAX_BUF) {
    perror("Str size is too big, try a smaller file name...\n");
    return -1;
  }

  // initialize namebuf_s                   
  fs_t->namebuf_s = MAX_BUF;

  // allocate memory for file_name 
  fs_t->file_name = malloc(fs_t->namebuf_s * sizeof(char));

  // Open a file 
  FILE *fp = fopen(fs_t->file_name, "r");
  if (fp == NULL) {
    perror("Failed to open file");
    free(fs_t->file_name); // Clean up allocated memory
    return 1;
  }

  // store the value from fp in fs_t struct 
  fs_t->file_ptr = fp;

  // close fp to prevent duplicate file pointers
  fclose(fp);

  // free allocated memory from the heap
  free(fs_t->file_name);

  return 0;
}

void get_file_size(const FILE *fp, size_t *file_byte_size, struct file_t *fs_t) {
  // get the size of the file and store it into filebytes_s 
  size_t tempbytesize_s = 0;
  char tempchar;
  printf("Attempting to read total bytes from %s\n", fs_t->file_name);
  while ((tempchar = fgetc(fs_t->file_ptr)) != EOF) {
    fs_t->filebytes_s += tempbytesize_s;
  }
}

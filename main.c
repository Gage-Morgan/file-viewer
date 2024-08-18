#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 1024

struct file_t {
  size_t filesize_s;

  unsigned char *read_buf;

  size_t namebuf_s;
  char *file_name;
};

long get_file_size(FILE *fp);
void read_file(FILE *fp, long file_size, unsigned char *buffer);
void print_file(unsigned char *buffer, long file_size);

int main(int argc, char *argv[]) {
  if (argc < 0 || argc > 2) {
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
  fs_t->file_name = (char *)malloc(fs_t->namebuf_s * sizeof(char));

  // copy argv[1] into file_name 
  if (strlen(argv[1]) < MAX_BUF) {
    strncpy(fs_t->file_name, argv[1], MAX_BUF);
  }

  // Open a file 
  FILE *fp = fopen(fs_t->file_name, "r");
  if (fp == NULL) {
    perror("Failed to open file");
    free(fs_t->file_name); // Clean up allocated memory
    return 1;
  }

  // get and set size of file 
  fs_t->filesize_s = get_file_size(fp);
  // allocate total number of bytes for read_buf 
  fs_t->read_buf = (unsigned char *)malloc(fs_t->filesize_s * sizeof(unsigned char));
  // read file 
  read_file(fp, fs_t->filesize_s, fs_t->read_buf);
  print_file(fs_t->read_buf, fs_t->filesize_s);  

  // close file_ptr 
  fclose(fp);
  // free allocated memory from the heap
  free(fs_t->read_buf);
  free(fs_t->file_name);

  return 0;
}

long get_file_size(FILE *fp) {
  // Determine the size of the file
  fseek(fp, 0, SEEK_END);  // Move to the end of the file
  long fileSize = ftell(fp); // Get the current position (file size)
  fseek(fp, 0, SEEK_SET);  // Move back to the beginning of the file
  return fileSize;
}

void read_file(FILE *fp, long file_size, unsigned char *buffer) {
  // Read the file content into the buffer 
  size_t bytes_read = fread(buffer, 1, file_size, fp);
  if (bytes_read != file_size) {
      perror("Failed to read the entire file");
      free(buffer);
      fclose(fp);
  }
}

void print_file(unsigned char *buffer, long file_size) {
  for (size_t i = 0; i < file_size && i < file_size; i++) {
    printf("%02x ", buffer[i]);
  }
  printf("\n");
}

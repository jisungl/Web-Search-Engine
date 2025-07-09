/*
Jisung Lee
jisung@uw.edu
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  //check for correct num of args
  if (argc != 2) {
    fprintf(stderr, "Invalid input");
      return EXIT_FAILURE;
  }

  // open file
  FILE* file = fopen(argv[1], "rb");
  if (file == NULL) {
    fprintf(stderr, "Cannot open file");
    return EXIT_FAILURE;
  }

  //check file size
  if (fseek(file, 0, SEEK_END) != 0) {
    fprintf(stderr, "fseek error");
    fclose(file);
    return EXIT_FAILURE;
  }

  long size = ftell(file);
  if (size < 0) {
    fprintf(stderr, "ftell error");
    fclose(file);
    return EXIT_FAILURE;
  }

  // read + print bytes in reverse
  for (long i = size - 1; i >= 0; i--) {
    if (fseek(file, i, SEEK_SET) != 0) {
        fprintf(stderr, "fseek error within file");
        fclose(file);
        return EXIT_FAILURE;
    }

    unsigned char byte;
    if (fread(&byte, sizeof(unsigned char), 1, file) != 1) {
      fprintf(stderr, "file read error");
      fclose(file);
      return EXIT_FAILURE;
    }

    printf("%c", byte);
  }

  if (fclose(file) != 0) {
    fprintf(stderr, "error closing file");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
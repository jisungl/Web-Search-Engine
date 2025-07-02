/*
Jisung Lee
jisung@uw.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

// prints byte values starting from a memory address in hex
void PrintBytes(void* mem_addr, int num_bytes) {
  // cast a void point as a byte pointer
  uint8_t* ptr = (uint8_t*)mem_addr;

  printf("The %d bytes starting at %p are: ", num_bytes, mem_addr);

  // loop and print each byte value
  for (int i = 0; i < num_bytes; i++) {
    printf(" %02" PRIx8, ptr[i]);
  }

  printf("\n");
}

int main(int argc, char **argv) {

  char     char_val = '0';

  int32_t  int_val = 1;

  float    float_val = 1.0;

  double   double_val  = 1.0;



  typedef struct {

    char     char_val;

    int32_t  int_val;

    float    float_val;

    double   double_val;

  } Ex2Struct;



  Ex2Struct struct_val = { '0', 1, 1.0, 1.0 };



  PrintBytes(&char_val, sizeof(char));

  PrintBytes(&int_val, sizeof(int32_t));

  PrintBytes(&float_val, sizeof(float));

  PrintBytes(&double_val, sizeof(double));

  PrintBytes(&struct_val, sizeof(struct_val));



  return EXIT_SUCCESS;

}
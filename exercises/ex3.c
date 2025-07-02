/*
Jisung Lee
jisung@uw.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t z;  
} Point3d;

// allocates and initializes a Point3d
Point3d* AllocatePoint3d(uint16_t x, uint16_t y, uint16_t z) {
  Point3d* pt = (Point3d*) malloc (sizeof(Point3d));
  if (pt != NULL) {
    pt->x = x;
    pt->y = y;
    pt->z = z;
  }
  return pt;
}

// check allocation
int main(int argc, char **argv) {
  uint16_t x = 1;
  uint16_t y = 2;
  uint16_t z = 3;

  Point3d* pt = AllocatePoint3d(x, y, z);

  // check if allocation worked
  if (pt == NULL) {
    fprintf(stderr, "Allocation failed\n");
    return 1;
  }

  // check that values are correct
  if (pt->x != x || pt->y != y || pt->z != z) {
    fprintf(stderr, "Point coordinates are not intiialized correctly\n");
    free(pt);
    return 2;
  }

  free(pt);
  
  //success
  return 0;
}
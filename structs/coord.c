#include "coord.h"

struct Coordinate new_coord(int x, int y, int z) {
  coordinate_t coord = {.x = x, .y = y, .z = z};

  return coord;
}

struct Coordinate scale_coordinate(struct Coordinate coord, int factor) {
  coordinate_t scaled = coord;
  scaled.x *= factor;
  scaled.y *= factor;
  scaled.z *= factor;

  return scaled;
}

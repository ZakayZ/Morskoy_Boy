#include "includes.h"

Field::Field(size_t horizontal_size, size_t vertical_size) : x_size_(horizontal_size), y_size_(vertical_size) {}

bool Field::IsValidCoord(const Coords& coords) const {
  return coords.x < x_size_ && coords.y < y_size_;
}

bool Field::IsValidBox(const BoundaryBox& box) const {
  auto borders = box.GetCoords();
  return IsValidCoord(borders.first) && IsValidCoord(borders.second);
}

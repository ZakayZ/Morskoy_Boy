#include "includes.h"
#include "Field.h"

Field::Field(size_t horizontal_size, size_t vertical_size)
    : x_size_(horizontal_size), y_size_(vertical_size), grid_(horizontal_size, vector<Cell>(vertical_size)) {}

const vector<vector<Field::Cell>>& Field::GetGrid() const {
  return grid_;
}

bool Field::IsValidCoord(const Coords& coords) const {
  return coords.x < x_size_ && coords.y < y_size_;
}

bool Field::IsValidBox(const BoundaryBox& box) const {
  auto borders = box.GetCoords();
  return IsValidCoord(borders.first) && IsValidCoord(borders.second);
}

void Field::TickEffects() {
  /// ticks all the internal counters in the end of a turn
}

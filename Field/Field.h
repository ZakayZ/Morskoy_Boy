#pragma once

#include "../Coords//Coords.h"
#include "../Ships/BoundaryBox.h"
#include "Field.h"
#include <vector>

using std::vector;

class Field {
 public:
  Field() = default;
  Field(size_t, size_t);
  [[nodiscard]] bool IsValidCoord(const Coords&) const;
  [[nodiscard]] bool IsValidBox(const BoundaryBox&) const;
  ~Field() = default;
 private:
  struct Cell {
    bool placeholder = false;
  };

  size_t x_size_;
  size_t y_size_;
  vector<vector<Cell>> grid_;
};

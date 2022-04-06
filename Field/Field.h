#pragma once

#include "../includes.h"

class Field {
 public:
  struct Cell;
  Field() = default;
  Field(size_t, size_t);
  [[nodiscard]] const vector<vector<Cell>>& GetGrid() const;
  [[nodiscard]] bool IsValidCoord(const Coords&) const;
  [[nodiscard]] bool IsValidBox(const BoundaryBox&) const;
  void TickEffects();
  ~Field() = default;
 private:

  size_t x_size_;
  size_t y_size_;
  vector<vector<Cell>> grid_;
};

struct Field::Cell {
  bool placeholder = false;
};
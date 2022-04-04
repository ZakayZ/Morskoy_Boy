#pragma once

#include "../includes.h"

class Field {
 public:
  Field() = default;
  Field(size_t, size_t);
  [[nodiscard]] bool IsValidCoord(const Coords&) const;
  [[nodiscard]] bool IsValidBox(const BoundaryBox&) const;
  void Display(sf::RenderWindow&, const Coords&, bool) const;
  ~Field() = default;
 private:
  struct Cell {
    bool placeholder = false;
  };

  size_t x_size_;
  size_t y_size_;
  vector<vector<Cell>> grid_;
};

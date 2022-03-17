#pragma once

#ifndef SHIPS_MORSKOY_BOY_FIELD_FIELD_H_
#define SHIPS_MORSKOY_BOY_FIELD_FIELD_H_

#include "../includes.h"

class Field {
 public:
  Field() = default;
  Field(size_t, size_t);
  [[nodiscard]] bool IsValidCoord(const Coords&) const;
  [[nodiscard]] bool IsValidBox(const BoundaryBox&) const;
  ~Field() = default;
 private:
  struct Cell {

  }

  size_t x_size_;
  size_t y_size_;
  vector<vector<>>
};

#endif //SHIPS_MORSKOY_BOY_FIELD_FIELD_H_

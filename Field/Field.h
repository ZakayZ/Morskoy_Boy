#pragma once

#include "../includes.h"

#ifndef SHIPS_MORSKOY_BOY_FIELD_FIELD_H_
#define SHIPS_MORSKOY_BOY_FIELD_FIELD_H_

class Field {
 public:
  Field() = delete;
  Field(size_t, size_t);
  bool IsValidBox(const Ship::BoundaryBox&) const;
  ~Field() = default;
 private:
  size_t x_size_;
  size_t y_size_;
};

#endif //SHIPS_MORSKOY_BOY_FIELD_FIELD_H_

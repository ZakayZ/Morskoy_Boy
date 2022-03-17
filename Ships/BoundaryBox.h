#pragma once

#ifndef MORSKOY_BOY_MORSKOY_BOY_SHIPS_BOUNDARYBOX_H_
#define MORSKOY_BOY_MORSKOY_BOY_SHIPS_BOUNDARYBOX_H_

#include "../includes.h"

class BoundaryBox {
 public:
  BoundaryBox() = default;
  BoundaryBox(const BoundaryBox&) = default;
  BoundaryBox(const Coords&, const Coords&);
  BoundaryBox& operator=(const BoundaryBox&) = default;
  [[nodiscard]] std::pair<Coords, Coords> GetCoords() const;
  [[nodiscard]] bool IsHit(const Coords&) const;
  [[nodiscard]] size_t WhereHit(const Coords&) const;
  [[nodiscard]] bool IsIntersect(const BoundaryBox&) const;
  void RotateAround(const Coords&, bool);
  void Move(size_t, bool);
  ~BoundaryBox() = default;
 private:
  enum class FacingDirection {
    kUp,
    kDown,
    kLeft,
    kRight,
  };

  [[nodiscard]] FacingDirection GetFacingDirection() const;

  Coords left_corner_;
  Coords right_corner_;
};


#endif //MORSKOY_BOY_MORSKOY_BOY_SHIPS_BOUNDARYBOX_H_

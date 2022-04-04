#pragma once

#include "../includes.h"

class BoundaryBox {
 public:
  enum class FacingDirection {
    kUp,
    kDown,
    kLeft,
    kRight,
  };

  BoundaryBox() = default;
  BoundaryBox(const BoundaryBox&) = default;
  BoundaryBox(const Coords&, const Coords&);
  BoundaryBox& operator=(const BoundaryBox&) = default;
  [[nodiscard]] std::pair<Coords, Coords> GetCoords() const;
  [[nodiscard]] Coords GetLeftUpperCorner() const;
  [[nodiscard]] size_t GetLength() const;
  [[nodiscard]] size_t GetWidth() const;
  [[nodiscard]] FacingDirection GetFacingDirection() const;
  [[nodiscard]] bool IsHit(const Coords&) const;
  [[nodiscard]] size_t WhereHit(const Coords&) const;
  [[nodiscard]] bool IsIntersect(const BoundaryBox&) const;
  void Translate(const Coords&);
  void RotateAround(const Coords&, bool);
  void Move(size_t, bool);
  ~BoundaryBox() = default;
 private:
  Coords left_corner_;
  Coords right_corner_;
};

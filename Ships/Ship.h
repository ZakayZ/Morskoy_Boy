#pragma once

#include "../includes.h"

#ifndef SHIPS_MORSKOY_BOY_SHIP_H_
#define SHIPS_MORSKOY_BOY_SHIP_H_

class Ship {
 public:
  class BoundaryBox {
   public:
    BoundaryBox() = delete;
    BoundaryBox(const BoundaryBox&) = default;
    BoundaryBox(const Coords&, const Coords&);
    BoundaryBox& operator=(const BoundaryBox&) = default;
    std::pair<Coords, Coords> GetCoords() const;
    bool IsHit(const Coords&) const;
    size_t WhereHit(const Coords&) const;
    bool IsIntersect(const BoundaryBox&) const;
    void RotateAround(const Coords&);
    void MoveForward(size_t);
    ~BoundaryBox() = default;
   private:
    Coords left_corner_;
    Coords right_corner_;
  };

  Ship() = delete;
  Ship(const Coords&);
  BoundaryBox GetPosition() const;
  std::shared_ptr<Projectile> Fire(const Coords&);
  bool IsHit(const Coords&);
  void ReceiveDamage(const Coords&);
  bool IsDead() const;
  ~Ship() = default;
 private:
  class Hull {
   public:
    Hull() = delete;
    Hull(const Hull&) = default;
    Hull& operator=(const Hull&) = default;
    Hull(size_t);
    bool IsDead() const;
    void GetHit(size_t);
    ~Hull() = default;
   private:
    size_t hit_points_;
  };

  BoundaryBox ship_box_;
  vector<Hull> hull_;
  Weapon weapon_;
  bool is_dead_;
};

#endif //SHIPS_MORSKOY_BOY_SHIP_H_

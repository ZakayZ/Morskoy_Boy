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

  Ship() = delete;
  Ship(const Coords&);
  [[nodiscard]] BoundaryBox GetPosition() const;
  [[nodiscard]] bool IsReadyFire() const;
  std::shared_ptr<Projectile> Fire(const Coords&);
  void Move(size_t, bool);
  void Rotate(const Coords&, bool);
  [[nodiscard]] bool IsHit(const Coords&) const;
  [[nodiscard]] bool IsIntersect(const BoundaryBox&) const;
  void ReceiveDamage(const Coords&, size_t);
  void Reload();
  [[nodiscard]] bool IsDead() const;
  ~Ship() = default;
 private:
  class Hull {
   public:
    Hull() = delete;
    Hull(const Hull&) = default;
    Hull& operator=(const Hull&) = default;
    explicit Hull(size_t);
    [[nodiscard]] bool IsDead() const;
    void GetHit(size_t);
    ~Hull() = default;
   private:
    size_t hit_points_;
  };

  BoundaryBox ship_box_;
  vector<Hull> hull_;
  std::unique_ptr<Weapon> weapon_;
  bool is_dead_;
};

#endif //SHIPS_MORSKOY_BOY_SHIP_H_

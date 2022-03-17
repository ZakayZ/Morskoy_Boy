#pragma once

#ifndef SHIPS_MORSKOY_BOY_SHIP_H_
#define SHIPS_MORSKOY_BOY_SHIP_H_

#include "../includes.h"

class Ship {
 public:
  Ship() = default;
  //Ship(const Coords&);
  [[nodiscard]] BoundaryBox GetPosition() const;
  [[nodiscard]] bool IsReadyFire() const;
  [[nodiscard]] bool IsHit(const Coords&) const;
  [[nodiscard]] bool IsIntersect(const BoundaryBox&) const;
  [[nodiscard]] std::shared_ptr<Projectile> Fire(const Coords&);
  void Move(size_t, bool);
  void Rotate(const Coords&, bool);
  void Mark(size_t);
  void ReceiveDamage(const Coords&, size_t);
  void TickEffects();
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

  void Reload();

  BoundaryBox ship_box_;
  vector<Hull> hull_;
  std::unique_ptr<Weapon> weapon_;
  size_t marked_for_;
  bool is_dead_;
};

#endif //SHIPS_MORSKOY_BOY_SHIP_H_

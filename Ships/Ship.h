#pragma once

#include "BoundaryBox.h"
#include "../Weapons/Weapon.h"
#include "../Weapons/Projectile.h"
#include <vector>

using std::vector;

class Ship {
 public:
  Ship() = delete;
  Ship(const BoundaryBox&, const vector<size_t>&, const std::shared_ptr<Weapon>&&);
  [[nodiscard]] BoundaryBox GetPosition() const;
  [[nodiscard]] bool IsReadyFire() const;
  [[nodiscard]] bool IsHit(const Coords&) const;
  [[nodiscard]] bool IsIntersect(const BoundaryBox&) const;
  [[nodiscard]] std::shared_ptr<Projectile> Fire(const Coords&);
  void Translate(const Coords&);
  void Move(size_t, bool);
  void Rotate(const Coords&, bool);
  void Mark(const Coords&, size_t);
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
  std::shared_ptr<Weapon> weapon_;
  size_t marked_for_;
  bool is_dead_;
};
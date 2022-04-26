#pragma once

#include "Projectile.h"
#include "WeaponTypes.h"
#include <memory>

class Weapon {
 public:
  explicit Weapon(WeaponType type);
  virtual std::shared_ptr<Projectile> Fire(Coords cord) = 0;
  void Reload();
  [[nodiscard]] bool IsReadyToFire() const;
  [[nodiscard]] WeaponType GetType() const;
 protected:
  WeaponType type_;
  size_t reload_counter_ = 0;
};

class Gun : public Weapon {
 public:
  Gun();
  std::shared_ptr<Projectile> Fire(Coords cord) override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload_;
};

class Mortar : public Weapon {
 public:
  Mortar();
  std::shared_ptr<Projectile> Fire(Coords cord) override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload_;
};

class FlareGun : public Weapon {
 public:
  FlareGun();
  std::shared_ptr<Projectile> Fire(Coords cord) override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload_;
};

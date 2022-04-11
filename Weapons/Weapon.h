#pragma once

#include "Projectile.h"
#include <memory>

class Weapon {
 public:
  virtual std::shared_ptr<Projectile> Fire(Coords cord) = 0;
  void Reload();
  [[nodiscard]] bool IsReadyToFire() const;
 protected:
  size_t reload_counter_ = 0;
};

class Gun : public Weapon {
 public:
  std::shared_ptr<Projectile> Fire(Coords cord) override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload_;
};

class Mortar : public Weapon {
 public:
  std::shared_ptr<Projectile> Fire(Coords cord) override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload_;
};

class FlareGun : public Weapon {
 public:
  std::shared_ptr<Projectile> Fire(Coords cord) override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload_;
};

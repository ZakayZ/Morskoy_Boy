#pragma once

#include "../Coords/Coords.h"
#include <vector>

using std::vector;

enum class ProjectileTypes {
  kDefault,
  kFlare,
};

class Projectile {
 public:
  Projectile(Coords cord, size_t time_to_fly);
  virtual ProjectileTypes GetType() = 0;
  void DecreaseTimeToFly();
  [[nodiscard]] bool IsReadyToLand() const;
  Coords GetLandingCords();
 protected:
  size_t current_time_to_fly_;
  Coords landing_cords_;
};

class DefaultProjectile : public Projectile {
 public:
  DefaultProjectile(Coords cord, size_t time_to_fly);
  virtual const vector<std::vector<uint64_t>>& GetDamageKernel() = 0;
  ProjectileTypes GetType() override;
 private:
};

class GunProjectile : public DefaultProjectile {
 public:
  GunProjectile(Coords cord, size_t time_to_fly);
  const vector<std::vector<uint64_t>>& GetDamageKernel() override;
 private:
  static const std::vector<vector<uint64_t>> kDamageKernel_;
};

class MortarProjectile : public DefaultProjectile {
 public:
  MortarProjectile(Coords cord, size_t time_to_fly);
  const vector<std::vector<uint64_t>>& GetDamageKernel() override;
 private:
  static const std::vector<vector<uint64_t>> kDamageKernel_;
};

class Flare : public Projectile {
 public:
  Flare(Coords cords, size_t time_to_fly);
  const std::vector<std::vector<bool>>& GetShowKernel();
 private:
  static const size_t show_time_;
  static const std::vector<vector<bool>> kShowKernel_;
};

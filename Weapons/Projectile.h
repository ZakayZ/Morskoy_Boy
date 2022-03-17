#pragma once

#include "../includes.h"

#ifndef MORSKOY_BOY_WEAPONS_PROJECTILE_H_
#define MORSKOY_BOY_WEAPONS_PROJECTILE_H_

enum class ProjectileTypes {
  kDefault,
  kGun,
  kMortar,
  kFlare,
};

class Projectile {
 public:
  Projectile(Coords cord, size_t time_to_fly);
  virtual ProjectileTypes GetType() = 0;
  void DecreaseTimeToFly();
  bool IsReadyToLand() const;
  Coords GetLandingCords();
 private:
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

//class Flare : Projectile {
//  static const std::vector<vector<bool>> kShowKernel_;
//};


#endif //MORSKOY_BOY_WEAPONS_PROJECTILE_H_

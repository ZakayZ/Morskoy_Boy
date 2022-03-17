#pragma once

#include "../includes.h"

#ifndef SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_
#define SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_

class Weapon {
 public:
  virtual std::shared_ptr<Projectile> Fire(Coords cord) = 0;
  void Reload();
  bool IsReadyToFire();
 private:
  size_t reload_counter_ = 0;
};

class Gun : public Weapon {
 public:
  std::shared_ptr<Projectile> Fire(Coords cord) override;
 private:
  static const size_t kTimeTyFly_;
  static const size_t kTimeToReload_;
};

class Mortar : public Weapon {
 public:
  std::shared_ptr<Projectile> Fire(Coords cord) override;
 private:
  static const size_t kTimeTyFly_;
  static const size_t kTimeToReload;
};

//class FlareGun : Weapon {
// public:
//  std::shared_ptr<Projectile> Fire(Coords cord) override;
// private:
//  static const size_t kTimeTyFly_;
//  static const size_t kTimeToReload;
//};

#endif //SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_

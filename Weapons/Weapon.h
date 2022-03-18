#pragma once

#include "../includes.h"

#ifndef SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_
#define SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_

class Weapon {
 public:
  virtual std::shared_ptr<Projectile> Fire(Coords cord) = 0;
  virtual void Display(sf::RenderWindow&, const Coords&) const = 0;
  void Reload();
  [[nodiscard]] bool IsReadyToFire() const;
 protected:
  size_t reload_counter_ = 0;
};

class Gun : public Weapon {
 public:
  std::shared_ptr<Projectile> Fire(Coords cord) override;
  void Display(sf::RenderWindow&, const Coords&) const override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload_;
};

class Mortar : public Weapon {
 public:
  std::shared_ptr<Projectile> Fire(Coords cord) override;
  void Display(sf::RenderWindow&, const Coords&) const override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload;
};

class FlareGun : public Weapon {
 public:
  std::shared_ptr<Projectile> Fire(Coords cord) override;
  void Display(sf::RenderWindow&, const Coords&) const override;
 private:
  static const size_t kTimeToFly_;
  static const size_t kTimeToReload_;
};

#endif //SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_

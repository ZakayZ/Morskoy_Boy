#include "includes.h"

void Weapon::Reload() {
  --reload_counter_;
}

bool Weapon::IsReadyToFire() const {
  return reload_counter_ == 0;
}

std::shared_ptr<Projectile> Gun::Fire(Coords cord) {
  auto ptr = std::make_shared<GunProjectile>(cord, kTimeToFly_);
  return ptr;
}

const size_t Gun::kTimeToFly_ = 1;

const size_t Gun::kTimeToReload_ = 1;

std::shared_ptr<Projectile> Mortar::Fire(Coords cord) {
  return std::make_shared<MortarProjectile>(cord, kTimeToFly_);
}

const size_t Mortar::kTimeToFly_ = 2;

const size_t Mortar::kTimeToReload = 2;

std::shared_ptr<Projectile> FlareGun::Fire(Coords cord) {
  return std::make_shared<MortarProjectile>(cord, kTimeToFly_);
}

const size_t FlareGun::kTimeToFly_ = 3;

const size_t FlareGun::kTimeToReload_ = 3;

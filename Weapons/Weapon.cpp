#include "Weapon.h"

void Weapon::Reload() {
  --reload_counter_;
}

bool Weapon::IsReadyToFire() {
  return reload_counter_ == 0;
}

std::shared_ptr<Projectile> Gun::Fire(Coords cord) {
  auto ptr = std::make_shared<GunProjectile>(cord, kTimeTyFly_);
  return ptr;
}

const size_t Gun::kTimeTyFly_ = 1;

const size_t Gun::kTimeToReload_ = 1;

std::shared_ptr<Projectile> Mortar::Fire(Coords cord) {
  return std::make_shared<MortarProjectile>(cord, kTimeTyFly_);
}

const size_t Mortar::kTimeTyFly_ = 2;

const size_t Mortar::kTimeToReload = 2;

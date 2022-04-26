#include "Weapon.h"

Weapon::Weapon(WeaponType type) : type_(type) {}

void Weapon::Reload() {
  if (reload_counter_ > 0) {
    --reload_counter_;
  }
}

bool Weapon::IsReadyToFire() const {
  return reload_counter_ == 0;
}

WeaponType Weapon::GetType() const {
  return type_;
}

Gun::Gun() : Weapon(WeaponType::Gun) {}

std::shared_ptr<Projectile> Gun::Fire(Coords cord) {
  reload_counter_ = kTimeToReload_;
  auto ptr = std::make_shared<GunProjectile>(cord, kTimeToFly_);
  return ptr;
}

const size_t Gun::kTimeToFly_ = 1;

const size_t Gun::kTimeToReload_ = 1;

Mortar::Mortar() : Weapon(WeaponType::Mortar) {}

std::shared_ptr<Projectile> Mortar::Fire(Coords cord) {
  reload_counter_ = kTimeToReload_;
  return std::make_shared<MortarProjectile>(cord, kTimeToFly_);
}

const size_t Mortar::kTimeToFly_ = 2;

const size_t Mortar::kTimeToReload_ = 2;

FlareGun::FlareGun() : Weapon(WeaponType::FlareGun) {}

std::shared_ptr<Projectile> FlareGun::Fire(Coords cord) {
  reload_counter_ = kTimeToReload_;
  return std::make_shared<MortarProjectile>(cord, kTimeToFly_);
}

const size_t FlareGun::kTimeToFly_ = 3;

const size_t FlareGun::kTimeToReload_ = 3;
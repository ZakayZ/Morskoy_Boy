#include "Projectile.h"

Projectile::Projectile(Coords cord, size_t time_to_fly) : landing_cords_(cord), current_time_to_fly_(time_to_fly) {}

void Projectile::DecreaseTimeToFly() {
  --current_time_to_fly_;
}

bool Projectile::IsReadyToLand() const {
  return current_time_to_fly_ == 0;
}

DefaultProjectile::DefaultProjectile(Coords cord, size_t time_to_fly) : Projectile(cord, time_to_fly) {}

ProjectileTypes DefaultProjectile::GetType() {
  return ProjectileTypes::kDefault;
}

GunProjectile::GunProjectile(Coords cord, size_t time_to_fly) : DefaultProjectile(cord, time_to_fly) {}

const std::vector<std::vector<uint64_t>> GunProjectile::kDamageKernel_ = {{0, 1, 0},
                                                                          {1, 1, 1},
                                                                          {0, 1, 0}};

const vector<std::vector<uint64_t>>& GunProjectile::GetDamageKernel() {
  return kDamageKernel_;
}

MortarProjectile::MortarProjectile(Coords cord, size_t time_to_fly) : DefaultProjectile(cord, time_to_fly) {}

const std::vector<vector<uint64_t>> MortarProjectile::kDamageKernel_ = {{0, 0, 1, 0, 0},
                                                                        {0, 1, 1, 1, 0},
                                                                        {1, 1, 1, 1, 1},
                                                                        {0, 1, 1, 1, 0},
                                                                        {0, 0, 1, 0, 0}};

const vector<std::vector<uint64_t>>& MortarProjectile::GetDamageKernel() {
  return kDamageKernel_;
}

//const std::vector<vector<bool>> kShowKernel_ = {{0, 0, 1, 0, 0},
//                                                {0, 1, 1, 1, 0},
//                                                {1, 1, 1, 1, 1},
//                                                {0, 1, 1, 1, 0},
//                                                {0, 0, 1, 0, 0}};


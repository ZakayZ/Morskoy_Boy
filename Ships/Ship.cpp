#include "Ship.h"

Ship::Ship(ShipType type,
           const BoundaryBox& box,
           const vector<size_t>& hull_health,
           const std::shared_ptr<Weapon>&& weapon)
    : type_(type), ship_box_(box), hull_(), weapon_(weapon), marked_for_(0), is_dead_(false) {
  for (auto health : hull_health) {
    hull_.emplace_back(Hull(health));
  }
}

const vector<Ship::Hull>& Ship::GetHull() const {
  return hull_;
}

BoundaryBox Ship::GetPosition() const {
  return ship_box_;
}

size_t Ship::GetMark() const {
  return marked_for_;
}

ShipType Ship::GetType() const {
  return type_;
}

const std::shared_ptr<Weapon> Ship::GetWeapon() const {
  return weapon_;
}

bool Ship::IsReadyFire() const {
  return weapon_->IsReadyToFire();
}

std::shared_ptr<Projectile> Ship::Fire(const Coords& where) {
  return weapon_->Fire(where);
}

void Ship::Move(size_t delta, bool forward) {
  ship_box_.Move(delta, forward);
}

void Ship::Rotate(const Coords& pivot, bool clockwise) {
  ship_box_.RotateAround(pivot, clockwise);
}

void Ship::Mark(const Coords&, size_t marked_for) {
  marked_for_ = marked_for;
}

bool Ship::IsHit(const Coords& coords) const {
  return ship_box_.IsHit(coords);
}

bool Ship::IsIntersect(const BoundaryBox& box) const {
  return ship_box_.IsIntersect(box);
}

void Ship::ReceiveDamage(const Coords& coords, size_t damage) {
  size_t hull_hit = ship_box_.WhereHit(coords);
  hull_[hull_hit].GetHit(damage);
  if (hull_[hull_hit].IsDead()) {
    is_dead_ = true;
  }
}

void Ship::TickEffects() {
  if (marked_for_ > 0) {
    --marked_for_;
  }
  weapon_->Reload();
}

bool Ship::IsDead() const {
  return is_dead_;
}

Ship::Hull::Hull(size_t hit_points) : hit_points_(hit_points) {}

bool Ship::Hull::IsDead() const {
  return hit_points_ == 0;
}

void Ship::Hull::GetHit(size_t damage) {
  if (damage > hit_points_) {
    damage = hit_points_;
  }
  hit_points_ -= damage;
}

void Ship::Reload() {
  if (!weapon_->IsReadyToFire()) {
    weapon_->Reload();
  }
}

void Ship::Translate(const Coords& delta) {
  ship_box_.Translate(delta);
}
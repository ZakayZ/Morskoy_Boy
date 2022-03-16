#include "Player.h"

size_t Player::GetShipId(const Coords& coords) const {
  for (size_t i = 0; i < fleet_.size(); ++i) {
    if (fleet_[i].IsHit(coords)) {
      return i;
    }
  }
  return fleet_.size();
}

Error Player::IsValidId(size_t index) const {
  if (index >= fleet_.size()) {
    return Error::kInvalidShip;
  }
  if (fleet_[index].IsDead()) {
    return Error::kShipIsDead;
  }
  return Error::kNoError;
}

Error Player::IsValidFire(size_t index, const Coords& where) const {
  if (actions_left_ == 0) {
    return Error::kOutOfActions;
  }

  Error error = IsValidId(index);
  if (error != Error::kNoError) {
    return error;
  }

  if (!fleet_[index].IsReadyFire()) {
    return Error::kWeaponOnCooldown;
  }

  if (my_field_.IsValidCoord(where)) {
    return Error::kInvalidTarget;
  }

  return Error::kNoError;
}

std::shared_ptr<Projectile> Player::Fire(size_t index, const Coords& where) {
  return fleet_[index].Fire(where);
}

Error Player::IsValidMove(size_t index, size_t delta, bool forward) const {
  if (actions_left_ == 0) {
    return Error::kOutOfActions;
  }

  Error error = IsValidId(index);
  if (error != Error::kNoError) {
    return error;
  }

  auto box = fleet_[index].GetPosition();
  box.Move(delta, forward);
  if (!my_field_.IsValidBox(box)) {
    return Error::kIntersectsFieldBoundary;
  }

  for (size_t i = 0; i < fleet_.size(); ++i) {
    if (i != index && fleet_[i].IsIntersect(box)) {
      return Error::kIntersectsShip;
    }
  }

  return Error::kNoError;
}

void Player::Move(size_t index, size_t delta, bool forward) {
  fleet_[index].Move(delta, forward);
}

Error Player::IsValidRotate(size_t index, const Coords& pivot, bool clockwise) const {
  if (actions_left_ == 0) {
    return Error::kOutOfActions;
  }

  Error error = IsValidId(index);
  if (error != Error::kNoError) {
    return error;
  }

  auto box = fleet_[index].GetPosition();
  box.RotateAround(pivot, clockwise);
  if (!my_field_.IsValidBox(box)) {
    return Error::kIntersectsFieldBoundary;
  }

  for (size_t i = 0; i < fleet_.size(); ++i) {
    if (i != index && fleet_[i].IsIntersect(box)) {
      return Error::kIntersectsShip;
    }
  }

  return Error::kNoError;
}

void Player::Rotate(size_t index, const Coords& pivot, bool clockwise) {
  fleet_[index].Rotate(pivot, clockwise);
}

void Player::GetHit(std::shared_ptr<Projectile>& projectile) {
  hit_by_.push_back(projectile);
}

void Player::EndTurn() {
  for (auto& ship : fleet_) {
    if (!ship.IsDead()) {
      ship.Reload();
    }
  }
    ///TODO
}
#include "includes.h"
#include "Player.h"

Player::Player(size_t actions, const Coords& field_size, const vector<Ship>& fleet)
    : actions_left_(actions), my_field_(field_size.x, field_size.y), fleet_(fleet) {}

size_t Player::GetShipId(const Coords& coords) const {
  for (size_t i = 0; i < fleet_.size(); ++i) {
    if (fleet_[i].IsHit(coords)) {
      return i;
    }
  }
  return fleet_.size();
}

Error Player::IsValidCoords(const Coords& coords) const {
  size_t index = GetShipId(coords);
  if (index >= fleet_.size()) {
    return Error::kInvalidShip;
  }
  if (fleet_[index].IsDead()) {
    return Error::kShipIsDead;
  }
  return Error::kNoError;
}

Error Player::IsValidFire(const Coords& coords, const Coords& where) const {
  if (actions_left_ == 0) {
    return Error::kOutOfActions;
  }

  size_t index = GetShipId(coords);
  Error error = IsValidCoords(coords);
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

std::shared_ptr<Projectile> Player::Fire(const Coords& coords, const Coords& where) {
  size_t index = GetShipId(coords);
  --actions_left_;
  return fleet_[index].Fire(where);
}

Error Player::IsValidMove(const Coords& coords, size_t delta, bool forward) const {
  if (actions_left_ == 0) {
    return Error::kOutOfActions;
  }

  size_t index = GetShipId(coords);
  Error error = IsValidCoords(coords);
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

void Player::Display(sf::RenderWindow& window, const Coords& offset, bool my_view) const {
  my_field_.Display(window, offset, my_view);
  for (auto& ship : fleet_) {
    ship.Display(window, offset, my_view);
  }
}

void Player::Move(const Coords& coords, size_t delta, bool forward) {
  size_t index = GetShipId(coords);
  fleet_[index].Move(delta, forward);
  --actions_left_;
}

Error Player::IsValidRotate(const Coords& coords, const Coords& pivot, bool clockwise) const {
  if (actions_left_ == 0) {
    return Error::kOutOfActions;
  }

  size_t index = GetShipId(coords);
  Error error = IsValidCoords(coords);
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

void Player::Rotate(const Coords& coords, const Coords& pivot, bool clockwise) {
  size_t index = GetShipId(coords);
  fleet_[index].Rotate(pivot, clockwise);
  --actions_left_;
}

void Player::GetHit(std::shared_ptr<Projectile>& projectile) {
  hit_by_.push_back(projectile);
}

void Player::EndTurn() {
  for (auto& ship : fleet_) {
    if (!ship.IsDead()) {
      ship.TickEffects();
    }
  }

  for (ssize_t projectile = 0; projectile < hit_by_.size(); ++projectile) {
    hit_by_[projectile]->DecreaseTimeToFly();
    if (hit_by_[projectile]->IsReadyToLand()) {
      auto projectile_type = hit_by_[projectile]->GetType();
      switch (projectile_type) {
        case ProjectileTypes::kDefault: {
          HandleDefaultProjectile(std::dynamic_pointer_cast<DefaultProjectile>(hit_by_[projectile]));
          break;
        }
        case ProjectileTypes::kFlare: {
          HandleFlareProjectile(std::dynamic_pointer_cast<Flare>(hit_by_[projectile]));
          break;
        }
      }
      hit_by_.erase(hit_by_.begin() + projectile);
      --projectile;
    }
  }
  actions_left_ = 2; /// Temporary
}

template <class Handler, typename T>
void Player::ApplyHandler(const Coords& epicenter, const vector<vector<T>>& kernel) {
  Handler handler;
  for (size_t i = epicenter.x < kernel.size() / 2 ? 0 : epicenter.x - kernel.size() / 2;
       i <= epicenter.x + kernel.size() / 2; ++i) {
    for (size_t j = epicenter.y < kernel.size() / 2 ? 0 : epicenter.y - kernel.size() / 2;
         j <= epicenter.y + kernel.size() / 2; ++j) {
      Coords hit{i, j};
      for (auto& ship : fleet_) {
        if (ship.IsHit(hit)) {
          handler(ship, hit, kernel[i][j]);
        }
      }
    }
  }
}

void Player::HandleDefaultProjectile(const std::shared_ptr<DefaultProjectile>& projectile) {
  Coords epicenter = projectile->GetLandingCords();
  auto kernel = projectile->GetDamageKernel();
  ApplyHandler<DefaultHandler, uint64_t>(epicenter, kernel);
}

void Player::HandleFlareProjectile(const std::shared_ptr<Flare>& flare) {
  Coords epicenter = flare->GetLandingCords();
  auto kernel = flare->GetShowKernel();
  ApplyHandler<FlareHandler, bool>(epicenter, kernel);
}

void Player::DefaultHandler::operator()(Ship& ship, const Coords& hit, size_t damage) {
  ship.ReceiveDamage(hit, damage);
}

void Player::FlareHandler::operator()(Ship& ship, const Coords& hit, size_t duration) {
  ship.Mark(hit, duration);
}

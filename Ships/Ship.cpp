#include "Ship.h"

Ship::BoundaryBox::BoundaryBox(const Coords& left_corner, const Coords& right_corner)
    : left_corner_(left_corner), right_corner_(right_corner) {}

std::pair<Coords, Coords> Ship::BoundaryBox::GetCoords() const {
  return {left_corner_, right_corner_};
}

bool Ship::BoundaryBox::IsHit(const Coords& coords) const {
  return coords.x >= std::min(left_corner_.x, right_corner_.x) && coords.x <= std::max(left_corner_.x, right_corner_.x)
      && coords.y >= std::min(left_corner_.y, right_corner_.y) && coords.y <= std::max(left_corner_.y, right_corner_.y);
}

size_t Ship::BoundaryBox::WhereHit(const Coords& coords) const {
  FacingDirection facing = GetFacingDirection();
  switch (facing) {
    case FacingDirection::kUp: {
      return coords.y - left_corner_.y;
    }
    case FacingDirection::kDown: {
      return left_corner_.y - coords.y;
    }
    case FacingDirection::kLeft: {
      return coords.x - left_corner_.x;
    }
    case FacingDirection::kRight: {
      return left_corner_.x - coords.x;
    }
  }
}

bool Ship::BoundaryBox::IsIntersect(const Ship::BoundaryBox& other) const {
  return (std::max(std::min(left_corner_.x, right_corner_.x), std::min(other.left_corner_.x, other.right_corner_.x))
      <= std::min(std::max(left_corner_.x, right_corner_.x), std::max(other.left_corner_.x, other.right_corner_.x)))
      && (std::max(std::min(left_corner_.y, right_corner_.y), std::min(other.left_corner_.y, other.right_corner_.y))
          <= std::min(std::max(left_corner_.y, right_corner_.y),
                      std::max(other.left_corner_.y, other.right_corner_.y)));
}

void Ship::BoundaryBox::RotateAround(const Coords& pivot, bool clockwise) {
  FacingDirection facing = GetFacingDirection();
  Coords copy;
  switch (facing) {
    case FacingDirection::kUp: {
      if (clockwise) {
        copy = left_corner_;
        left_corner_.x = pivot.x - (pivot.y - copy.y);
        left_corner_.y = pivot.y - (copy.x - pivot.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + (copy.y - pivot.y);
        right_corner_.y = pivot.y + (pivot.x - copy.x);
      } else {
        copy = left_corner_;
        left_corner_.x = pivot.x + (pivot.y - copy.y);
        left_corner_.y = pivot.y + (copy.x - pivot.x);
        copy = right_corner_;
        right_corner_.x = pivot.x - (copy.y - pivot.y);
        right_corner_.y = pivot.y - (pivot.x - copy.x);
      }
      break;
    }
    case FacingDirection::kDown: {
      if (clockwise) {
        copy = left_corner_;
        left_corner_.x = pivot.x + (copy.y - pivot.y);
        left_corner_.y = pivot.y + (pivot.x - copy.x);
        copy = right_corner_;
        right_corner_.x = pivot.x - (pivot.y - copy.y);
        right_corner_.y = pivot.y - (copy.x - pivot.x);
      } else {
        copy = left_corner_;
        left_corner_.x = pivot.x - (copy.y - pivot.y);
        left_corner_.y = pivot.y - (pivot.x - copy.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + (pivot.y - copy.y);
        right_corner_.y = pivot.y + (copy.x - pivot.x);
      }
      break;
    }
    case FacingDirection::kLeft: {
      if (clockwise) {
        copy = left_corner_;
        left_corner_.x = pivot.x - (copy.y - pivot.y);
        left_corner_.y = pivot.y - (copy.x - pivot.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + (pivot.y - copy.y);
        right_corner_.y = pivot.y + (pivot.x - copy.x);
      } else {
        copy = left_corner_;
        left_corner_.x = pivot.x + (copy.y - pivot.y);
        left_corner_.y = pivot.y + (copy.x - pivot.x);
        copy = right_corner_;
        right_corner_.x = pivot.x - (pivot.y - copy.y);
        right_corner_.y = pivot.y - (pivot.x - copy.x);
      }
      break;
    }
    case FacingDirection::kRight: {
      if (clockwise) {
        copy = left_corner_;
        left_corner_.x = pivot.x + (pivot.y - copy.y);
        left_corner_.y = pivot.y + (pivot.x - copy.x);
        copy = right_corner_;
        right_corner_.x = pivot.x - (copy.y - pivot.y);
        right_corner_.y = pivot.y - (copy.x - pivot.x);
      } else {
        copy = left_corner_;
        left_corner_.x = pivot.x - (pivot.y - copy.y);
        left_corner_.y = pivot.y - (pivot.x - copy.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + (copy.y - pivot.y);
        right_corner_.y = pivot.y + (copy.x - pivot.x);
      }
      break;
    }
  }
}

void Ship::BoundaryBox::Move(size_t delta, bool forward) {
  FacingDirection facing = GetFacingDirection();
  switch (facing) {
    case FacingDirection::kUp: {
      if (forward) {
        right_corner_.y += delta;
        left_corner_.y += delta;
      } else {
        right_corner_.y -= delta;
        left_corner_.y -= delta;
      }
      break;
    }
    case FacingDirection::kDown: {
      if (forward) {
        right_corner_.y -= delta;
        left_corner_.y -= delta;
      } else {
        right_corner_.y += delta;
        left_corner_.y += delta;
      }
      break;
    }
    case FacingDirection::kLeft: {
      if (forward) {
        right_corner_.x -= delta;
        left_corner_.x -= delta;
      } else {
        right_corner_.x += delta;
        left_corner_.x += delta;
      }
      break;
    }
    case FacingDirection::kRight: {
      if (forward) {
        right_corner_.x += delta;
        left_corner_.x += delta;
      } else {
        right_corner_.x -= delta;
        left_corner_.x -= delta;
      }
      break;
    }
  }
}

Ship::BoundaryBox::FacingDirection Ship::BoundaryBox::GetFacingDirection() const {
  if (left_corner_.x <= right_corner_.x && left_corner_.y <= right_corner_.y) {
    return FacingDirection::kRight;
  }

  if (left_corner_.x >= right_corner_.x && left_corner_.y >= right_corner_.y) {
    return FacingDirection::kLeft;
  }

  if (left_corner_.x <= right_corner_.x && left_corner_.y >= right_corner_.y) {
    return FacingDirection::kDown;
  }

  if (left_corner_.x >= right_corner_.x && left_corner_.y <= right_corner_.y) {
    return FacingDirection::kUp;
  }
}

Ship::BoundaryBox Ship::GetPosition() const {
  return ship_box_;
}

bool Ship::IsReadyFire() const {
  return weapon_.IsReadyToFire();
}

std::shared_ptr<Projectile> Ship::Fire(const Coords& where) {
  return weapon_.Fire(where);
}

void Ship::Move(size_t delta, bool forward) {
  ship_box_.Move(delta, forward);
}

void Ship::Rotate(const Coords& pivot, bool clockwise) {
  ship_box_.RotateAround(pivot, clockwise);
}

bool Ship::IsHit(const Coords& coords) const {
  return ship_box_.IsHit(coords);
}

bool Ship::IsIntersect(const Ship::BoundaryBox& box) const {
  return ship_box_.IsIntersect(box);
}

void Ship::ReceiveDamage(const Coords& coords, size_t damage) {
  size_t hull_hit = ship_box_.WhereHit(coords);
  hull_[hull_hit].GetHit(damage);
  if (hull_[hull_hit].IsDead()) {
    is_dead_ = true;
  }
}

void Ship::Reload() {
  if (!weapon_.IsReadyToFire()) {
    weapon_.Reload();
  }
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

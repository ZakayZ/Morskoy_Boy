#include "BoundaryBox.h"

BoundaryBox::BoundaryBox(const Coords& left_corner, const Coords& right_corner)
    : left_corner_(left_corner), right_corner_(right_corner) {}

pair<Coords, Coords> BoundaryBox::GetCoords() const {
  return {left_corner_, right_corner_};
}

Coords BoundaryBox::GetLeftUpperCorner() const {
  switch (GetFacingDirection()) {
    case FacingDirection::kUp: { return right_corner_; }
    case FacingDirection::kDown: { return left_corner_; }
    case FacingDirection::kLeft: { return {right_corner_.x, left_corner_.y}; }
    case FacingDirection::kRight: { return {left_corner_.x, right_corner_.y}; }
  }
}

sf::Vector2f BoundaryBox::GetCenter() const {
  return {float(left_corner_.x + right_corner_.x) / 2.f, float(left_corner_.y + right_corner_.y) / 2.f};
}

size_t BoundaryBox::GetLength() const {
  switch (GetFacingDirection()) {
    case FacingDirection::kUp: { return right_corner_.y - left_corner_.y; }
    case FacingDirection::kDown: { return left_corner_.y - right_corner_.y; }
    case FacingDirection::kLeft: { return left_corner_.x - right_corner_.x; }
    case FacingDirection::kRight: { return right_corner_.x - left_corner_.x; }
  }
}

size_t BoundaryBox::GetWidth() const {
  switch (GetFacingDirection()) {
    case FacingDirection::kUp: { return left_corner_.x - right_corner_.x; }
    case FacingDirection::kDown: { return right_corner_.x - left_corner_.x; }
    case FacingDirection::kLeft: { return right_corner_.y - left_corner_.y; }
    case FacingDirection::kRight: { return left_corner_.y - right_corner_.y; }
  }
}

bool BoundaryBox::IsHit(const Coords& coords) const {
  return coords.x >= std::min(left_corner_.x, right_corner_.x) && coords.x <= std::max(left_corner_.x, right_corner_.x)
      && coords.y >= std::min(left_corner_.y, right_corner_.y) && coords.y <= std::max(left_corner_.y, right_corner_.y);
}

size_t BoundaryBox::WhereHit(const Coords& coords) const {
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

bool BoundaryBox::IsIntersect(const BoundaryBox& other) const {
  return (std::max(std::min(left_corner_.x, right_corner_.x), std::min(other.left_corner_.x, other.right_corner_.x))
      <= std::min(std::max(left_corner_.x, right_corner_.x), std::max(other.left_corner_.x, other.right_corner_.x)))
      && (std::max(std::min(left_corner_.y, right_corner_.y), std::min(other.left_corner_.y, other.right_corner_.y))
          <= std::min(std::max(left_corner_.y, right_corner_.y),
                      std::max(other.left_corner_.y, other.right_corner_.y)));
}

void BoundaryBox::RotateAround(const Coords& pivot, bool clockwise) {
  FacingDirection facing = GetFacingDirection();
  switch (facing) {
    case FacingDirection::kUp: {
      if (clockwise) {
        Coords copy = left_corner_;
        left_corner_.x = pivot.x + 1 - (copy.y - pivot.y);
        left_corner_.y = pivot.y + (copy.x - pivot.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + 1 + (pivot.y - copy.y);
        right_corner_.y = pivot.y - (pivot.x - copy.x);
      } else {
        Coords copy = left_corner_;
        left_corner_.x = pivot.x + (copy.y - pivot.y);
        left_corner_.y = pivot.y + 1 - (copy.x - pivot.x);
        copy = right_corner_;
        right_corner_.x = pivot.x - (pivot.y - copy.y);
        right_corner_.y = pivot.y + 1 + (pivot.x - copy.x);
      }
      break;
    }
    case FacingDirection::kDown: {
      if (clockwise) {
        Coords copy = left_corner_;
        left_corner_.x = pivot.x + 1 + (pivot.y - copy.y);
        left_corner_.y = pivot.y - (pivot.x - copy.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + 1 - (copy.y - pivot.y);
        right_corner_.y = pivot.y + (copy.x - pivot.x);
      } else {
        Coords copy = left_corner_;
        left_corner_.x = pivot.x - (pivot.y - copy.y);
        left_corner_.y = pivot.y + 1 + (pivot.x - copy.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + (copy.y - pivot.y);
        right_corner_.y = pivot.y + 1 - (copy.x - pivot.x);
      }
      break;
    }
    case FacingDirection::kLeft: {
      if (clockwise) {
        Coords copy = left_corner_;
        left_corner_.x = pivot.x + 1 + (pivot.y - copy.y);
        left_corner_.y = pivot.y + (copy.x - pivot.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + 1 - (copy.y - pivot.y);
        right_corner_.y = pivot.y - (pivot.x - copy.x);
      } else {
        Coords copy = left_corner_;
        left_corner_.x = pivot.x - (pivot.y - copy.y);
        left_corner_.y = pivot.y + 1 - (copy.x - pivot.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + (copy.y - pivot.y);
        right_corner_.y = pivot.y + 1 + (pivot.x - copy.x);
      }
      break;
    }
    case FacingDirection::kRight: {
      if (clockwise) {
        Coords copy = left_corner_;
        left_corner_.x = pivot.x + 1 - (copy.y - pivot.y);
        left_corner_.y = pivot.y - (pivot.x - copy.x);
        copy = right_corner_;
        right_corner_.x = pivot.x + 1 + (pivot.y - copy.y);
        right_corner_.y = pivot.y + (copy.x - pivot.x);
      } else {
        Coords copy = left_corner_;
        left_corner_.x = pivot.x + (copy.y - pivot.y);
        left_corner_.y = pivot.y + 1 + (pivot.x - copy.x);
        copy = right_corner_;
        right_corner_.x = pivot.x - (pivot.y - copy.y);
        right_corner_.y = pivot.y + 1 - (copy.x - pivot.x);
      }
      break;
    }
  }
}

void BoundaryBox::Move(size_t delta, bool forward) {
  FacingDirection facing = GetFacingDirection();
  switch (facing) {
    case FacingDirection::kUp: {
      if (forward) {
        right_corner_.y -= delta;
        left_corner_.y -= delta;
      } else {
        right_corner_.y += delta;
        left_corner_.y += delta;
      }
      break;
    }
    case FacingDirection::kDown: {
      if (forward) {
        right_corner_.y += delta;
        left_corner_.y += delta;
      } else {
        right_corner_.y -= delta;
        left_corner_.y -= delta;
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

BoundaryBox::FacingDirection BoundaryBox::GetFacingDirection() const {
  if (left_corner_.x <= right_corner_.x && left_corner_.y >= right_corner_.y) {
    return FacingDirection::kRight;
  }

  if (left_corner_.x >= right_corner_.x && left_corner_.y <= right_corner_.y) {
    return FacingDirection::kLeft;
  }

  if (left_corner_.x <= right_corner_.x && left_corner_.y <= right_corner_.y) {
    return FacingDirection::kDown;
  } else {
    return FacingDirection::kUp;
  }
}

void BoundaryBox::Translate(int deltax, int deltay) {
  left_corner_.x += deltax;
  left_corner_.y += deltay;
  right_corner_.x += deltax;
  right_corner_.y += deltay;
}

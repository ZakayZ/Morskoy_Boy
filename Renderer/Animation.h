#include <vector>
#include "Coords/Coords.h"
#include <SFML/Graphics.hpp>

#include "AnimationType.h"

#pragma once

class Animation {
 public:
  Animation() = default;
  Animation(AnimationType type, const Coords& coords, size_t change_speed, size_t max_frame);
  ~Animation() = default;
  AnimationType GetType() const;
  size_t GetFrameIndex() const;
  Coords GetCenter() const;
  void AdvanceFrame();
  bool IsExpired() const;
  void Restart();

 private:
  AnimationType type_;
  Coords center_;
  size_t change_speed_;
  size_t frame_;
  size_t max_frame_;
};

#include "Animation.h"

Animation::Animation(AnimationType type, const Coords& center, size_t change_speed, size_t max_frame) :
    type_(type), center_(center), change_speed_(change_speed), frame_(0), max_frame_(max_frame) {}

AnimationType Animation::GetType() const {
  return type_;
}

size_t Animation::GetFrameIndex() const {
  return change_speed_ != 0 ? frame_ / change_speed_ : 0;
}

Coords Animation::GetCenter() const {
  return center_;
}

void Animation::AdvanceFrame() {
  ++frame_;
}

bool Animation::IsExpired() const {
  return change_speed_ != 0 && frame_ / change_speed_ >= max_frame_;
}

void Animation::Restart() {
  frame_ = 0;
}

#include "AnimationFactory.h"

Animation AnimationFactory::MakeBoomAnimation(const Coords& center) {
  return {AnimationType::kBoom, center, 5, 8};
}

#pragma once

#include "../includes.h"

#ifndef SHIPS_MORSKOY_BOY_ACTION_ACTION_H_
#define SHIPS_MORSKOY_BOY_ACTION_ACTION_H_

class Action {
 public:
  enum class ActionType {
    MoveForward,
    Fire,
    RotateClockwise,
    RotateCounterClockwise,
  };
  Action();

  ~Action();
 private:
  ActionType type_;
  size_t ship_index_;
};

#endif //SHIPS_MORSKOY_BOY_ACTION_ACTION_H_

#pragma once

#include "../Coords/Coords.h"

#ifndef SHIPS_MORSKOY_BOY_ACTION_ACTION_H_
#define SHIPS_MORSKOY_BOY_ACTION_ACTION_H_

enum class ActionType {
  Move,
  Fire,
  RotateClockwise,
  RotateCounterClockwise,
  EndTurn,
};

class Action {
 public:
  ActionType GetActionType();
  uint8_t GetPlayerNum();
 protected:
  ActionType action_type_;
  uint8_t player_;
};

class FireAction : public Action {
 public:
  FireAction(Coords firing_ship, Coords landing_cords, uint8_t player_);
 private:
  Coords firing_ship_cords_;
  Coords landing_cords_;
};

class MoveAction : public Action {
 public:
  MoveAction(Coords moving_ship, size_t distance);
 private:
  Coords moving_ship_cords_;
  size_t distance_;
};

class RotateClockwiseAction : public Action {
 public:
  explicit RotateClockwiseAction(Coords rotating_pivot);
 private:
  Coords pivot_;
};

class RotateCounterClockwiseAction : public Action {
 public:
  explicit RotateCounterClockwiseAction(Coords rotating_pivot);
 private:
  Coords pivot_;
};

class EndTurnAction : public Action {
 public:
  EndTurnAction() = default;
 private:
};

#endif //SHIPS_MORSKOY_BOY_ACTION_ACTION_H_

#include "includes.h"
#include "Action.h"

ActionType Action::GetActionType() {
  return action_type_;
}

uint8_t Action::GetPlayerNum() {
  return player_;
}

FireAction::FireAction(Coords firing_ship, Coords landing_cords, uint8_t player) {
  player_ = player;
  firing_ship_cords_ = firing_ship;
  landing_cords_ = landing_cords;
}

MoveAction::MoveAction(Coords moving_ship, size_t distance) {
  moving_ship_cords_ = moving_ship;
  distance_ = distance;
}

RotateCounterClockwiseAction::RotateCounterClockwiseAction(Coords rotating_pivot) {
  pivot_ = rotating_pivot;
}

RotateClockwiseAction::RotateClockwiseAction(Coords rotating_pivot) {
  pivot_ = rotating_pivot;
}

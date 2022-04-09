#include "Action.h"

ActionType Action::GetActionType() const {
  return action_type_;
}

uint8_t Action::GetPlayerNum()  const {
  return player_;
}

FireAction::FireAction(Coords firing_ship, Coords landing_cords, uint8_t player) {
  player_ = player;
  firing_ship_cords_ = firing_ship;
  landing_cords_ = landing_cords;
}

const Coords& FireAction::GetFiringShipCords() const {
  return firing_ship_cords_;
}
const Coords& FireAction::GetLandingCords() const {
  return landing_cords_;
}

MoveAction::MoveAction(Coords moving_ship, size_t distance) {
  moving_ship_cords_ = moving_ship;
  distance_ = distance;
}

const Coords& MoveAction::GetMovingShipCords() const {
  return moving_ship_cords_;
}

int MoveAction::GetDistance() const {
  return distance_;
}

RotateCounterClockwiseAction::RotateCounterClockwiseAction(Coords rotating_pivot) {
  pivot_ = rotating_pivot;
}
const Coords& RotateCounterClockwiseAction::GetPivot() const {
  return pivot_;
}

RotateClockwiseAction::RotateClockwiseAction(Coords rotating_pivot) {
  pivot_ = rotating_pivot;
}

const Coords& RotateClockwiseAction::GetPivot() const {
  return pivot_;
}

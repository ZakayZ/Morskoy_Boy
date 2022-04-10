#include "Action.h"

ActionType Action::GetActionType() const {
  return action_type_;
}

uint8_t Action::GetPlayerNum() const {
  return player_;
}

FireAction::FireAction(Coords firing_ship, Coords landing_cords, uint8_t player) {
  action_type_ = ActionType::Fire;
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

MoveAction::MoveAction(Coords moving_ship, int distance, uint8_t player) {
  action_type_ = ActionType::Move;
  player_ = player;
  moving_ship_cords_ = moving_ship;
  distance_ = distance;
}

const Coords& MoveAction::GetMovingShipCords() const {
  return moving_ship_cords_;
}

int MoveAction::GetDistance() const {
  return distance_;
}

RotateCounterClockwiseAction::RotateCounterClockwiseAction(Coords rotating_pivot, uint8_t player) {
  action_type_ = ActionType::RotateCounterClockwise;
  player_ = player;
  pivot_ = rotating_pivot;
}
const Coords& RotateCounterClockwiseAction::GetPivot() const {
  return pivot_;
}

RotateClockwiseAction::RotateClockwiseAction(Coords rotating_pivot, uint8_t player) {
  action_type_ = ActionType::RotateClockwise;
  player_ = player;
  pivot_ = rotating_pivot;
}

const Coords& RotateClockwiseAction::GetPivot() const {
  return pivot_;
}

EndTurnAction::EndTurnAction(uint8_t player) {
  action_type_ = ActionType::EndTurn;
  player_ = player;
}

ConstructShipAction::ConstructShipAction(ShipType ship_type, uint8_t player, Coords cords) {
  action_type_ = ActionType::ConstructShip;
  player_ = player;
  ship_type_ = ship_type;
  top_cords_ = cords;
}

ShipType ConstructShipAction::GetShipType() const {
  return ship_type_;
}
const Coords& ConstructShipAction::GetTopCords() const {
  return top_cords_;
}

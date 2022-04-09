#include "GameMaster.h"



Error GameMaster::CheckAction(const Action& action) const {
  switch (action.GetActionType()) {
    case ActionType::Move:
      return CheckMove(action);
    case ActionType::Fire:
      return CheckFire(action);
    case ActionType::RotateClockwise:
      return CheckRotateClock(action);
    case ActionType::RotateCounterClockwise:
      return CheckRotateCounterClock(action);
  }
}

void GameMaster::ManageAction(const Action& action) {
  switch (action.GetActionType()) {
    case ActionType::Move:
      return Move(action);
    case ActionType::Fire:
      return Fire(action);
    case ActionType::RotateClockwise:
      return RotateClock(action);
    case ActionType::RotateCounterClockwise:
      return RotateCounterClock(action);
    case ActionType::EndTurn:
      return EndTurn(action);
    case ActionType::ConstructShip:
      return ConstructShip(action);
  }
}

Player& GameMaster::GetPlayer(size_t num) {
  if (num == 1) {
    return player1_;
  } else if (num == 2) {
    return player2_;
  }
}

const Player& GameMaster::GetPlayer(size_t num) const {
  if (num == 1) {
    return player1_;
  } else if (num == 2) {
    return player2_;
  }
}

Error GameMaster::CheckMove(const Action& action) const {
  auto move_action = dynamic_cast<const MoveAction&>(action);
  return GetPlayer(action.GetPlayerNum()).IsValidMove(move_action.GetMovingShipCords(),
                                                      abs(move_action.GetDistance()),
                                                      move_action.GetDistance() > 0);
}

void GameMaster::Move(const Action& action) {
  auto move_action = dynamic_cast<const MoveAction&>(action);
  GetPlayer(action.GetPlayerNum()).Move(move_action.GetMovingShipCords(),
                                               abs(move_action.GetDistance()),
                                               move_action.GetDistance() > 0);
}

Error GameMaster::CheckFire(const Action& action) const {
  auto fire_action = dynamic_cast<const FireAction&>(action);
  return GetPlayer(action.GetPlayerNum()).IsValidFire(fire_action.GetFiringShipCords(),
                                                      fire_action.GetLandingCords());
}

void GameMaster::Fire(const Action& action) {
  auto fire_action = dynamic_cast<const FireAction&>(action);
  auto bullet = GetPlayer(action.GetPlayerNum()).Fire(fire_action.GetFiringShipCords(),
                                                      fire_action.GetLandingCords());
  size_t another_player = action.GetPlayerNum() % 2 + 1;
  GetPlayer(another_player).GetHit(bullet);
}

Error GameMaster::CheckRotateClock(const Action& action) const {
  auto rotate_clock_action = dynamic_cast<const RotateClockwiseAction&>(action);
  return GetPlayer(action.GetPlayerNum()).IsValidRotate(rotate_clock_action.GetPivot(),
                                                        rotate_clock_action.GetPivot(),
                                                        true);
}

void GameMaster::RotateClock(const Action& action) {
  auto rotate_clock_action = dynamic_cast<const RotateClockwiseAction&>(action);
  GetPlayer(action.GetPlayerNum()).Rotate(rotate_clock_action.GetPivot(),
                                          rotate_clock_action.GetPivot(),
                                          true);
}

Error GameMaster::CheckRotateCounterClock(const Action& action) const {
  auto rotate_cclock_action = dynamic_cast<const RotateClockwiseAction&>(action);
  return GetPlayer(action.GetPlayerNum()).IsValidRotate(rotate_cclock_action.GetPivot(),
                                                        rotate_cclock_action.GetPivot(),
                                                        false);
}

void GameMaster::RotateCounterClock(const Action& action) {
  auto rotate_cclock_action = dynamic_cast<const RotateClockwiseAction&>(action);
  GetPlayer(action.GetPlayerNum()).Rotate(rotate_cclock_action.GetPivot(),
                                          rotate_cclock_action.GetPivot(),
                                          false);
}

void GameMaster::EndTurn(const Action& action) {
  auto end_turn_action = dynamic_cast<const EndTurnAction&>(action);
  GetPlayer(action.GetPlayerNum()).EndTurn();
}

void GameMaster::ConstructShip(const Action& action) {} // TODO Ship Construction




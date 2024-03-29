#include "GameMaster.h"
#include "Ships/Shipyard.h"

GameMaster::GameMaster(size_t) {
  Shipyard factory;

  vector<Ship> fleet1;
  fleet1.push_back(factory.MakeCruiser({1, 1}));
  fleet1.push_back(factory.MakeFrigate({7, 7}));
  player1_ = Player(3, {10, 10}, fleet1);

  vector<Ship> fleet2;
  fleet2.push_back(factory.MakeFighter({1, 1}));
  fleet2.push_back(factory.MakeDestroyer({5, 5}));
  player2_ = Player(3, {10, 10}, fleet2);
}

Error GameMaster::CheckAction(const Action& action) const {
  switch (action.GetActionType()) {
    case ActionType::Move:return CheckMove(action);
    case ActionType::Fire:return CheckFire(action);
    case ActionType::RotateClockwise:return CheckRotateClock(action);
    case ActionType::RotateCounterClockwise:return CheckRotateCounterClock(action);
    case ActionType::ConstructShip:return CheckConstructShip(action);
    case ActionType::EndTurn:return Error::kNoError;
  }
}

void GameMaster::ManageAction(const Action& action) {
  switch (action.GetActionType()) {
    case ActionType::Move:Move(action);
      break;
    case ActionType::Fire:Fire(action);
      break;
    case ActionType::RotateClockwise:RotateClock(action);
      break;
    case ActionType::RotateCounterClockwise:RotateCounterClock(action);
      break;
    case ActionType::EndTurn:EndTurn(action);
      break;
    case ActionType::ConstructShip:ConstructShip(action);
      break;
  }
  if (is_turn_finished1_ and is_turn_finished2_) {
    player1_.EndTurn();
    player2_.EndTurn();
    ++turns_passed_;
    is_turn_finished1_ = false;
    is_turn_finished2_ = false;
  }
}

Player& GameMaster::GetPlayerByReference(size_t num) {
  return (num == 1) ? player1_ : player2_;
}

const Player& GameMaster::GetPlayer(size_t num) const {
  return (num == 1) ? player1_ : player2_;
}

bool& GameMaster::GetIsTurnFinished(size_t player_num) {
  return (player_num == 1) ? is_turn_finished1_ : is_turn_finished2_;
}

size_t& GameMaster::GetMoney(size_t player_num) {
  return (player_num == 1) ? money1_ : money2_;
}

size_t GameMaster::GetMoney(size_t player_num) const {
  return (player_num == 1) ? money1_ : money2_;
}

Error GameMaster::CheckMove(const Action& action) const {
  auto move_action = dynamic_cast<const MoveAction&>(action);
  return GetPlayer(action.GetPlayerNum()).IsValidMove(move_action.GetMovingShipCords(),
                                                      abs(move_action.GetDistance()),
                                                      move_action.GetDistance() > 0);
}

void GameMaster::Move(const Action& action) {
  auto move_action = dynamic_cast<const MoveAction&>(action);
  GetPlayerByReference(action.GetPlayerNum()).Move(move_action.GetMovingShipCords(),
                                                   abs(move_action.GetDistance()),
                                                   move_action.GetDistance() > 0);
  if (GetPlayerByReference(action.GetPlayerNum()).GetActionsLeft() == 0) {
    GetIsTurnFinished(action.GetPlayerNum()) = true;
  }
}

Error GameMaster::CheckFire(const Action& action) const {
  auto fire_action = dynamic_cast<const FireAction&>(action);
  return GetPlayer(action.GetPlayerNum()).IsValidFire(fire_action.GetFiringShipCords(),
                                                      fire_action.GetLandingCords());
}

void GameMaster::Fire(const Action& action) {
  auto fire_action = dynamic_cast<const FireAction&>(action);
  auto bullet = GetPlayerByReference(action.GetPlayerNum()).Fire(fire_action.GetFiringShipCords(),
                                                                 fire_action.GetLandingCords());
  size_t another_player = action.GetPlayerNum() % 2 + 1;
  GetPlayerByReference(another_player).ProcessHit(bullet);
  if (GetPlayerByReference(action.GetPlayerNum()).GetActionsLeft() == 0) {
    GetIsTurnFinished(action.GetPlayerNum()) = true;
  }
}

Error GameMaster::CheckRotateClock(const Action& action) const {
  auto rotate_clock_action = dynamic_cast<const RotateClockwiseAction&>(action);
  return GetPlayer(action.GetPlayerNum()).IsValidRotate(rotate_clock_action.GetPivot(),
                                                        rotate_clock_action.GetPivot(),
                                                        true);
}

void GameMaster::RotateClock(const Action& action) {
  auto rotate_clock_action = dynamic_cast<const RotateClockwiseAction&>(action);
  GetPlayerByReference(action.GetPlayerNum()).Rotate(rotate_clock_action.GetPivot(),
                                                     rotate_clock_action.GetPivot(),
                                                     true);
  if (GetPlayerByReference(action.GetPlayerNum()).GetActionsLeft() == 0) {
    GetIsTurnFinished(action.GetPlayerNum()) = true;
  }
}

Error GameMaster::CheckRotateCounterClock(const Action& action) const {
  auto rotate_cclock_action = dynamic_cast<const RotateClockwiseAction&>(action);
  return GetPlayer(action.GetPlayerNum()).IsValidRotate(rotate_cclock_action.GetPivot(),
                                                        rotate_cclock_action.GetPivot(),
                                                        false);
}

void GameMaster::RotateCounterClock(const Action& action) {
  auto rotate_cclock_action = dynamic_cast<const RotateClockwiseAction&>(action);
  GetPlayerByReference(action.GetPlayerNum()).Rotate(rotate_cclock_action.GetPivot(),
                                                     rotate_cclock_action.GetPivot(),
                                                     false);
  if (GetPlayerByReference(action.GetPlayerNum()).GetActionsLeft() == 0) {
    GetIsTurnFinished(action.GetPlayerNum()) = true;
  }
}

void GameMaster::EndTurn(const Action& action) {
  GetIsTurnFinished(action.GetPlayerNum()) = true;
}

Error GameMaster::CheckConstructShip(const Action& action) const {
  auto construct_action = dynamic_cast<const ConstructShipAction&>(action);
  if (GetMoney(action.GetPlayerNum()) < Shipyard().GetPrice(construct_action.GetShipType())) {
    return Error::kOutOfMoney;
  }
  return Error::kNoError;
}

void GameMaster::ConstructShip(const Action& action) {
  auto construct_action = dynamic_cast<const ConstructShipAction&>(action);
  Ship new_ship = Shipyard().Make(construct_action.GetShipType(), construct_action.GetTopCords());
  GetPlayerByReference(action.GetPlayerNum()).AddShip(new_ship);
  GetMoney(action.GetPlayerNum()) -= Shipyard().GetPrice(construct_action.GetShipType());
}
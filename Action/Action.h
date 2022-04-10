#pragma once

#include "Ships/ShipType.h"
#include "Coords/Coords.h"
#include <cstdint>

enum class ActionType {
  Move,
  Fire,
  RotateClockwise,
  RotateCounterClockwise,
  EndTurn,
  ConstructShip,
};

class Action {
 public:
  ActionType GetActionType() const;
  uint8_t GetPlayerNum() const;
  virtual ~Action() = default;
 protected:
  ActionType action_type_;
  uint8_t player_;
};

class FireAction : public Action {
 public:
  FireAction(Coords firing_ship, Coords landing_cords, uint8_t player);
  const Coords& GetFiringShipCords() const;
  const Coords& GetLandingCords() const;
 private:
  Coords firing_ship_cords_;
  Coords landing_cords_;
};

class MoveAction : public Action {
 public:
  MoveAction(Coords moving_ship, int distance, uint8_t player);
  const Coords& GetMovingShipCords() const;
  int GetDistance() const;
 private:
  Coords moving_ship_cords_;
  int distance_;
};

class RotateClockwiseAction : public Action {
 public:
  explicit RotateClockwiseAction(Coords rotating_pivot, uint8_t player);
  const Coords& GetPivot() const;
 private:
  Coords pivot_;
};

class RotateCounterClockwiseAction : public Action {
 public:
  explicit RotateCounterClockwiseAction(Coords rotating_pivot, uint8_t player);
  const Coords& GetPivot() const;
 private:
  Coords pivot_;
};

class EndTurnAction : public Action {
 public:
  EndTurnAction(uint8_t player);
 private:
};

class ConstructShipAction : public Action {
 public:
  ConstructShipAction(ShipType ship_type, uint8_t player);
  ShipType GetShipType() const;
 private:
  ShipType ship_type_;
};
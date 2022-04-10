#pragma once

#include "Ship.h"
#include "ShipType.h"

#ifndef MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_
#define MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_

class Shipyard {
 public:
  [[nodiscard]] Ship Make(ShipType, Coords cords = {0, 0}) const;
  [[nodiscard]] size_t GetPrice(ShipType ship_type) const;
  [[nodiscard]] Ship MakeFighter(Coords) const;
  [[nodiscard]] Ship MakeFrigate(Coords) const;
  [[nodiscard]] Ship MakeDestroyer(Coords) const;
  [[nodiscard]] Ship MakeCruiser(Coords) const;
  [[nodiscard]] Ship MakeMothership(Coords) const;
 private:
  static const size_t kFighterPrice = 100;
  static const size_t kFrigatePrice = 200;
  static const size_t kDestroyerPrice = 100;
  static const size_t kCruiserPrice = 100;
  static const size_t kMothershipPrice = 100;
};

#endif //MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_

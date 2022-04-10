#pragma once

#include "Ship.h"
#include "ShipType.h"

#ifndef MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_
#define MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_

class Shipyard {
 public:
  [[nodiscard]] Ship Make(ShipType) const;
  [[nodiscard]] size_t GetPrice(ShipType ship_type) const;
  [[nodiscard]] Ship MakeFighter() const;
  [[nodiscard]] Ship MakeFrigate() const;
  [[nodiscard]] Ship MakeDestroyer() const;
  [[nodiscard]] Ship MakeCruiser() const;
  [[nodiscard]] Ship MakeMothership() const;
 private:
  static const size_t kFighterPrice = 100;
  static const size_t kFrigatePrice = 200;
  static const size_t kDestroyerPrice = 100;
  static const size_t kCruiserPrice = 100;
  static const size_t kMothershipPrice = 100;
};

#endif //MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_

#pragma once

#include "Ship.h"
#include "ShipType.h"

class Shipyard {
 public:
  [[nodiscard]] Ship Make(ShipType, Coords cords = {0, 0}) const;
  [[nodiscard]] size_t GetPrice(ShipType ship_type) const;
  [[nodiscard]] Ship MakeFighter(Coords) const;
  [[nodiscard]] Ship MakeFrigate(Coords) const;
  [[nodiscard]] Ship MakeSubmarine(Coords cords) const;
  [[nodiscard]] Ship MakeCruiser(Coords) const;
  [[nodiscard]] Ship MakeCarrier(Coords cords) const;

  struct ShipInfo {
    size_t price;
    size_t width;
    size_t length;
  };

  constexpr static const ShipInfo kFighterInfo = {100, 1, 1};
  constexpr static const ShipInfo kFrigateInfo = {150, 1, 2};
  constexpr static const ShipInfo kSubmarineInfo = {200, 1, 3};
  constexpr static const ShipInfo kCruiserInfo = {250, 1, 4};
  constexpr static const ShipInfo kCarrierInfo = {400, 2, 4};

 private:
};
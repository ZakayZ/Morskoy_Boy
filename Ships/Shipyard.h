#pragma once

#include "../includes.h"

#ifndef MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_
#define MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_

class Shipyard {
 public:
  [[nodiscard]] Ship Make(ShipType) const;
  [[nodiscard]] Ship MakeFighter() const;
  [[nodiscard]] Ship MakeFrigate() const;
  [[nodiscard]] Ship MakeDestroyer() const;
  [[nodiscard]] Ship MakeCruiser() const;
  [[nodiscard]] Ship MakeMothership() const;
 private:
};

#endif //MORSKOY_BOY_MORSKOY_BOY_SHIPS_SHIPYARD_H_

#pragma once

#include "../includes.h"

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


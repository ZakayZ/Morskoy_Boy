#pragma once

#ifndef SHIPS_MORSKOY_BOY_GAMEMASTER_GAMEMASTER_H_
#define SHIPS_MORSKOY_BOY_GAMEMASTER_GAMEMASTER_H_

#include "../includes.h"

class GameMaster {
 public:
  GameMaster();
  [[nodiscard]] Error CheckAction(const Action&) const;
  void MakeAction(const Action&);
  ~GameMaster() = default;
 private:
  Player player1_;
  Player player2_;
};

#endif //SHIPS_MORSKOY_BOY_GAMEMASTER_GAMEMASTER_H_

#pragma once

#ifndef SHIPS_MORSKOY_BOY_GAMEMASTER_GAMEMASTER_H_
#define SHIPS_MORSKOY_BOY_GAMEMASTER_GAMEMASTER_H_

#include "../includes.h"

class GameMaster {
 public:
  GameMaster() = default;
  void MakeNewGame(std::string name1, std::string name2);

  [[nodiscard]] Error CheckAction(const Action&) const;
  void ManageAction(const Action&);
  void EndTurn();
  ~GameMaster() = default;
 private:
  Player player1_;
  Player player2_;
  size_t turns_passed_;
};

#endif //SHIPS_MORSKOY_BOY_GAMEMASTER_GAMEMASTER_H_

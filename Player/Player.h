#pragma once

#include "../includes.h"
#include "../Field/Field.h"

#ifndef SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_
#define SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_

class Player {
 public:
  Player() = delete;
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  bool HasActionPoints(size_t = 1) const;
  size_t GetShipId(const Coords&) const;
  bool IsValidId(size_t) const;
  bool IsValidAction(const Action&) const;
  void MakeAction(const Action&);
  ~Player() = default;
 private:
  Field my_field_;
  vector<Ship> fleet_;
  size_t actions_left_;
};

#endif //SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_

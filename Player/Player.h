#pragma once

#include "../includes.h"

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
  Error IsValidFire(size_t, const Coords&) const;
  void Fire(size_t, const Coords&);
  Error IsValidMove(size_t, size_t) const;
  void Move(size_t, size_t);
  Error IsValidRotate(size_t, const Coords&, bool) const;
  void Rotate(size_t, const Coords&, bool);
  ~Player() = default;
 private:
  size_t actions_left_;
  Field my_field_;
  vector<Ship> fleet_;
  vector<std::shared_ptr<Projectile>> hit_by_;
};

#endif //SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_
#pragma once

#ifndef SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_
#define SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_

#include "../includes.h"

class Player {
 public:
  Player();
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  [[nodiscard]] size_t GetShipId(const Coords&) const;
  [[nodiscard]] Error IsValidId(size_t) const;
  [[nodiscard]] Error IsValidFire(size_t, const Coords&) const;
  [[nodiscard]] std::shared_ptr<Projectile> Fire(size_t, const Coords&);
  [[nodiscard]] Error IsValidMove(size_t, size_t, bool) const;
  void Move(size_t, size_t, bool);
  [[nodiscard]] Error IsValidRotate(size_t, const Coords&, bool) const;
  void Rotate(size_t, const Coords&, bool);
  void GetHit(std::shared_ptr<Projectile>&);
  void EndTurn();
  ~Player() = default;
 private:
  void HandleDefault(const std::shared_ptr<Projectile>&); // TODO
  //void HandleFlare(const std::shared_ptr<FlareProjectile>&); // TODO
  size_t actions_left_;
  Field my_field_;
  vector<Ship> fleet_;
  vector<std::shared_ptr<Projectile>> hit_by_;
};

#endif //SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_
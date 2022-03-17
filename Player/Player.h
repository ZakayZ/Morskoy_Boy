#pragma once

#include "../includes.h"

#ifndef SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_
#define SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_

class Player {
 public:
  Player() = default;
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  [[nodiscard]] Error IsValidCoords(const Coords&) const;
  [[nodiscard]] Error IsValidFire(const Coords&, const Coords&) const;
  [[nodiscard]] std::shared_ptr<Projectile> Fire(const Coords&, const Coords&);
  [[nodiscard]] Error IsValidMove(const Coords&, size_t, bool) const;
  void Move(const Coords&, size_t, bool);
  [[nodiscard]] Error IsValidRotate(const Coords&, const Coords&, bool) const;
  void Rotate(const Coords&, const Coords&, bool);
  void GetHit(std::shared_ptr<Projectile>&);
  void EndTurn();
  ~Player() = default;
 private:
  [[nodiscard]] size_t GetShipId(const Coords&) const;
  void HandleDefaultProjectile(const std::shared_ptr<DefaultProjectile>&);
  void HandleFlareProjectile(const std::shared_ptr<Flare>&);
  size_t actions_left_;
  Field my_field_;
  vector<Ship> fleet_;
  vector<std::shared_ptr<Projectile>> hit_by_;
};

#endif //SHIPS_MORSKOY_BOY_PLAYER_PLAYER_H_
#pragma once

#include "../Ships/Ship.h"
#include "../Coords/Coords.h"
#include "../Error.h"
#include "../Weapons/Projectile.h"
#include "../Field//Field.h"
#include <vector>

using std::vector;

class Player {
 public:
  Player() = default;
  Player(size_t, const Coords&, const vector<Ship>&);
  Player& operator=(const Player&) = delete;
  [[nodiscard]] Error IsValidCoords(const Coords&) const;
  [[nodiscard]] Error IsValidFire(const Coords&, const Coords&) const;
  [[nodiscard]] std::shared_ptr<Projectile> Fire(const Coords&, const Coords&);
  [[nodiscard]] Error IsValidMove(const Coords&, size_t, bool) const;
  [[nodiscard]] Error IsValidRotate(const Coords&, const Coords&, bool) const;
  void Move(const Coords&, size_t, bool);
  void Rotate(const Coords&, const Coords&, bool);
  void GetHit(std::shared_ptr<Projectile>&);
  void EndTurn();
  ~Player() = default;
 private:
  struct ProjectileHandler;
  struct DefaultHandler;
  struct FlareHandler;
  [[nodiscard]] size_t GetShipId(const Coords&) const;
  template <class Handler, typename T>
  void ApplyHandler(const Coords&, const vector<vector<T>>&);
  void HandleDefaultProjectile(const std::shared_ptr<DefaultProjectile>&);
  void HandleFlareProjectile(const std::shared_ptr<Flare>&);
  size_t actions_left_;
  Field my_field_;
  vector<Ship> fleet_;
  vector<std::shared_ptr<Projectile>> hit_by_;
};

struct Player::ProjectileHandler {
  virtual void operator()(Ship&, const Coords&, size_t) = 0;
};

struct Player::DefaultHandler: ProjectileHandler {
  void operator()(Ship&, const Coords&, size_t) override;
};

struct Player::FlareHandler: ProjectileHandler {
  void operator()(Ship&, const Coords&, size_t) override;
};
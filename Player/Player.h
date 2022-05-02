#pragma once

#include "Ships/Ship.h"
#include "Coords/Coords.h"
#include "Error.h"
#include "Weapons/Projectile.h"
#include "Field/Field.h"
#include <vector>
#include <memory>

using std::vector;

class Player {
 public:
  Player() = default;
  Player(size_t, const Coords&, const vector<Ship>&);
  Player& operator=(const Player&) = default;
  ~Player() = default;
  [[nodiscard]] const vector<Ship>& GetFleet() const;
  [[nodiscard]] const Field& GetField() const;
  [[nodiscard]] Error IsValidCoords(const Coords&) const;
  [[nodiscard]] Error IsValidFire(const Coords&, const Coords&) const;
  [[nodiscard]] std::shared_ptr<Projectile> Fire(const Coords&, const Coords&);
  [[nodiscard]] Error IsValidMove(const Coords&, size_t, bool) const;
  [[nodiscard]] Error IsValidRotate(const Coords&, const Coords&, bool) const;
  bool IsValidSetup() const;
  Error IsValidTranslate(const Coords& ship_cords, int delta_x, int delta_y) const;
  void Move(const Coords&, size_t, bool);
  void AddShip(const Ship&);
  void Rotate(const Coords&, const Coords&, bool);
  void ProcessHit(std::shared_ptr<Projectile>&);
  [[nodiscard]] size_t GetActionsLeft() const;
  bool IsDead() const;
  void EndTurn();
  void Translate(const Coords& ship_cords, int delta_x, int delta_y);
 private:
  struct ProjectileHandler;
  struct DefaultHandler;
  struct FlareHandler;
  [[nodiscard]] size_t GetShipId(const Coords&) const;
  template <class Handler, typename T>
  void ApplyHandler(const Coords&, const vector<vector<T>>&);
  void HandleDefaultProjectile(const std::shared_ptr<DefaultProjectile>&);
  void HandleFlareProjectile(const std::shared_ptr<Flare>&);

  size_t max_actions_;
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
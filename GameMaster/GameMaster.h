#pragma once

#include "../includes.h"

class GameMaster {
 public:
  GameMaster() = default;
  void MakeNewGame(std::string name1, std::string name2);
  [[nodiscard]] Error CheckAction(const Action&) const;
  void ManageAction(const Action&);
  void Display(sf::RenderWindow&, const Coords& field1, const Coords& field2, uint8_t player) const;
  void EndTurn();
  ~GameMaster() = default;
 private:
  void Fire(const Action&);
  void Move(const Action&);
  void RotateClock(const Action&);
  void RotateCounterClock(const Action&);
  Error CheckFire(const Action&) const;
  Error CheckMove(const Action&) const;
  Error CheckRotateClock(const Action&) const;
  Error CheckRotateCounterClock(const Action&) const;
  Player player1_;
  Player player2_;
  size_t turns_passed_;
};

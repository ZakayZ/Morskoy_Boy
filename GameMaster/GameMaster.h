#pragma once

#include "../Error.h"
#include "../Action/Action.h"
#include "../Player/Player.h"
#include <vector>

using std::vector;

class GameMaster {
 public:
  GameMaster() = default;
  void MakeNewGame(std::string name1, std::string name2);
  [[nodiscard]] Error CheckAction(const Action& action) const;
  void ManageAction(const Action& action);
  ~GameMaster() = default;
 private:
  Player& GetPlayer(size_t num);
  const Player& GetPlayer(size_t num) const;
  bool& GetIsTurnFinished(size_t player_num);
  size_t& GetMoney(size_t player_num);
  size_t GetMoney(size_t player_num) const;
  void Fire(const Action& action);
  void Move(const Action& action);
  void RotateClock(const Action& action);
  void RotateCounterClock(const Action& action);
  void EndTurn(const Action& action);
  void ConstructShip(const Action& action);
  Error CheckFire(const Action& action) const;
  Error CheckMove(const Action& action) const;
  Error CheckRotateClock(const Action& action) const;
  Error CheckRotateCounterClock(const Action& action) const;
  Error CheckConstructShip(const Action& action) const;
  size_t money1_ = kInitialMoney;
  size_t money2_ = kInitialMoney;
  bool is_turn_finished1_ = false;
  bool is_turn_finished2_ = false;
  Player player1_;
  Player player2_;
  size_t turns_passed_ = 0;
  static const size_t kInitialMoney = 1000;
};

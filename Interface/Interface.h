#pragma once

#include "GameMaster/GameMaster.h"
#include "Action/ActionGenerator.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <string>

enum class InterfaceType {
  Graphical,
  Console,
};

template <InterfaceType>
class Interface;

template <>
class Interface<InterfaceType::Graphical> {
 public:
  Interface(size_t width, size_t height);
  ~Interface();
  void Setup();
  void GameCycle();
  [[nodiscard]] bool Running() const;
 private:
  void Setup(uint8_t player_num);
  void Turn(uint8_t player_num);
  void Display(uint8_t player_num) const;
  bool active_;
  GameMaster game_;
  std::shared_ptr<sf::RenderWindow> window1_;
  SFMLRenderer renderer1_;

  std::shared_ptr<sf::RenderWindow> window2_;
  SFMLRenderer renderer2_;
};

template <>
class Interface<InterfaceType::Console> {
 public:
 private:
};

Interface<InterfaceType::Graphical>::Interface(size_t width, size_t height)
    : active_(true),
      game_(),
      window1_(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Ships")),
      renderer1_(window1_),
      window2_(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Ships")),
      renderer2_(window2_) {}

Interface<InterfaceType::Graphical>::~Interface() = default;

void Interface<InterfaceType::Graphical>::Setup() {
//  cout << "Enter first player name: ";
//  std::string first_player_name;
//  cin >> first_player_name;
//  cout << "Enter second player name: ";
//  std::string second_player_name;
//  cin >> second_player_name;
//  game_.MakeNewGame(first_player_name, second_player_name);
  cout << "First player can setup his fleet:\n";
  Setup(1);
  cout << "Second player can setup his fleet:\n";
  Setup(2);
}

void Interface<InterfaceType::Graphical>::GameCycle() {
  cout << "First player's turn:\n";
  Turn(1);
  cout << "Second player's turn:\n";
  Turn(2);
  cout << "EndTurn!\n";
}

bool Interface<InterfaceType::Graphical>::Running() const {
  return active_;
}

void Interface<InterfaceType::Graphical>::Setup(uint8_t player_num) {
  bool player_finished = false;
  std::string command;
  while (!player_finished) {
    cin >> command;
    if (!ActionGenerator::IsValidString(command, player_num)) {
      continue;
    }
    auto action = ActionGenerator::GenerateFromString(player_num, command);
    auto error = game_.CheckAction(*action);
    if (action->GetActionType() == ActionType::EndTurn) {
      player_finished = true;
      break;
    }
    if (action->GetActionType() == ActionType::Fire) {
      error = Error::kInvalidTarget;
    }
    switch (error) {
      case Error::kOutOfActions: {
        cout << "How I ended up here! \n";
        player_finished = true;
        break;
      }
      case Error::kNoError: {
        game_.ManageAction(*action);
        break;
      }
      case Error::kInvalidShip: {
        cout << "No ship with this coordinates! \n";
        break;
      }
      case Error::kInvalidTarget: {
        cout << "Can't fire in this stage! \n";
        break;
      }
      case Error::kShipIsDead: {
        cout << "This ship is dead! \n";
        break;
      }
      case Error::kIntersectsFieldBoundary: {
        cout << "This position is out of field! \n";
        break;
      }
      case Error::kIntersectsShip: {
        cout << "This position intersect other ship! \n";
        break;
      }
      case Error::kWeaponOnCooldown: {
        cout << "Ship's weapons are reloading! \n";
        break;
      }
      case Error::kOutOfMoney: {
        cout << "You can't buy ships now! \n";
        break;
      }
    }
  }
}

void Interface<InterfaceType::Graphical>::Turn(uint8_t player_num) {
  bool player_finished = false;
  std::string command;
  while (!player_finished) {
    Display(player_num);
    cin >> command;
    if (!ActionGenerator::IsValidString(command, player_num)) {
      continue;
    }
    auto action = ActionGenerator::GenerateFromString(player_num, command);
    auto error = game_.CheckAction(*action);
    if (action->GetActionType() == ActionType::EndTurn) {
      game_.ManageAction(*action);
      player_finished = true;
      break;
    }
    switch (error) {
      case Error::kOutOfActions: {
        cout << "No Actions left, change! \n";
        game_.ManageAction(EndTurnAction(player_num));
        player_finished = true;
        break;
      }
      case Error::kNoError: {
        game_.ManageAction(*action);
        break;
      }
      case Error::kInvalidShip: {
        cout << "No ship with this coordinates! \n";
        break;
      }
      case Error::kInvalidTarget: {
        cout << "Invalid target! \n";
        break;
      }
      case Error::kShipIsDead: {
        cout << "This ship is dead! \n";
        break;
      }
      case Error::kIntersectsFieldBoundary: {
        cout << "This position is out of field! \n";
        break;
      }
      case Error::kIntersectsShip: {
        cout << "This position intersect other ship! \n";
        break;
      }
      case Error::kWeaponOnCooldown: {
        cout << "Ship's weapons are reloading! \n";
        break;
      }
      case Error::kOutOfMoney: {
        cout << "You can't buy ships now! \n";
        break;
      }
    }
  }
}

void Interface<InterfaceType::Graphical>::Display(uint8_t player_num) const {
  auto player1 = game_.GetPlayer(1);
  auto player2 = game_.GetPlayer(2);
  if (player_num == 1) {
    window1_->clear();
    renderer1_.Render(player1, {0, 0}, true);
    renderer1_.Render(player2, {500, 0}, false);
    window1_->display();
  } else {
    window2_->clear();
    renderer2_.Render(player2, {0, 0}, true);
    renderer2_.Render(player1, {500, 0}, false);
    window2_->display();
  }
}

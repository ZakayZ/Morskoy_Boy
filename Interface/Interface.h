#pragma once

#include "GameMaster/GameMaster.h"
#include "Action/ActionGenerator.h"
#include "Renderer/Renderer.h"
#include <SFML/System.hpp>
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
  void Game();
  void GameCycle();
  void Display();
  [[nodiscard]] bool Running() const;
 private:
  void Setup(uint8_t player_num);
  void Turn(uint8_t player_num);
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
      game_(3),
      window1_(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Ships1")),
      renderer1_(window1_),
      window2_(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Ships2")),
      renderer2_(window2_) {
  window1_->setFramerateLimit(15);
  window2_->setFramerateLimit(15);
}

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
  std::system("clear");
  cout << "Second player can setup his fleet:\n";
  Setup(2);
  std::system("clear");
}

void Interface<InterfaceType::Graphical>::Game() {
  Setup();
  while (Running()) {
    GameCycle();
  }
}

void Interface<InterfaceType::Graphical>::GameCycle() {
  std::system("clear");
  cout << "First player's turn:\n";
  Turn(1);
  std::system("clear");
  cout << "Second player's turn:\n";
  Turn(2);
  cout << "EndTurn!\n";
}

bool Interface<InterfaceType::Graphical>::Running() const {
  return window1_->isOpen() && window2_->isOpen();
}

void Interface<InterfaceType::Graphical>::Setup(uint8_t player_num) {
  bool player_finished = false;
  std::string command;
  while (!player_finished) {
    std::getline(cin, command);
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
        cout << "Success!\n";
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
    std::getline(cin, command);
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
        cout << "Success!\n";
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

void Interface<InterfaceType::Graphical>::Display() {
  auto& player1 = game_.GetConstPlayer(1);
  auto& player2 = game_.GetConstPlayer(2);
  while (Running()) {
    sf::Event event;
    while (window1_->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window1_->close();
        window2_->close();
      }
    }
    window1_->clear();
    renderer1_.Render(player1, {0, 0}, true);
    renderer1_.Render(player2, {500, 0}, false);
    window1_->display();

    while (window2_->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window1_->close();
        window2_->close();
      }
    }
    window2_->clear();
    renderer2_.Render(player2, {0, 0}, true);
    renderer2_.Render(player1, {500, 0}, false);
    window2_->display();
  }
}
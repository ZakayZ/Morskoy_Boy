#pragma once

#include "GameMaster/GameMaster.h"
#include "Action/ActionGenerator.h"
#include "Renderer/ImageStorage.h"
#include "Renderer/Renderer.h"
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <array>

class Interface {
 public:
  explicit Interface(size_t actions);
  ~Interface() = default;
  virtual void Game() = 0;
  virtual void Display() = 0;
  [[nodiscard]] virtual bool Running() const = 0;
 protected:
  Error ProcessSetupAction(const string& command, uint8_t player_num, bool& player_finished);
  Error ProcessTurnAction(const string& command, uint8_t player_num, bool& player_finished);
  void SetupMessage(Error error);
  void TurnMessage(Error error);

  bool active_;
  GameMaster game_;
};

class GraphicalInterface : public Interface {
 public:
  GraphicalInterface(size_t width, size_t height, size_t actions, std::shared_ptr<ImageStorage>& storage);
  ~GraphicalInterface();
  void Game() override;
  void Display() override;
  [[nodiscard]] bool Running() const override;
 private:
  void GameCycle();
  void Setup();
  void Setup(uint8_t player_num);
  void Turn(uint8_t player_num);
  void Display(const std::array<const Player*, 2>&, uint8_t player);

  std::array<std::shared_ptr<sf::RenderWindow>, 2> windows_;
  std::array<SFMLRenderer, 2> renderers_;
};

//class ConsoleInterface : public Interface {
// public:
// private:
//};

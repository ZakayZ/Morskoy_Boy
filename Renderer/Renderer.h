#pragma once

#include "ConsoleWindow.h"
#include "Ships/Ship.h"
#include "Weapons/Weapon.h"
#include "Field/Field.h"
#include "Player/Player.h"
#include <SFML/Graphics.hpp>

namespace render_data {
static const size_t kTileSide = 50;
}

class Renderer {
 public:
  Renderer() = default;
  virtual void Render(const std::shared_ptr<Weapon>, const Coords&, bool) const = 0;
  virtual void Render(const Ship&, const Coords&, bool) const = 0;
  virtual void Render(const Field&, const Coords&, bool) const = 0;
  virtual void Render(const Player&, const Coords&, bool) const = 0;
  virtual ~Renderer() = 0;
};

class ConsoleRenderer : public Renderer {
 public:
  explicit ConsoleRenderer(std::shared_ptr<ConsoleWindow>&);
  void Render(const std::shared_ptr<Weapon>, const Coords&, bool) const override {}
  void Render(const Ship&, const Coords&, bool) const override;
  void Render(const Field&, const Coords&, bool) const override;
  void Render(const Player&, const Coords&, bool) const override;
  ~ConsoleRenderer() override = default;
 private:
  std::shared_ptr<ConsoleWindow> window_;
};

class SFMLRenderer : public Renderer {
 public:
  explicit SFMLRenderer(std::shared_ptr<sf::RenderWindow>&);
  void Render(std::shared_ptr<Weapon>, const Coords&, bool) const override;
  void Render(const Ship&, const Coords&, bool) const override;
  void Render(const Field&, const Coords&, bool) const override;
  void Render(const Player&, const Coords&, bool) const override;
  ~SFMLRenderer() override = default;
 private:
 private:
  std::shared_ptr<sf::RenderWindow> window_;
};

#pragma once

#include "ConsoleWindow.h"
#include "Ships/Ship.h"
#include "Ships/Shipyard.h"
#include "Weapons/Weapon.h"
#include "Field/Field.h"
#include "Player/Player.h"
#include "ImageStorage.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Renderer {
 public:
  Renderer() = default;
  virtual void Render(std::shared_ptr<Weapon>, const Coords&, bool) = 0;
  virtual void Render(const Ship&, const Coords&, bool) = 0;
  virtual void Render(const Field&, const Coords&, bool) = 0;
  virtual void Render(const Player&, const Coords&, bool) = 0;
  virtual ~Renderer() = 0;
};

class ConsoleRenderer : public Renderer {
 public:
  explicit ConsoleRenderer(std::shared_ptr<ConsoleWindow>&);
  void Render(std::shared_ptr<Weapon>, const Coords&, bool) override {}
  void Render(const Ship&, const Coords&, bool) override;
  void Render(const Field&, const Coords&, bool) override;
  void Render(const Player&, const Coords&, bool) override;
  ~ConsoleRenderer() override = default;

 private:
  std::shared_ptr<ConsoleWindow> window_;
};

class SFMLRenderer : public Renderer {
 public:
  SFMLRenderer(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<ImageStorage>& images);
  void Render(std::shared_ptr<Weapon>, const Coords&, bool) override;
  void Render(std::shared_ptr<Weapon>,
              const sf::Vector2f& center,
              const Coords& offset,
              bool visible,
              BoundaryBox::FacingDirection facing);
  void Render(const Ship&, const Coords&, bool) override;
  void Render(const Field&, const Coords&, bool) override;
  void Render(const Player&, const Coords&, bool) override;
  void Render(const Animation&, const Coords&, bool);
  ~SFMLRenderer() override = default;

 private:
  struct SpriteHolder {
    sf::Sprite fighter_sprite;
    sf::Sprite frigate_sprite;
    sf::Sprite submarine_sprite;
    sf::Sprite cruiser_sprite;
    sf::Sprite carrier_sprite;

    sf::Sprite gun_sprite_;
    sf::Sprite flare_gun_sprite;
    sf::Sprite mortar_sprite;
    sf::Sprite bang_sprite;

    sf::Sprite water_sprite;

    std::vector<sf::Sprite> boom_animation_sprite_;
  };

  sf::Sprite& ShipSprite(ShipType type);
  sf::Sprite& WeaponSprite(WeaponType type);
  void AssignShips(std::shared_ptr<ImageStorage>& images);
  void AssignWeapons(std::shared_ptr<ImageStorage>& images);
  void AssignField(std::shared_ptr<ImageStorage>& images);
  void AssignAnimations(std::shared_ptr<ImageStorage>& images);
  static void SetCenter(sf::Sprite& sprite);
  static void SetRotation(sf::Sprite& sprite, BoundaryBox::FacingDirection facing);

  std::shared_ptr<sf::RenderWindow> window_;
  SpriteHolder sprites_;
};

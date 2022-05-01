#include <SFML/Graphics.hpp>

#pragma once

namespace render_data {
static const size_t kTileSide = 80;
static const char* kFighterImage = "../Images/Battleships/Fighter.png";
static const char* kFrigateImage = "../Images/Battleships/Frigate.png";
static const char* kSubmarineImage = "../Images/Battleships/Submarine.png";
static const char* kCruiserImage = "../Images/Battleships/Cruiser.png";
static const char* kCarrierImage = "../Images/Battleships/Carrier.png";

static const char* kGunImage = "../Images/Weapons/Gun.png";
static const char* kFlareGunImage = "../Images/Weapons/FlareGun.png";
static const char* kMortarImage = "../Images/Weapons/Mortar.png";
static const char* kBangImage = "../Images/Weapons/Bang.png";

static const char* kWaterTile = "../Images/Field/Water.png";

static const char* kBoomAnimation = "../Images/Effects/Boom0.png";
}

class ImageStorage {
 public:
  ImageStorage();
  sf::Texture& GetFighter();
  sf::Texture& GetFrigate();
  sf::Texture& GetSubmarine();
  sf::Texture& GetCruiser();
  sf::Texture& GetCarrier();

  sf::Texture& GetGun();
  sf::Texture& GetFlareGun();
  sf::Texture& GetMortar();
  sf::Texture& GetBang();

  sf::Texture& GetWater();

  std::vector<sf::Texture>& GetBoomAnimation();

 private:
  void LoadShips();
  void LoadWeapons();
  void LoadField();
  void LoadAnimation();

  sf::Texture fighter_texture_;
  sf::Texture frigate_texture_;
  sf::Texture submarine_texture_;
  sf::Texture cruiser_texture_;
  sf::Texture carrier_texture_;

  sf::Texture gun_texture_;
  sf::Texture flare_gun_texture_;
  sf::Texture mortar_texture_;
  sf::Texture bang_texture_;

  sf::Texture water_texture_;

  std::vector<sf::Texture> boom_textures_;
};

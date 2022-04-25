#include <SFML/Graphics.hpp>

#pragma once

namespace render_data {
static const size_t kTileSide = 80;
static const char* kFighterImage = "../Images/Battleships/Fighter.png";
static const char* kFrigateImage = "../Images/Battleships/Frigate.png";
static const char* kSubmarineImage = "../Images/Battleships/Submarine.png";
static const char* kCruiserImage = "../Images/Battleships/Cruiser.png";
static const char* kCarrierImage = "../Images/Battleships/Carrier.png";
static const char* kWaterTile = "../Images/Water.png";
}

class ImageStorage {
 public:
  ImageStorage();
  sf::Texture& GetFighter();
  sf::Texture& GetFrigate();
  sf::Texture& GetSubmarine();
  sf::Texture& GetCruiser();
  sf::Texture& GetCarrier();
  sf::Texture& GetWater();
 private:
  sf::Texture fighter_texture_;
  sf::Texture frigate_texture_;
  sf::Texture submarine_texture_;
  sf::Texture cruiser_texture_;
  sf::Texture carrier_texture_;
  sf::Texture water_texture_;
};

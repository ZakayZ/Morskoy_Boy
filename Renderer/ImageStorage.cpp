#include "ImageStorage.h"

ImageStorage::ImageStorage() {
  if (!fighter_texture_.loadFromFile(render_data::kFighterImage)) {
    throw std::runtime_error("Couldn't load Fighter Image");
  }

  if (!frigate_texture_.loadFromFile(render_data::kFrigateImage)) {
    throw std::runtime_error("Couldn't load Frigate Image");
  }

  if (!submarine_texture_.loadFromFile(render_data::kSubmarineImage)) {
    throw std::runtime_error("Couldn't load Submarine Image");
  }

  if (!cruiser_texture_.loadFromFile(render_data::kCruiserImage)) {
    throw std::runtime_error("Couldn't load Cruiser Image");
  }

  if (!carrier_texture_.loadFromFile(render_data::kCarrierImage)) {
    throw std::runtime_error("Couldn't load Carrier Image");
  }

  if (!water_texture_.loadFromFile(render_data::kWaterTile)) {
    throw std::runtime_error("Couldn't load Water Tile");
  }
}

sf::Texture& ImageStorage::GetFighter() { return fighter_texture_; }

sf::Texture& ImageStorage::GetFrigate() { return frigate_texture_; }

sf::Texture& ImageStorage::GetSubmarine() { return submarine_texture_; }

sf::Texture& ImageStorage::GetCruiser() { return cruiser_texture_; }

sf::Texture& ImageStorage::GetCarrier() { return carrier_texture_; }

sf::Texture& ImageStorage::GetWater() { return water_texture_; }

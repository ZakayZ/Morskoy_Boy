#include "ImageStorage.h"

ImageStorage::ImageStorage() {
  LoadShips();
  LoadWeapons();
  LoadField();
  LoadAnimation();
}

sf::Texture& ImageStorage::GetFighter() { return fighter_texture_; }

sf::Texture& ImageStorage::GetFrigate() { return frigate_texture_; }

sf::Texture& ImageStorage::GetSubmarine() { return submarine_texture_; }

sf::Texture& ImageStorage::GetCruiser() { return cruiser_texture_; }

sf::Texture& ImageStorage::GetCarrier() { return carrier_texture_; }

sf::Texture& ImageStorage::GetGun() { return gun_texture_; }

sf::Texture& ImageStorage::GetFlareGun() { return flare_gun_texture_; }

sf::Texture& ImageStorage::GetMortar() { return mortar_texture_; }

sf::Texture& ImageStorage::GetBang() { return bang_texture_; }

sf::Texture& ImageStorage::GetWater() { return water_texture_; }

std::vector<sf::Texture>& ImageStorage::GetBoomAnimation() {
  return boom_textures_;
}


void ImageStorage::LoadShips() {
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
}

void ImageStorage::LoadWeapons() {
  if (!gun_texture_.loadFromFile(render_data::kGunImage)) {
    throw std::runtime_error("Couldn't load Fighter Image");
  }

  if (!flare_gun_texture_.loadFromFile(render_data::kFlareGunImage)) {
    throw std::runtime_error("Couldn't load Frigate Image");
  }

  if (!mortar_texture_.loadFromFile(render_data::kMortarImage)) {
    throw std::runtime_error("Couldn't load Submarine Image");
  }

  if (!bang_texture_.loadFromFile(render_data::kBangImage)) {
    throw std::runtime_error("Couldn't load Cruiser Image");
  }
}

void ImageStorage::LoadField() {
  if (!water_texture_.loadFromFile(render_data::kWaterTile)) {
    throw std::runtime_error("Couldn't load Water Tile");
  }
}

void ImageStorage::LoadAnimation() {
  boom_textures_.resize(8);
  std::string file_name = render_data::kBoomAnimation;
  for (size_t i = 0; i < 8; ++i) {
    file_name[file_name.size() - 5] = i + '0';
    if(!boom_textures_[i].loadFromFile(file_name)){
      throw std::runtime_error("Couldn't load Boom Animation");
    }
  }
}

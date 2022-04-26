#include "Renderer.h"

Renderer::~Renderer() = default;

ConsoleRenderer::ConsoleRenderer(std::shared_ptr<ConsoleWindow>& window) : Renderer(), window_(window) {}

void ConsoleRenderer::Render(const Ship& ship, const Coords& offset, bool my_view) {
  if (my_view || ship.GetMark() > 0) {
    auto ship_box = ship.GetPosition();
    auto& hull = ship.GetHull();
    auto width = ship_box.GetWidth();
    auto position = ship_box.GetLeftUpperCorner();
    RectangleShape rect(offset.x + position.x, offset.y + position.y, 0, 0, '*');
    auto facing = ship_box.GetFacingDirection();
    if (facing == BoundaryBox::FacingDirection::kDown || facing == BoundaryBox::FacingDirection::kUp) {
      rect.SetSize(width, 1);
    } else {
      rect.SetSize(1, width);
    }
    for (const auto& tile : hull) {
      window_->Draw(rect);
      if (facing == BoundaryBox::FacingDirection::kDown || facing == BoundaryBox::FacingDirection::kUp) {
        rect.Move(0, 1);
      } else {
        rect.Move(1, 0);
      }
    }
  }
}

void ConsoleRenderer::Render(const Field& field, const Coords& offset, bool my_view) {
  auto& grid = field.GetGrid();
  RectangleShape rect(offset.x, offset.y, 1, 1, '#');
//  rect.SetOutlineThickness(0);
//  rect.SetOutlineValue('.');
  for (const auto& row : grid) {
    for (const auto& cell : row) {
      window_->Draw(rect);
      rect.Move(1, 0);
    }
    rect.SetPosition(offset.x, rect.GetPosition().second);
    rect.Move(0, 1);
  }
}

void ConsoleRenderer::Render(const Player& player, const Coords& offset, bool my_view) {
  auto& field = player.GetField();
  Render(field, offset, my_view);
  auto& ships = player.GetFleet();
  for (const auto& ship : ships) {
    Render(ship, offset, my_view);
  }
}

SFMLRenderer::SFMLRenderer(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<ImageStorage>& images)
    : Renderer(), window_(window) {
  AssignShips(images);
  AssignWeapons(images);
  AssignField(images);
}

void SFMLRenderer::Render(const Ship& ship, const Coords& offset, bool my_view) {
  if (my_view || ship.GetMark() > 0) {
    auto ship_box = ship.GetPosition();
    auto center = ship_box.GetCenter();
    auto facing = ship_box.GetFacingDirection();
    sf::Sprite& ship_sprite = ShipSprite(ship.GetType());
    SetRotation(ship_sprite, facing);
    if (ship.IsDead()) {
      ship_sprite.setColor(sf::Color::Red);
    }
    ship_sprite.setPosition(center.x * render_data::kTileSide, center.y * render_data::kTileSide);
    window_->draw(ship_sprite);
    Render(ship.GetWeapon(), center, true, facing);
  }
}

void SFMLRenderer::Render(const Field& field, const Coords& offset, bool my_view) {
  auto& grid = field.GetGrid();
  sf::Sprite& field_sprite = sprites_.water_sprite;
  field_sprite.setPosition(offset.x + render_data::kTileSide / 2, offset.y + render_data::kTileSide / 2);
  for (const auto& row : grid) {
    for (const auto& cell : row) {
      window_->draw(field_sprite);
      field_sprite.move(render_data::kTileSide, 0);
    }
    field_sprite.setPosition(offset.x + render_data::kTileSide / 2,
                             field_sprite.getPosition().y + render_data::kTileSide);
  }
}

void SFMLRenderer::Render(const Player& player, const Coords& offset, bool my_view) {
  auto& field = player.GetField();
  Render(field, offset, my_view);
  auto& ships = player.GetFleet();
  for (const auto& ship : ships) {
    Render(ship, offset, my_view);
  }
}

void SFMLRenderer::Render(std::shared_ptr<Weapon> weapon, const Coords& offset, bool visible) {}

void SFMLRenderer::Render(
    std::shared_ptr<Weapon> weapon, const sf::Vector2f& center, bool visible, BoundaryBox::FacingDirection facing) {
  if (visible) {
    auto& weapon_sprite = WeaponSprite(weapon->GetType());
    weapon_sprite.setPosition(center.x * render_data::kTileSide, center.y * render_data::kTileSide);
    SetRotation(weapon_sprite, facing);
    window_->draw(weapon_sprite);
  }
}

sf::Sprite& SFMLRenderer::ShipSprite(ShipType type) {
  switch (type) {
    case ShipType::Fighter:return sprites_.fighter_sprite;
    case ShipType::Frigate:return sprites_.frigate_sprite;
    case ShipType::Submarine:return sprites_.submarine_sprite;
    case ShipType::Cruiser:return sprites_.cruiser_sprite;
    case ShipType::Carrier:return sprites_.carrier_sprite;
  }
}

sf::Sprite& SFMLRenderer::WeaponSprite(WeaponType type) {
  switch (type) {
    case WeaponType::Gun:return sprites_.gun_sprite_;
    case WeaponType::FlareGun:return sprites_.flare_gun_sprite;
    case WeaponType::Mortar:return sprites_.mortar_sprite;
    case WeaponType::Bang:return sprites_.bang_sprite;
  };
}

void SFMLRenderer::AssignShips(std::shared_ptr<ImageStorage>& images) {
  sprites_.fighter_sprite.setTexture(images->GetFighter());
  sprites_.fighter_sprite.setScale(
      Shipyard::kFighterInfo.length * float(render_data::kTileSide) / float(images->GetFighter().getSize().x),
      Shipyard::kFighterInfo.width * float(render_data::kTileSide) / float(images->GetFighter().getSize().y));
  SetCenter(sprites_.fighter_sprite);

  sprites_.frigate_sprite.setTexture(images->GetFrigate());
  sprites_.frigate_sprite.setScale(
      Shipyard::kFrigateInfo.length * float(render_data::kTileSide) / float(images->GetFrigate().getSize().x),
      Shipyard::kFrigateInfo.width * float(render_data::kTileSide) / float(images->GetFrigate().getSize().y));
  SetCenter(sprites_.frigate_sprite);

  sprites_.submarine_sprite.setTexture(images->GetSubmarine());
  sprites_.submarine_sprite.setScale(
      Shipyard::kSubmarineInfo.length * float(render_data::kTileSide) / float(images->GetSubmarine().getSize().x),
      Shipyard::kSubmarineInfo.width * float(render_data::kTileSide) / float(images->GetSubmarine().getSize().y));
  SetCenter(sprites_.submarine_sprite);

  sprites_.cruiser_sprite.setTexture(images->GetCruiser());
  sprites_.cruiser_sprite.setScale(
      Shipyard::kCruiserInfo.length * float(render_data::kTileSide) / float(images->GetCruiser().getSize().x),
      Shipyard::kCruiserInfo.width * float(render_data::kTileSide) / float(images->GetCruiser().getSize().y));
  SetCenter(sprites_.cruiser_sprite);

  sprites_.carrier_sprite.setTexture(images->GetCarrier());
  sprites_.carrier_sprite.setScale(
      Shipyard::kCarrierInfo.length * float(render_data::kTileSide) / float(images->GetCarrier().getSize().x),
      Shipyard::kCarrierInfo.width * float(render_data::kTileSide) / float(images->GetCarrier().getSize().y));
  SetCenter(sprites_.carrier_sprite);
}

void SFMLRenderer::AssignWeapons(std::shared_ptr<ImageStorage>& images) {
  sprites_.gun_sprite_.setTexture(images->GetGun());
  sprites_.gun_sprite_.setScale(
      0.5f * float(render_data::kTileSide) / float(images->GetGun().getSize().x),
      0.5f * float(render_data::kTileSide) / float(images->GetGun().getSize().y));
  SetCenter(sprites_.gun_sprite_);

  sprites_.flare_gun_sprite.setTexture(images->GetFlareGun());
  sprites_.flare_gun_sprite.setScale(
      0.5f * float(render_data::kTileSide) / float(images->GetFlareGun().getSize().x),
      0.5f * float(render_data::kTileSide) / float(images->GetFlareGun().getSize().y));
  SetCenter(sprites_.flare_gun_sprite);

  sprites_.mortar_sprite.setTexture(images->GetMortar());
  sprites_.mortar_sprite.setScale(
      0.5f * float(render_data::kTileSide) / float(images->GetMortar().getSize().x),
      0.5f * float(render_data::kTileSide) / float(images->GetMortar().getSize().y));
  SetCenter(sprites_.mortar_sprite);

  sprites_.bang_sprite.setTexture(images->GetBang());
  sprites_.bang_sprite.setScale(
      0.5f * float(render_data::kTileSide) / float(images->GetBang().getSize().x),
      0.5f * float(render_data::kTileSide) / float(images->GetBang().getSize().y));
  SetCenter(sprites_.bang_sprite);
}

void SFMLRenderer::AssignField(std::shared_ptr<ImageStorage>& images) {
  sprites_.water_sprite.setTexture(images->GetWater());
  sprites_.water_sprite.setScale(float(render_data::kTileSide) / float(images->GetWater().getSize().x),
                                 float(render_data::kTileSide) / float(images->GetWater().getSize().y));
  SetCenter(sprites_.water_sprite);
}

void SFMLRenderer::SetCenter(sf::Sprite& sprite) {
  sprite.setOrigin(sprite.getPosition().x + float(sprite.getTexture()->getSize().x) / 2.f,
                   sprite.getPosition().y + float(sprite.getTexture()->getSize().y) / 2.f);
}

void SFMLRenderer::SetRotation(sf::Sprite& sprite, BoundaryBox::FacingDirection facing) {
  switch (facing) {
    case BoundaryBox::FacingDirection::kUp : {
      sprite.setRotation(90);
      break;
    }
    case BoundaryBox::FacingDirection::kDown: {
      sprite.setRotation(270);
      break;
    }
    case BoundaryBox::FacingDirection::kLeft: {
      sprite.setRotation(180);
      break;
    }
    case BoundaryBox::FacingDirection::kRight: {
      sprite.setRotation(0);
      break;
    }
  }
}
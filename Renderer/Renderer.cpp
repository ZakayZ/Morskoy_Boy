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
  sprites_.fighter_sprite.setTexture(images->GetFighter());
  sprites_.fighter_sprite.setScale(
      Shipyard::kFighterInfo.length * float(render_data::kTileSide) / images->GetFighter().getSize().x,
      Shipyard::kFighterInfo.width * float(render_data::kTileSide) / images->GetFighter().getSize().y);
  SetCenter(sprites_.fighter_sprite);

  sprites_.frigate_sprite.setTexture(images->GetFrigate());
  sprites_.frigate_sprite.setScale(
      Shipyard::kFrigateInfo.length * float(render_data::kTileSide) / images->GetFrigate().getSize().x,
      Shipyard::kFrigateInfo.width * float(render_data::kTileSide) / float(images->GetFrigate().getSize().y));
  SetCenter(sprites_.frigate_sprite);

  sprites_.submarine_sprite.setTexture(images->GetSubmarine());
  sprites_.submarine_sprite.setScale(
      Shipyard::kSubmarineInfo.length * float(render_data::kTileSide) / images->GetSubmarine().getSize().x,
      Shipyard::kSubmarineInfo.width * float(render_data::kTileSide) / float(images->GetSubmarine().getSize().y));
  SetCenter(sprites_.submarine_sprite);

  sprites_.cruiser_sprite.setTexture(images->GetCruiser());
  sprites_.cruiser_sprite.setScale(
      Shipyard::kCruiserInfo.length * float(render_data::kTileSide) / images->GetCruiser().getSize().x,
      Shipyard::kCruiserInfo.width * float(render_data::kTileSide) / float(images->GetCruiser().getSize().y));
  SetCenter(sprites_.cruiser_sprite);

  sprites_.carrier_sprite.setTexture(images->GetCarrier());
  sprites_.carrier_sprite.setScale(
      Shipyard::kCarrierInfo.length * float(render_data::kTileSide) / images->GetCarrier().getSize().x,
      Shipyard::kCarrierInfo.width * float(render_data::kTileSide) / float(images->GetCarrier().getSize().y));
  SetCenter(sprites_.carrier_sprite);

  sprites_.water_sprite.setTexture(images->GetWater());
  sprites_.water_sprite.setScale(float(render_data::kTileSide) / images->GetWater().getSize().x,
                                 float(render_data::kTileSide) / images->GetWater().getSize().y);
  SetCenter(sprites_.water_sprite);
}

void SFMLRenderer::Render(const Ship& ship, const Coords& offset, bool my_view) {
  if (my_view || ship.GetMark() > 0) {
    auto ship_box = ship.GetPosition();
    auto position = ship_box.GetCenter();
    sf::Sprite& ship_sprite = ShipSprite(ship.GetType());
    ShipRotation(ship_sprite, ship_box.GetFacingDirection());
    if (ship.IsDead()) {
      ship_sprite.setColor(sf::Color::Red);
    }
    ship_sprite.setPosition(position.x * render_data::kTileSide, position.y * render_data::kTileSide);
    window_->draw(ship_sprite);
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

void SFMLRenderer::Render(std::shared_ptr<Weapon> weapon, const Coords& offset, bool my_view) {
  if (my_view) {
    sf::CircleShape weapon(render_data::kTileSide / 2.);
    weapon.setPosition(offset.x, offset.y);
    weapon.setFillColor(sf::Color::Red);
    window_->draw(weapon);
  }
}

void SFMLRenderer::SetCenter(sf::Sprite& sprite) {
  sprite.setOrigin(sprite.getPosition().x + sprite.getTexture()->getSize().x / 2,
                   sprite.getPosition().y + sprite.getTexture()->getSize().y / 2);
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

void SFMLRenderer::ShipRotation(sf::Sprite& sprite, BoundaryBox::FacingDirection facing) {
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

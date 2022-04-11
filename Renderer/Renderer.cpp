#include "Renderer.h"

Renderer::~Renderer() = default;

ConsoleRenderer::ConsoleRenderer(std::shared_ptr<ConsoleWindow>& window) : Renderer(), window_(window) {}

void ConsoleRenderer::Render(const Ship& ship, const Coords& offset, bool my_view) const {
  if (my_view || ship.GetMark() > 0) {
    auto ship_box = ship.GetPosition();
    auto& hull = ship.GetHull();
    auto width = ship_box.GetWidth();
    auto position = ship_box.GetLeftUpperCorner();
    RectangleShape rect(offset.x + position.x, offset.y + position.y, 0, 0, '*');
    switch (ship_box.GetFacingDirection()) {
      case BoundaryBox::FacingDirection::kUp: {
        rect.SetSize(width, 1);
        for (const auto& tile : hull) {
          window_->Draw(rect);
          rect.Move(0, 1);
        }
        break;
      }
      case BoundaryBox::FacingDirection::kDown: {
        rect.SetSize(width, 1);
        for (const auto& tile : hull) {
          window_->Draw(rect);
          rect.Move(0, 1);
        }
        break;
      }
      case BoundaryBox::FacingDirection::kLeft: {
        rect.SetSize(1, width);
        for (const auto& tile : hull) {
          window_->Draw(rect);
          rect.Move(1, 0);
        }
        break;
      }
      case BoundaryBox::FacingDirection::kRight: {
        rect.SetSize(1, width);
        for (const auto& tile : hull) {
          window_->Draw(rect);
          rect.Move(1, 0);
        }
        break;
      }
    }
  }
}

void ConsoleRenderer::Render(const Field& field, const Coords& offset, bool my_view) const {
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

void ConsoleRenderer::Render(const Player& player, const Coords& offset, bool my_view) const {
  auto& field = player.GetField();
  Render(field, offset, my_view);
  auto& ships = player.GetFleet();
  for (const auto& ship : ships) {
    Render(ship, offset, my_view);
  }
}

SFMLRenderer::SFMLRenderer(std::shared_ptr<sf::RenderWindow>& window) : Renderer(), window_(window) {}

void SFMLRenderer::Render(const Ship& ship, const Coords& offset, bool my_view) const {
  if (my_view || ship.GetMark() > 0) {
    auto ship_box = ship.GetPosition();
    auto& hull = ship.GetHull();
    auto width = ship_box.GetWidth();
    auto position = ship_box.GetLeftUpperCorner();
    sf::RectangleShape rect;
    if(ship.IsDead()) {
      rect.setFillColor(sf::Color::Red);
    }else{
      rect.setFillColor(sf::Color::Cyan);
    }
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color::Black);
    rect.setPosition(offset.x + position.x * render_data::kTileSide, offset.y + position.y * render_data::kTileSide);
    switch (ship_box.GetFacingDirection()) {
      case BoundaryBox::FacingDirection::kUp: {
        rect.setSize(sf::Vector2f(render_data::kTileSide * width, render_data::kTileSide));
        for (const auto& tile : hull) {
          window_->draw(rect);
          rect.move(0, render_data::kTileSide);
        }
        break;
      }
      case BoundaryBox::FacingDirection::kDown: {
        rect.setSize(sf::Vector2f(render_data::kTileSide * width, render_data::kTileSide));
        for (const auto& tile : hull) {
          window_->draw(rect);
          rect.move(0, render_data::kTileSide);
        }
        break;
      }
      case BoundaryBox::FacingDirection::kLeft: {
        rect.setSize(sf::Vector2f(render_data::kTileSide, render_data::kTileSide * width));
        for (const auto& tile : hull) {
          window_->draw(rect);
          rect.move(render_data::kTileSide, 0);
        }
        break;
      }
      case BoundaryBox::FacingDirection::kRight: {
        rect.setSize(sf::Vector2f(render_data::kTileSide, render_data::kTileSide * width));
        for (const auto& tile : hull) {
          window_->draw(rect);
          rect.move(render_data::kTileSide, 0);
        }
        break;
      }
    }
  }
}

void SFMLRenderer::Render(const Field& field, const Coords& offset, bool my_view) const {
  auto& grid = field.GetGrid();
  sf::RectangleShape rect;
  rect.setFillColor(sf::Color::Magenta);
  rect.setOutlineThickness(1);
  rect.setOutlineColor(sf::Color::Black);
  rect.setSize(sf::Vector2f(render_data::kTileSide, render_data::kTileSide));
  rect.setPosition(offset.x, offset.y);
  window_->draw(rect);
  for (const auto& row : grid) {
    for (const auto& cell : row) {
      window_->draw(rect);
      rect.move(render_data::kTileSide, 0);
    }
    rect.setPosition(offset.x, rect.getPosition().y);
    rect.move(0, render_data::kTileSide);
  }
}

void SFMLRenderer::Render(const Player& player, const Coords& offset, bool my_view) const {
  auto& field = player.GetField();
  Render(field, offset, my_view);
  auto& ships = player.GetFleet();
  for (const auto& ship : ships) {
    Render(ship, offset, my_view);
  }
}

void SFMLRenderer::Render(std::shared_ptr<Weapon> weapon, const Coords& offset, bool my_view) const {
  if (my_view) {
    sf::CircleShape weapon(render_data::kTileSide / 2.);
    weapon.setPosition(offset.x, offset.y);
    weapon.setFillColor(sf::Color::Red);
    window_->draw(weapon);
  }
}

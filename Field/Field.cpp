#include "includes.h"
#include "Field.h"

Field::Field(size_t horizontal_size, size_t vertical_size)
    : x_size_(horizontal_size), y_size_(vertical_size), grid_(horizontal_size, vector<Cell>(vertical_size)) {}

bool Field::IsValidCoord(const Coords& coords) const {
  return coords.x < x_size_ && coords.y < y_size_;
}

bool Field::IsValidBox(const BoundaryBox& box) const {
  auto borders = box.GetCoords();
  return IsValidCoord(borders.first) && IsValidCoord(borders.second);
}

void Field::Display(sf::RenderWindow& window, const Coords& offset, bool my_view) const {
  sf::RectangleShape rect;
  rect.setFillColor(sf::Color::Magenta);
  for (size_t i = 0; i < grid_.size(); ++i) {
    rect.setPosition(offset.x, offset.y + i * temporary::kTileSide);
    for (size_t j = 0; j < grid_[i].size(); ++j) {
      window.draw(rect);
      rect.move(temporary::kTileSide, 0);
    }
  }
}

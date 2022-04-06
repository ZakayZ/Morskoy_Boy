#include "ConsoleWindow.h"

Shape::Shape(int x, int y, uint8_t value) : x_(x), y_(y), value_(value) {}

void Shape::SetPosition(int x, int y) {
  x_ = x;
  y_ = y;
}

void Shape::SetValue(uint8_t new_value) {
  value_ = new_value;
}

void Shape::Move(int dx, int dy) {
  x_ += dx;
  y_ += dy;
}

std::pair<int, int> Shape::GetPosition() const {
  return {x_, y_};
}

uint8_t Shape::GetValue() const {
  return value_;
}

PixelShape::PixelShape(int x, int y, uint8_t value) : Shape(x, y, value) {}

RectangleShape::RectangleShape(int x, int y, int w, int h, uint8_t value)
    : Shape(x, y, value), width_(w), height_(h), outline_thickness_(0), outline_value_(' ') {}

void RectangleShape::SetSize(int w, int h) {
  width_ = w;
  height_ = h;
}

void RectangleShape::SetOutlineValue(uint8_t new_value) {
  outline_value_ = new_value;
}

void RectangleShape::SetOutlineThickness(int thickness) {
  outline_thickness_ = thickness;
}

uint8_t RectangleShape::GetOutlineValue() const {
  return outline_value_;
}

uint8_t RectangleShape::GetOutlineThickness() const {
  return outline_thickness_;
}

std::pair<int, int> RectangleShape::GetSize() const {
  return {width_, height_};
}

CircleShape::CircleShape(int x, int y, int r, uint8_t value) : Shape(x, y, value),
                                                               radius_(r),
                                                               outline_thickness_(0),
                                                               outline_value_(' ') {}

void CircleShape::SetRadius(int new_radius) {
  radius_ = new_radius;
}

void CircleShape::SetOutlineValue(uint8_t new_value) {
  outline_value_ = new_value;
}

void CircleShape::SetOutlineThickness(int thickness) {
  outline_thickness_ = thickness;
}

uint8_t CircleShape::GetOutlineValue() const {
  return outline_value_;
}

uint8_t CircleShape::GetOutlineThickness() const {
  return outline_thickness_;
}

int CircleShape::GetRadius() const {
  return radius_;
}

ConsoleWindow::ConsoleWindow(size_t width, size_t height) : screen_(height, string(width, ' ')) {}

void ConsoleWindow::Display() const {
  for (const auto& str : screen_) {
    cout << str << '\n';
  }
}

void ConsoleWindow::Clear() {
  std::system("clear");
  for (auto& str : screen_) {
    for (auto& ch : str) {
      ch = ' ';
    }
  }
}

void ConsoleWindow::Draw(const PixelShape& pixel) {
  auto pos = pixel.GetPosition();
  auto value = pixel.GetValue();
  if (IsValid(pos.first, pos.second)) {
    operator[](pos) = value;
  }
}

void ConsoleWindow::Draw(const RectangleShape& rectangle) {
  auto pos = rectangle.GetPosition();
  auto size = rectangle.GetSize();
  auto outline_size = rectangle.GetOutlineThickness();
  auto value = rectangle.GetValue();
  auto outline_value = rectangle.GetOutlineValue();
  for (int i = std::max(0, pos.second); i < std::min(pos.second + size.second, int(screen_.size())); ++i) {
    for (int j = std::max(0, pos.first); j < std::min(pos.first + size.first, int(screen_.back().size())); ++j) {
      if (i - pos.second < outline_size && j - pos.first < outline_size
          || pos.second + size.second - i < outline_size && pos.first + size.first - j < outline_size) {
        screen_[i][j] = outline_value;
      } else {
        screen_[i][j] = value;
      }
    }
  }
}

void ConsoleWindow::Draw(const CircleShape& circle) {
  auto pos = circle.GetPosition();
  auto rad = circle.GetRadius();
  auto outline_size = circle.GetOutlineThickness();
  auto value = circle.GetValue();
  auto outline_value = circle.GetOutlineValue();
  for (int i = std::max(0, pos.second); i < std::min(pos.second + 2 * rad, int(screen_.size())); ++i) {
    for (int j = std::max(0, pos.first); j < std::min(pos.first + 2 * rad, int(screen_.back().size())); ++j) {
      if ((i - rad) * (i - rad) + (j - rad) * (j - rad) <= rad * rad) {
        if ((i - rad) * (i - rad) + (j - rad) * (j - rad) > (rad - outline_size) * (rad - outline_size)) {
          screen_[i][j] = outline_value;
        } else {
          screen_[i][j] = value;
        }
      }
    }
  }
}

char& ConsoleWindow::operator[](const std::pair<int, int>& pos) {
  return screen_[pos.second][pos.first];
}

bool ConsoleWindow::IsValid(int x, int y) const {
  return x >= 0 && y >= 0 && y < screen_.size() && x < screen_.back().size();
}

#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cin;
using std::cout;

class Shape {
 public:
  Shape(int, int, uint8_t);
  void SetPosition(int, int);
  void SetValue(uint8_t);
  void Move(int, int);
  [[nodiscard]] std::pair<int, int> GetPosition() const;
  [[nodiscard]] uint8_t GetValue() const;
  virtual ~Shape() = default;
 protected:
  int x_;
  int y_;
  uint8_t value_;
};

class PixelShape : public Shape {
 public:
  PixelShape(int, int, uint8_t);
  ~PixelShape() override = default;
 private:
};

class RectangleShape : public Shape {
 public:
  RectangleShape(int, int, int, int, uint8_t);
  void SetSize(int, int);
  void SetOutlineValue(uint8_t);
  void SetOutlineThickness(int);
  [[nodiscard]] uint8_t GetOutlineValue() const;
  [[nodiscard]] int GetOutlineThickness() const;
  [[nodiscard]] std::pair<int, int> GetSize() const;
  ~RectangleShape() override = default;
 private:
  int width_;
  int height_;
  int outline_thickness_;
  uint8_t outline_value_;
};

class CircleShape : public Shape {
 public:
  CircleShape(int, int, int, uint8_t);
  void SetRadius(int);
  void SetOutlineValue(uint8_t);
  void SetOutlineThickness(int);
  [[nodiscard]] uint8_t GetOutlineValue() const;
  [[nodiscard]] int GetOutlineThickness() const;
  [[nodiscard]] int GetRadius() const;
  ~CircleShape() override = default;
 private:
  int radius_;
  int outline_thickness_;
  uint8_t outline_value_;
};

class ConsoleWindow {
 public:
  ConsoleWindow(size_t, size_t);
  void Draw(const PixelShape&);
  void Draw(const RectangleShape&);
  void Draw(const CircleShape&);
  void Display() const;
  void Clear();
  ~ConsoleWindow() = default;
 private:
  char& operator[](const std::pair<int, int>&);
  [[nodiscard]] bool IsValid(int, int) const;

  vector<string> screen_;
};

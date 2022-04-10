#include "Shipyard.h"
#include <memory>
#include <cassert>



Ship Shipyard::Make(ShipType type) const {
  switch (type) {
    case ShipType::Fighter: { return MakeFighter(); }
    case ShipType::Frigate: { return MakeFrigate(); }
    case ShipType::Destroyer: { return MakeDestroyer(); }
    case ShipType::Cruiser: { return MakeCruiser(); }
    case ShipType::Mothership: { return MakeMothership(); }
  }
}

size_t Shipyard::GetPrice(ShipType ship_type) const {
  switch (ship_type) {
    case ShipType::Fighter: { return Shipyard::kFighterPrice; }
    case ShipType::Frigate: { return Shipyard::kFrigatePrice; }
    case ShipType::Destroyer: { return Shipyard::kDestroyerPrice; }
    case ShipType::Cruiser: { return Shipyard::kCruiserPrice; }
    case ShipType::Mothership: { return Shipyard::kMothershipPrice; }
  }
}

Ship Shipyard::MakeFighter() const {
  auto gun = std::make_shared<Gun>();
  static size_t length = 1;
  static size_t width = 1;
  static BoundaryBox box({0, width}, {length, 0});
  static vector<size_t> hp = {5};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

Ship Shipyard::MakeFrigate() const {
  auto gun = std::make_shared<FlareGun>();
  static size_t length = 2;
  static size_t width = 1;
  static BoundaryBox box({0, width}, {length, 0});
  static vector<size_t> hp = {6, 6};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

Ship Shipyard::MakeDestroyer() const {
  auto gun = std::make_shared<Mortar>();
  static size_t length = 3;
  static size_t width = 1;
  static BoundaryBox box({0, width}, {length, 0});
  static vector<size_t> hp = {8, 9, 8};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

Ship Shipyard::MakeCruiser() const {
  //TODO WIP
  auto gun = std::make_shared<Mortar>();
  static size_t length = 4;
  static size_t width = 1;
  static BoundaryBox box({0, width}, {length, 0});
  static vector<size_t> hp = {10, 12, 12, 10};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

Ship Shipyard::MakeMothership() const {
  //TODO WIP
  auto gun = std::make_shared<Mortar>();
  static size_t length = 3;
  static size_t width = 3;
  static BoundaryBox box({0, width}, {length, 0});
  static vector<size_t> hp = {5, 100, 5};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

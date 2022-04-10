#include "Shipyard.h"
#include <memory>
#include <cassert>



Ship Shipyard::Make(ShipType type, Coords cords) const {
  switch (type) {
    case ShipType::Fighter: { return MakeFighter(cords); }
    case ShipType::Frigate: { return MakeFrigate(cords); }
    case ShipType::Destroyer: { return MakeDestroyer(cords); }
    case ShipType::Cruiser: { return MakeCruiser(cords); }
    case ShipType::Mothership: { return MakeMothership(cords); }
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

Ship Shipyard::MakeFighter(Coords cords) const {
  auto gun = std::make_shared<Gun>();
  static size_t length = 1;
  static size_t width = 1;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {5};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

Ship Shipyard::MakeFrigate(Coords cords) const {
  auto gun = std::make_shared<FlareGun>();
  static size_t length = 2;
  static size_t width = 1;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {6, 6};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

Ship Shipyard::MakeDestroyer(Coords cords) const {
  auto gun = std::make_shared<Mortar>();
  static size_t length = 3;
  static size_t width = 1;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {8, 9, 8};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

Ship Shipyard::MakeCruiser(Coords cords) const {
  //TODO WIP
  auto gun = std::make_shared<Mortar>();
  static size_t length = 4;
  static size_t width = 1;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {10, 12, 12, 10};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

Ship Shipyard::MakeMothership(Coords cords) const {
  //TODO WIP
  auto gun = std::make_shared<Mortar>();
  static size_t length = 3;
  static size_t width = 3;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {5, 100, 5};
  assert(hp.size() == length);
  return Ship(box, hp, gun);
}

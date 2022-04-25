#include "Shipyard.h"
#include <memory>
#include <cassert>

Ship Shipyard::Make(ShipType type, Coords cords) const {
  switch (type) {
    case ShipType::Fighter: { return MakeFighter(cords); }
    case ShipType::Frigate: { return MakeFrigate(cords); }
    case ShipType::Submarine: { return MakeSubmarine(cords); }
    case ShipType::Cruiser: { return MakeCruiser(cords); }
    case ShipType::Carrier: { return MakeCarrier(cords); }
  }
}

size_t Shipyard::GetPrice(ShipType ship_type) const {
  switch (ship_type) {
    case ShipType::Fighter: { return kFighterInfo.price; }
    case ShipType::Frigate: { return kFrigateInfo.price; }
    case ShipType::Submarine: { return kSubmarineInfo.price; }
    case ShipType::Cruiser: { return kCruiserInfo.price; }
    case ShipType::Carrier: { return kCarrierInfo.price; }
  }
}

Ship Shipyard::MakeFighter(Coords cords) const {
  auto gun = std::make_shared<Gun>();
  static size_t length = kFighterInfo.length;
  static size_t width = kFighterInfo.width;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {5};
  assert(hp.size() == length);
  return {ShipType::Fighter, box, hp, gun};
}

Ship Shipyard::MakeFrigate(Coords cords) const {
  auto gun = std::make_shared<FlareGun>();
  static size_t length = kFrigateInfo.length;
  static size_t width = kFrigateInfo.width;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {6, 6};
  assert(hp.size() == length);
  return {ShipType::Frigate, box, hp, gun};
}

Ship Shipyard::MakeSubmarine(Coords cords) const {
  auto gun = std::make_shared<Mortar>();
  static size_t length = kSubmarineInfo.length;
  static size_t width = kSubmarineInfo.width;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {8, 9, 8};
  assert(hp.size() == length);
  return {ShipType::Submarine, box, hp, gun};
}

Ship Shipyard::MakeCruiser(Coords cords) const {
  //TODO
  auto gun = std::make_shared<Mortar>();
  static size_t length = kCruiserInfo.length;
  static size_t width = kCruiserInfo.width;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {10, 12, 12, 10};
  assert(hp.size() == length);
  return {ShipType::Cruiser, box, hp, gun};
}

Ship Shipyard::MakeCarrier(Coords cords) const {
  //TODO
  auto gun = std::make_shared<Mortar>();
  static size_t length = kCarrierInfo.length;
  static size_t width = kCarrierInfo.width;
  BoundaryBox box({width + cords.x, length + cords.y}, cords);
  static vector<size_t> hp = {5, 100, 100, 5};
  assert(hp.size() == length);
  return {ShipType::Carrier, box, hp, gun};
}

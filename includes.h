#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

using std::vector;
using std::string;
using std::cout;
using std::cin;

enum class Error;
class Projectile;
class Weapon;
class BoundaryBox;
class Ship;
enum class ShipType;
class Shipyard;
class Field;
class Player;
class Action;
class ActionGenerator;
class GameMaster;
class Renderer;

struct Coords {
  size_t x;
  size_t y;
};

#include "Error.h"
#include "Weapons/Projectile.h"
#include "Weapons/Weapon.h"
#include "Ships/BoundaryBox.h"
#include "Ships/Ship.h"
#include "Ships/ShipType.h"
#include "Ships/Shipyard.h"
#include "Field/Field.h"
#include "Player/Player.h"
#include "Action/Action.h"
#include "Action/ActionGenerator.h"
#include "GameMaster/GameMaster.h"
#include "Renderer/Renderer.h"
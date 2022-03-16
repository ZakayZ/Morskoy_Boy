#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <memory>

#ifndef SHIPS_MORSKOY_BOY_INCLUDES_
#define SHIPS_MORSKOY_BOY_INCLUDES_

using std::vector;
using std::string;
using std::cout;
using std::cin;

class Ship;
class Weapon;
class Field;
class Player;
class Action;
class GameMaster;

struct Coords{
  size_t x;
  size_t y;
};

#include "Error.h"
#include "Weapons/Projectile.h"
#include "Ships/Ship.h"
#include "Weapons/Weapon.h"
#include "Field/Field.h"
#include "Player/Player.h"
#include "Action/Action.h"
#include "GameMaster/GameMaster.h"

#endif //SHIPS_MORSKOY_BOY_INCLUDES_
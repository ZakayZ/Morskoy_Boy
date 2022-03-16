#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <memory>

#ifndef SHIPS_MORSKOY_BOY_INCLUDES_
#define SHIPS_MORSKOY_BOY_INCLUDES_

using std::vector;
using std::cout;
using std::cin;

class Ship;
class Weapon;
class Player;
class Action;
class GameMaster;
class Field;
class Bullet;

struct Coords{
  size_t x;
  size_t y;
};

#include "Weapons/Projectile.h"
#include "Ships/Ship.h"
#include "Weapons/Weapon.h"
#include "Action/Action.h"
#include "Player/Player.h"
#include "GameMaster/GameMaster.h"
#include "Field/Field.h"
#include "Bullet/Bullet.h"

#endif //SHIPS_MORSKOY_BOY_INCLUDES_
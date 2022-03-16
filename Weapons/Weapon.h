#pragma once

#include "../includes.h"

#ifndef SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_
#define SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_

class Weapon {
 public:
  Fire();
  Reload();
 private:
  size_t reload_counter_;
  static const size_t kTimeToReload;
};

#endif //SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_

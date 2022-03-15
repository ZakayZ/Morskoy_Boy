#pragma once

#include "../includes.h"

#ifndef SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_
#define SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_

class Weapon {
 public:
  virtual Fire();
  virtual Reload();
  virtual
 private:
  size_t reload_counter_;
  vector<vector<uint64_t>> damage_kernel_;
  size_t time_;
};

#endif //SHIPS_MORSKOY_BOY_WEAPONS_WEAPON_H_

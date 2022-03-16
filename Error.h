#pragma once

#ifndef SHIPS_MORSKOY_BOY_ERROR_H_
#define SHIPS_MORSKOY_BOY_ERROR_H_

enum class Error{
  kNoError,
  kInvalidShip,
  kInvalidTarget,
  kShipIsDead,
  kIntersectsFieldBoundary,
  kIntersectsShip,
  kWeaponOnCooldown,
  kOutOfActions,
};

#endif //SHIPS_MORSKOY_BOY_ERROR_H_

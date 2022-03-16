#pragma once

#ifndef SHIPS_MORSKOY_BOY_ERROR_H_
#define SHIPS_MORSKOY_BOY_ERROR_H_

enum class Error{
  kNoError,
  kInvalidId,
  kInvalidTarget,
  kIntersectsFieldBoundary,
  kIntersectsShip,
  kWeaponOnCooldown,
};

#endif //SHIPS_MORSKOY_BOY_ERROR_H_

#pragma once

enum class Error {
  kNoError,
  kInvalidShip,
  kInvalidTarget,
  kShipIsDead,
  kIntersectsFieldBoundary,
  kIntersectsShip,
  kWeaponOnCooldown,
  kOutOfActions,
  kOutOfMoney,
};

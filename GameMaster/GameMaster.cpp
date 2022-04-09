#include "GameMaster.h"



Error GameMaster::CheckAction(const Action&) const {
  return Error::kIntersectsFieldBoundary;
}

void GameMaster::ManageAction(const Action&) {

}

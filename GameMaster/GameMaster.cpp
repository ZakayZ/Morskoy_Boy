#include "includes.h"

GameMaster::GameMaster() {

}

Error GameMaster::CheckAction(const Action&) const {
  return Error::kIntersectsFieldBoundary;
}
void GameMaster::MakeAction(const Action&) {

}

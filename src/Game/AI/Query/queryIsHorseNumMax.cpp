#include "Game/AI/Query/queryIsHorseNumMax.h"
#include <evfl/Query.h>
#include "Game/gameHorseMgr.h"

namespace uking::query {

IsHorseNumMax::IsHorseNumMax(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsHorseNumMax::~IsHorseNumMax() = default;

int IsHorseNumMax::doQuery() {
    return HorseMgr::instance()->getNumRegisteredHorses() > 4;
}

void IsHorseNumMax::loadParams(const evfl::QueryArg& arg) {}

void IsHorseNumMax::loadParams() {}

}  // namespace uking::query

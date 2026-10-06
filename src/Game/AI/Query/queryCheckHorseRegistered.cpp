#include "Game/AI/Query/queryCheckHorseRegistered.h"
#include <evfl/Query.h>
#include "Game/gameHorseMgr.h"

namespace uking::query {

CheckHorseRegistered::CheckHorseRegistered(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckHorseRegistered::~CheckHorseRegistered() = default;

int CheckHorseRegistered::doQuery() {
    return HorseMgr::instance()->getNumRegisteredHorses() > 0;
}

void CheckHorseRegistered::loadParams(const evfl::QueryArg& arg) {}

void CheckHorseRegistered::loadParams() {}

}  // namespace uking::query

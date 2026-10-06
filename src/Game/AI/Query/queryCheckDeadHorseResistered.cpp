#include "Game/AI/Query/queryCheckDeadHorseResistered.h"
#include <evfl/Query.h>
#include "Game/gameHorseMgr.h"

namespace uking::query {

CheckDeadHorseResistered::CheckDeadHorseResistered(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckDeadHorseResistered::~CheckDeadHorseResistered() = default;

int CheckDeadHorseResistered::doQuery() {
    auto* mgr = HorseMgr::instance();
    if (mgr)
        return mgr->getNumDeadHorsesRegistered() > 0;
    return 0;
}

void CheckDeadHorseResistered::loadParams(const evfl::QueryArg& arg) {}

void CheckDeadHorseResistered::loadParams() {}

}  // namespace uking::query

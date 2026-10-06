#include "Game/AI/Query/queryIsHorseFamiliarityPassedAlready.h"
#include <evfl/Query.h>
#include "Game/gameHorseMgr.h"

namespace uking::query {

IsHorseFamiliarityPassedAlready::IsHorseFamiliarityPassedAlready(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

IsHorseFamiliarityPassedAlready::~IsHorseFamiliarityPassedAlready() = default;

int IsHorseFamiliarityPassedAlready::doQuery() {
    auto* mgr = HorseMgr::instance();
    if (mgr)
        return mgr->isSelectedHorseFamiliarityChecked();
    return 0;
}

void IsHorseFamiliarityPassedAlready::loadParams(const evfl::QueryArg& arg) {}

void IsHorseFamiliarityPassedAlready::loadParams() {}

}  // namespace uking::query

#include "Game/AI/Query/queryCheckTypeOfOwnedHorseForEvent.h"
#include <evfl/Query.h>
#include "Game/gameHorseMgr.h"

namespace uking::query {

CheckTypeOfOwnedHorseForEvent::CheckTypeOfOwnedHorseForEvent(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckTypeOfOwnedHorseForEvent::~CheckTypeOfOwnedHorseForEvent() = default;

// NON_MATCHING: the original keeps `type` at sp+8 (ours at sp+0xc); stack slot placement only.
int CheckTypeOfOwnedHorseForEvent::doQuery() {
    auto* mgr = HorseMgr::instance();
    if (mgr) {
        HorseMgr::RiddenAnimalType type;
        mgr->sub_7100E8612C(&type);
        return type == HorseMgr::RiddenAnimalType::_6;
    }
    return 0;
}

void CheckTypeOfOwnedHorseForEvent::loadParams(const evfl::QueryArg& arg) {}

void CheckTypeOfOwnedHorseForEvent::loadParams() {}

}  // namespace uking::query

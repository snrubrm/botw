#include "Game/AI/Query/queryCheckOwnedHorseFamiliarity.h"
#include <evfl/Query.h>
#include "Game/Actor/actHorseBase.h"
#include "Game/gameHorseMgr.h"

namespace uking::query {

CheckOwnedHorseFamiliarity::CheckOwnedHorseFamiliarity(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckOwnedHorseFamiliarity::~CheckOwnedHorseFamiliarity() = default;

int CheckOwnedHorseFamiliarity::doQuery() {
    auto* mgr = HorseMgr::instance();
    if (mgr && mgr->mOwnedHorse.hasProc()) {
        if (auto* horse = sead::DynamicCast<act::HorseBase>(mgr->mOwnedHorse.getProc(nullptr, nullptr))) {
            const f32 familiarity = horse->sub_7100E6AD4C();
            if (familiarity >= 0.0f && familiarity < 0.3f)
                return 0;
            if (familiarity >= 0.3f && familiarity < 0.6f)
                return 1;
            if (familiarity >= 0.6f && familiarity < 1.0f)
                return 2;
            if (familiarity == 1.0f)
                return 3;
        }
    }
    return 0;
}

void CheckOwnedHorseFamiliarity::loadParams(const evfl::QueryArg& arg) {}

void CheckOwnedHorseFamiliarity::loadParams() {}

}  // namespace uking::query

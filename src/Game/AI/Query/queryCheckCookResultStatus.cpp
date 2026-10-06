#include "Game/AI/Query/queryCheckCookResultStatus.h"
#include <evfl/Query.h>
#include "Game/Cooking/cookManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::query {

CheckCookResultStatus::CheckCookResultStatus(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckCookResultStatus::~CheckCookResultStatus() = default;

int CheckCookResultStatus::doQuery() {
    if (auto* mgr = CookingMgr::instance()) {
        CookItem item;
        mgr->getCookItem(item);
        const s32 type = *mCheckType;
        if (type == 0)
            return !ksys::act::hasTag(item.actor_name, ksys::act::tags::CookFailure);
        if (type == 1)
            return item.is_crit;
    }
    return 0;
}

void CheckCookResultStatus::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckType");
}

void CheckCookResultStatus::loadParams() {
    getDynamicParam(&mCheckType, "CheckType");
    getAITreeVariable(&mCurrentCookResultHolder, "CurrentCookResultHolder");
}

}  // namespace uking::query

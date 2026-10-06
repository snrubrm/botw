#include "Game/AI/Query/queryCheckTerrorLevel.h"
#include <evfl/Query.h>
#include "Game/Actor/actNPC.h"

namespace uking::query {

CheckTerrorLevel::CheckTerrorLevel(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckTerrorLevel::~CheckTerrorLevel() = default;

int CheckTerrorLevel::doQuery() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        return npc->_c74;
    return 0;
}

void CheckTerrorLevel::loadParams(const evfl::QueryArg& arg) {}

void CheckTerrorLevel::loadParams() {}

}  // namespace uking::query

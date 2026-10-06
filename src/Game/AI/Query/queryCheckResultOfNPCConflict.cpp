#include "Game/AI/Query/queryCheckResultOfNPCConflict.h"
#include <evfl/Query.h>
#include "Game/Actor/actNPC.h"

namespace uking::query {

CheckResultOfNPCConflict::CheckResultOfNPCConflict(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckResultOfNPCConflict::~CheckResultOfNPCConflict() = default;

// NON_MATCHING: same logic, but the original materializes the clamp constant 3 separately from the
// "no NPC" return value (extra register move in ours).
int CheckResultOfNPCConflict::doQuery() {
    auto* npc = sead::DynamicCast<act::NPC>(mActor);
    if (!npc)
        return 3;
    return npc->_1048 < 3 ? npc->_1048 : 3;
}

void CheckResultOfNPCConflict::loadParams(const evfl::QueryArg& arg) {}

void CheckResultOfNPCConflict::loadParams() {}

}  // namespace uking::query

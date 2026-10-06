#include "Game/AI/Query/queryCheckRankOfEnemyAttackedNPC.h"
#include <evfl/Query.h>
#include "Game/Actor/actNPC.h"

namespace uking::query {

CheckRankOfEnemyAttackedNPC::CheckRankOfEnemyAttackedNPC(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckRankOfEnemyAttackedNPC::~CheckRankOfEnemyAttackedNPC() = default;

// NON_MATCHING: same logic; the original compares with `cmp #0x14, ge` / `cmp #0xa, lt` (signed >= 20 /
// < 10 after the select) while ours emits `> 19` / `> 9`.
int CheckRankOfEnemyAttackedNPC::doQuery() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        const s32 rank = npc->_1038;
        s32 level = 1;
        if (rank >= 20)
            level = 2;
        return rank < 10 ? 0 : level;
    }
    return 0;
}

void CheckRankOfEnemyAttackedNPC::loadParams(const evfl::QueryArg& arg) {}

void CheckRankOfEnemyAttackedNPC::loadParams() {}

}  // namespace uking::query

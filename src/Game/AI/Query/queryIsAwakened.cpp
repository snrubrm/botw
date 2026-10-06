#include "Game/AI/Query/queryIsAwakened.h"
#include <evfl/Query.h>
#include "Game/Actor/actNPC.h"

namespace uking::query {

IsAwakened::IsAwakened(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsAwakened::~IsAwakened() = default;

int IsAwakened::doQuery() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        if (npc->_fe8 & 0x100000)
            return 1;
    }
    return 0;
}

void IsAwakened::loadParams(const evfl::QueryArg& arg) {}

void IsAwakened::loadParams() {}

}  // namespace uking::query

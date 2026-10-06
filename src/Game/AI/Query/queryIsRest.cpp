#include "Game/AI/Query/queryIsRest.h"
#include <evfl/Query.h>
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::query {

IsRest::IsRest(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsRest::~IsRest() = default;

int IsRest::doQuery() {
    sead::FixedSafeString<64> state;
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        if (npc->_a70.isEmpty()) {
            if (mActor->getRootAi()->isChildIdx0())
                mActor->getRootAi()->getNames(&state);
            else
                mActor->getRootAi()->getCurrentName(&state, nullptr);
        } else {
            state = npc->_a70;
        }
    }
    return state.findIndex("/Root/Rest") != -1 || state.findIndex("/Root/ReturnRestPos/Turn") != -1;
}

void IsRest::loadParams(const evfl::QueryArg& arg) {}

void IsRest::loadParams() {}

}  // namespace uking::query

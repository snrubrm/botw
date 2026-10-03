#include "Game/AI/Action/actionSetWanderPathIndex.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actNPC.h"

namespace uking::action {

SetWanderPathIndex::SetWanderPathIndex(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetWanderPathIndex::~SetWanderPathIndex() = default;

bool SetWanderPathIndex::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetWanderPathIndex::loadParams_() {}

bool SetWanderPathIndex::oneShot_() {
    auto* npc = sead::DynamicCast<uking::act::NPC>(mActor);
    if (!npc)
        return false;
    npc->_fe8 |= 0x400000;
    if (auto* rail = npc->_848._8.rail)
        npc->_848.sub_7100EEBAE0(rail, 0.0f);
    return true;
}

}  // namespace uking::action

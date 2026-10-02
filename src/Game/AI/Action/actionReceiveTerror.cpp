#include "Game/AI/Action/actionReceiveTerror.h"
#include "Game/Actor/actNPC.h"

namespace uking::action {

ReceiveTerror::ReceiveTerror(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReceiveTerror::~ReceiveTerror() = default;

bool ReceiveTerror::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ReceiveTerror::oneShot_() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        npc->_fe8 |= 0x800000;
    return true;
}

void ReceiveTerror::loadParams_() {}

}  // namespace uking::action

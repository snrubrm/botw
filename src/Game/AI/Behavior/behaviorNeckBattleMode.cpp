#include "Game/AI/Behavior/behaviorNeckBattleMode.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

NeckBattleMode::NeckBattleMode(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NeckBattleMode::~NeckBattleMode() = default;

bool NeckBattleMode::m6(sead::Heap* heap) {
    return true;
}

void NeckBattleMode::m7() {}

void NeckBattleMode::loadParams() {

}

void NeckBattleMode::m8() {
    if (auto* control = mActor->sub_71011D8A10())
        control->_8c |= 0x10;
}

void NeckBattleMode::m9() {
    if (auto* control = mActor->sub_71011D8A10())
        control->_8c &= ~0x10;
}

}  // namespace uking::behavior

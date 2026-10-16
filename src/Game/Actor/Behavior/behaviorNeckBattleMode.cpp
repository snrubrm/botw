#include "Game/Actor/Behavior/behaviorNeckBattleMode.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

NeckBattleMode::NeckBattleMode(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NeckBattleMode::~NeckBattleMode() = default;

bool NeckBattleMode::init_(sead::Heap* heap) {
    return true;
}

void NeckBattleMode::calc() {}

void NeckBattleMode::loadParams() {

}

void NeckBattleMode::enter() {
    if (auto* control = mActor->sub_71011D8A10())
        control->_8c |= 0x10;
}

void NeckBattleMode::leave() {
    if (auto* control = mActor->sub_71011D8A10())
        control->_8c &= ~0x10;
}

}  // namespace uking::behavior

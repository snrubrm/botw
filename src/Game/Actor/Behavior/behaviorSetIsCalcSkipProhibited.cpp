#include "Game/Actor/Behavior/behaviorSetIsCalcSkipProhibited.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetIsCalcSkipProhibited::SetIsCalcSkipProhibited(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetIsCalcSkipProhibited::~SetIsCalcSkipProhibited() = default;

bool SetIsCalcSkipProhibited::init_(sead::Heap* heap) {
    return true;
}

void SetIsCalcSkipProhibited::calc() {}

void SetIsCalcSkipProhibited::loadParams() {

}

void SetIsCalcSkipProhibited::enter() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.set(0x40);
}

void SetIsCalcSkipProhibited::leave() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.reset(0x40);
}

}  // namespace uking::behavior

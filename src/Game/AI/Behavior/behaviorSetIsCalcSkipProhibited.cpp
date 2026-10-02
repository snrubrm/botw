#include "Game/AI/Behavior/behaviorSetIsCalcSkipProhibited.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetIsCalcSkipProhibited::SetIsCalcSkipProhibited(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetIsCalcSkipProhibited::~SetIsCalcSkipProhibited() = default;

bool SetIsCalcSkipProhibited::m6(sead::Heap* heap) {
    return true;
}

void SetIsCalcSkipProhibited::m7() {}

void SetIsCalcSkipProhibited::loadParams() {

}

void SetIsCalcSkipProhibited::m8() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.set(0x40);
}

void SetIsCalcSkipProhibited::m9() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.reset(0x40);
}

}  // namespace uking::behavior

#include "Game/AI/Behavior/behaviorDisableSkipCalcCloth.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

DisableSkipCalcCloth::DisableSkipCalcCloth(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableSkipCalcCloth::~DisableSkipCalcCloth() = default;

bool DisableSkipCalcCloth::m6(sead::Heap* heap) {
    return true;
}

void DisableSkipCalcCloth::m7() {}

void DisableSkipCalcCloth::loadParams() {

}

void DisableSkipCalcCloth::m8() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.set(0x2);
}

void DisableSkipCalcCloth::m9() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.reset(0x2);
}

}  // namespace uking::behavior

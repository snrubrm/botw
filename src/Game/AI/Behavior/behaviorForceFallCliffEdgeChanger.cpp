#include "Game/AI/Behavior/behaviorForceFallCliffEdgeChanger.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

ForceFallCliffEdgeChanger::ForceFallCliffEdgeChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ForceFallCliffEdgeChanger::~ForceFallCliffEdgeChanger() = default;

bool ForceFallCliffEdgeChanger::m6(sead::Heap* heap) {
    return true;
}

void ForceFallCliffEdgeChanger::m7() {}

void ForceFallCliffEdgeChanger::loadParams() {
    getStaticParam(&mState_s, "State");
}

// NON_MATCHING: the original computes the set (orr) before the reset (and) value
void ForceFallCliffEdgeChanger::m8() {
    auto* cc = mActor->getCharacterController();
    if (!cc)
        return;
    _30 = cc->mFlags.isOn(0x4000);
    cc->mFlags.change(0x4000, *mState_s);
}

// NON_MATCHING: the original computes the set (orr) before the reset (and) value
void ForceFallCliffEdgeChanger::m9() {
    auto* cc = mActor->getCharacterController();
    if (!cc)
        return;
    cc->mFlags.change(0x4000, _30);
}

}  // namespace uking::behavior

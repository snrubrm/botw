#include "Game/Actor/Behavior/behaviorForceFallCliffEdgeChanger.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

ForceFallCliffEdgeChanger::ForceFallCliffEdgeChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ForceFallCliffEdgeChanger::~ForceFallCliffEdgeChanger() = default;

bool ForceFallCliffEdgeChanger::init_(sead::Heap* heap) {
    return true;
}

void ForceFallCliffEdgeChanger::calc() {}

void ForceFallCliffEdgeChanger::loadParams() {
    getStaticParam(&mState_s, "State");
}

void ForceFallCliffEdgeChanger::enter() {
    auto* cc = mActor->getCharacterController();
    if (!cc)
        return;
    _30 = cc->mFlags.isOn(0x4000);
    cc->mFlags.setDirect(*mState_s ? (cc->mFlags.getDirect() | 0x4000) :
                                    (cc->mFlags.getDirect() & ~0x4000));
}

void ForceFallCliffEdgeChanger::leave() {
    auto* cc = mActor->getCharacterController();
    if (!cc)
        return;
    cc->mFlags.setDirect(_30 ? (cc->mFlags.getDirect() | 0x4000) :
                             (cc->mFlags.getDirect() & ~0x4000));
}

}  // namespace uking::behavior

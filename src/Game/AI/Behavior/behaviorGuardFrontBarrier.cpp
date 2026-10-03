#include "Game/AI/Behavior/behaviorGuardFrontBarrier.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

GuardFrontBarrier::GuardFrontBarrier(const InitArg& arg) : GuardFrontBarrierBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
GuardFrontBarrier::~GuardFrontBarrier() {
    ;
}

bool GuardFrontBarrier::m6(sead::Heap* heap) {
    return GuardFrontBarrierBase::m6(heap);
}

void GuardFrontBarrier::m8() {
    GuardFrontBarrierBase::m8();
    sead::Matrix34f mtx;
    m15(&mtx);
    _58.mELink.setMatrix(mtx);
    auto* body =
        mActor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), mTgtName_s.cstr());
    if (body) {
        if (body->isAddedToWorld())
            body->changePositionAndRotation(mtx);
        else
            body->setTransform(mtx);
    }
}

void GuardFrontBarrier::m7() {
    GuardFrontBarrierBase::m7();
    sead::Matrix34f mtx;
    m15(&mtx);
    _58.mELink.setMatrix(mtx);
    auto* body =
        mActor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), mTgtName_s.cstr());
    if (body) {
        if (body->isAddedToWorld())
            body->changePositionAndRotation(mtx);
        else
            body->setTransform(mtx);
    }
}

void GuardFrontBarrier::m9() {
    GuardFrontBarrierBase::m9();
    auto* body =
        mActor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), mTgtName_s.cstr());
    if (body && body->isAddedToWorld()) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
}

void GuardFrontBarrier::loadParams() {
    GuardFrontBarrierBase::loadParams();
    getStaticParam(&mTgtName_s, "TgtName");
}

void GuardFrontBarrier::m15(sead::Matrix34f* out) {
    *out = mActor->getMtx();
}

}  // namespace uking::behavior

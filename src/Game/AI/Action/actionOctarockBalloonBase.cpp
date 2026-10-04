#include "Game/AI/Action/actionOctarockBalloonBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

// out of line in the original (leave_ calls it): kept out of line here too
[[gnu::noinline]] void OctarockBalloonBase::sub_71000B8928(f32 value) {
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(value);
}

OctarockBalloonBase::OctarockBalloonBase(const InitArg& arg) : BalloonBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
OctarockBalloonBase::~OctarockBalloonBase() {
    ;
}

bool OctarockBalloonBase::init_(sead::Heap* heap) {
    return BalloonBase::init_(heap);
}

void OctarockBalloonBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BalloonBase::enter_(params);
}

void OctarockBalloonBase::leave_() {
    BalloonBase::leave_();
    sub_71000B8928(1.0f);
    auto* actor = mActor;
    if (actor->getConnectedCalcChild())
        actor->resetConnectedCalcChild(false);
}

void OctarockBalloonBase::loadParams_() {
    BalloonBase::loadParams_();
    getStaticParam(&mConnectReleaseTimer_s, "ConnectReleaseTimer");
    getStaticParam(&mClampWindForceScale_s, "ClampWindForceScale");
    getStaticParam(&mReduceVel_s, "ReduceVel");
    getDynamicParam(&mConnectRigidName_d, "ConnectRigidName");
    getDynamicParam(&mConnectRigidOffset_d, "ConnectRigidOffset");
    getDynamicParam(&mRopeActorHandle_d, "RopeActorHandle");
}

void OctarockBalloonBase::calc_() {
    BalloonBase::calc_();
}

// NON_MATCHING: the original loads and negates *mClampWindForceScale_s before calling BalloonBase::m33
// (`const f32 low = -*p; const f32 value = BalloonBase::m33(); return clamp(value, low, *p);` matches)
f32 OctarockBalloonBase::m33() {
    return sead::Mathf::clamp(BalloonBase::m33(), -*mClampWindForceScale_s, *mClampWindForceScale_s);
}

f32 OctarockBalloonBase::m34(f32 current, f32 target, f32 step) {
    if (current < target) {
        const f32 value = current + step * 0.2f;
        if (value >= target || value < current)
            return target;
        return value;
    }
    if (current > target) {
        const f32 value = current + step * -0.1f;
        if (value <= target || value > current)
            return target;
        return value;
    }
    return current;
}

}  // namespace uking::action

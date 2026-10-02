#include "Game/AI/Action/actionOctarockBalloonBase.h"

namespace uking::action {

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

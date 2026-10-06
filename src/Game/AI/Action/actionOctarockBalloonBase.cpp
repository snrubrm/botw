#include "Game/AI/Action/actionOctarockBalloonBase.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
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
    const sead::Vector3f wind = sub_71000B7980();
    if (sead::Mathf::sqrt(wind.x * wind.x + wind.z * wind.z) < 1.0f) {
        auto* actor = mActor;
        sead::Vector3f gravity = getGravity(actor);
        gravity = gravity * (1.0f / 900.0f);
        sub_7100738488(actor, *mReduceVel_s, gravity);
    }
    if (!(_128.value <= sead::Mathf::epsilon())) {
        _128.update();
        if (_128.value <= sead::Mathf::epsilon()) {
            auto* actor = mActor;
            if (actor->getConnectedCalcChild())
                actor->resetConnectedCalcChild(false);
        }
    }
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

void OctarockBalloonBase::m35(ksys::phys::RigidBody* a, ksys::phys::RigidBody* b,
                              ksys::act::RopeBase* rope) {
    if (!rope)
        return;
    rope->sub_7100ECE140();
    rope->sub_7100ECE0CC(ksys::phys::ContactLayer::EntityRope);
    rope->sub_7100ECE0CC(ksys::phys::ContactLayer::EntitySmallObject);
    rope->sub_7100ECE0CC(ksys::phys::ContactLayer::EntityGroundObject);
    rope->sub_7100ECE0CC(ksys::phys::ContactLayer::EntityObject);
    rope->sub_7100ECE0CC(a->getContactLayer());
    rope->sub_7100ECE0CC(b->getContactLayer());
}

}  // namespace uking::action

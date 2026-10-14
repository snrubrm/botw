#include "Game/Actor/Action/actionBalloonRopeBase.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

// out of line in the original (leave_ calls it): kept out of line here too
[[gnu::noinline]] void BalloonRopeBase::sub_71000B8928(f32 value) {
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(value);
}

BalloonRopeBase::BalloonRopeBase(const InitArg& arg) : BalloonBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
BalloonRopeBase::~BalloonRopeBase() {
    ;
}

bool BalloonRopeBase::init_(sead::Heap* heap) {
    return BalloonBase::init_(heap);
}

void BalloonRopeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BalloonBase::enter_(params);
    auto* actor = mActor;
    sub_71000B8928(0.1f);
    sub_71000B782C(actor->getMtx().m[1][3]);

    auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild());
    ksys::phys::RigidBody* body = nullptr;
    if (child)
        body = child->findPhysicsBodyByName("Body", mConnectRigidName_d.cstr());

    auto* handle = *mRopeActorHandle_d;
    if (handle) {
        if (auto* rope = sead::DynamicCast<ksys::act::RopeBase>(handle->getProc())) {
            sub_71000B8470(child, body, mConnectRigidOffset_d, rope);
            rope->_98a = false;
            handle->releaseAndWakeProc();
            const f32 t = *mConnectReleaseTimer_s;
            _128.value = t;
            _128.previous_value = t;
            _128.rate = -1.0f;
            return;
        }
    }
    _128.value = 0;
    _128.previous_value = 0;
    _128.rate = 0;
    actor->resetConnectedCalcChild(false);
}

void BalloonRopeBase::leave_() {
    BalloonBase::leave_();
    sub_71000B8928(1.0f);
    auto* actor = mActor;
    if (actor->getConnectedCalcChild())
        actor->resetConnectedCalcChild(false);
}

void BalloonRopeBase::loadParams_() {
    BalloonBase::loadParams_();
    getStaticParam(&mConnectReleaseTimer_s, "ConnectReleaseTimer");
    getStaticParam(&mClampWindForceScale_s, "ClampWindForceScale");
    getStaticParam(&mReduceVel_s, "ReduceVel");
    getDynamicParam(&mConnectRigidName_d, "ConnectRigidName");
    getDynamicParam(&mConnectRigidOffset_d, "ConnectRigidOffset");
    getDynamicParam(&mRopeActorHandle_d, "RopeActorHandle");
}

void BalloonRopeBase::calc_() {
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

f32 BalloonRopeBase::m33() {
    const f32 lower = -*mClampWindForceScale_s;
    f32 value = BalloonBase::m33();
    if (value < lower)
        value = lower;
    else if (value > *mClampWindForceScale_s)
        value = *mClampWindForceScale_s;
    return value;
}

f32 BalloonRopeBase::m34(f32 current, f32 target, f32 step) {
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

void BalloonRopeBase::m35(ksys::phys::RigidBody* a, ksys::phys::RigidBody* b,
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

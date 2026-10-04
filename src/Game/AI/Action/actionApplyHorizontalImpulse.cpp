#include "Game/AI/Action/actionApplyHorizontalImpulse.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ApplyHorizontalImpulse::ApplyHorizontalImpulse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyHorizontalImpulse::~ApplyHorizontalImpulse() = default;

bool ApplyHorizontalImpulse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ApplyHorizontalImpulse::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        sead::Vector3f center;
        body->getCenterOfMassInWorld(&center);
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        body->setLinearVelocity(*mDynVel_d * 30.0f);
        body->setAngularVelocity(*mDynAngVel_d * 30.0f);
    }
    _4c = false;
    mFlags.set(Flag::Changeable);
}

void ApplyHorizontalImpulse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ApplyHorizontalImpulse::loadParams_() {
    getDynamicParam(&mDynVel_d, "DynVel");
    getDynamicParam(&mDynAngVel_d, "DynAngVel");
    getMapUnitParam(&mIsBreakable_m, "IsBreakable");
    getMapUnitParam(&mEnableToEmitSpEffect_m, "EnableToEmitSpEffect");
}

void ApplyHorizontalImpulse::calc_() {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        if (body->getMotionType() != ksys::phys::MotionType::Fixed) {
            if (actor->sub_71011C7990())
                _4c = true;
            else if (_4c)
                body->changeMotionType(ksys::phys::MotionType::Fixed);
        }
    }
}

}  // namespace uking::action

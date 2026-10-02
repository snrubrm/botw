#include "Game/AI/Action/actionSwitchStepSliderConstraintOnce.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

SwitchStepSliderConstraintOnce::SwitchStepSliderConstraintOnce(const InitArg& arg)
    : SwitchStepSliderConstraint(arg) {}

bool SwitchStepSliderConstraintOnce::init_(sead::Heap* heap) {
    return SwitchStepSliderConstraint::init_(heap);
}

void SwitchStepSliderConstraintOnce::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchStepSliderConstraint::enter_(params);
    _e1 = mActor->checkLinkBasicSig();
}

void SwitchStepSliderConstraintOnce::leave_() {
    SwitchStepSliderConstraint::leave_();
}

void SwitchStepSliderConstraintOnce::loadParams_() {
    SwitchStepSliderConstraint::loadParams_();
}

void SwitchStepSliderConstraintOnce::calc_() {
    _e1 = mActor->checkLinkBasicSig();
    SwitchStepSliderConstraint::calc_();
}

void SwitchStepSliderConstraintOnce::m32(f32 value) {
    if (!(value <= 0.001f) || _e0 || _e1)
        return;
    auto* actor = mActor;
    actor->emitBasicSigOn();
    _e0 = 1;
    ksys::eft::searchAndEmitSLink(actor, "on", false);
    sub_710028EE24();
}

void SwitchStepSliderConstraintOnce::m33(ksys::phys::RigidBody* body, const sead::Vector3f* impulse,
                                         const sead::Vector3f* pos) {
    if (_e1)
        body->changePosition(*pos, ksys::phys::KeepAngularVelocity(true));
    else
        body->applyLinearImpulse(*impulse);
}

void SwitchStepSliderConstraintOnce::m34() {
    if (mActor->checkLinkBasicSig())
        sub_710028EE24();
    else
        sub_710028EE98();
}

}  // namespace uking::action

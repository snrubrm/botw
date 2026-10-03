#include "Game/AI/Action/actionSideStep.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SideStep::SideStep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SideStep::~SideStep() = default;

void SideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

// NON_MATCHING: operand order of the normalisation multiplies (`s10 * s0` in the original)
void SideStep::leave_() {
    const f32 speed = _cc;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f dir;
        dir.set(controller->get70());
        dir.normalize();
        dir.multScalar(-speed);
        controller->sub_7100F5EE1C(dir);
    }
    const f32 gravity_scale = _d0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62B70(gravity_scale);
    sub_71005DA114(mActor, &_80);
}

void SideStep::loadParams_() {
    getStaticParam(&mParams.mRotSpeedRatio_s, "RotSpeedRatio");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mParams.mGravity_s, "Gravity");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void SideStep::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SideStep::isChangeable() const {
    return false;
}

}  // namespace uking::action

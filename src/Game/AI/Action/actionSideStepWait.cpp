#include "Game/AI/Action/actionSideStepWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SideStepWait::SideStepWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SideStepWait::~SideStepWait() = default;

void SideStepWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

// NON_MATCHING: operand order of the normalisation multiplies (`s10 * s0` in the original)
void SideStepWait::leave_() {
    const f32 speed = _b4;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f dir;
        dir.set(controller->get70());
        dir.normalize();
        dir.multScalar(-speed);
        controller->sub_7100F5EE1C(dir);
    }
    const f32 gravity_scale = _b8;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62B70(gravity_scale);
}

void SideStepWait::loadParams_() {
    getStaticParam(&mParams.mFirstStepDist_s, "FirstStepDist");
    getStaticParam(&mParams.mSecondStepDist_s, "SecondStepDist");
    getStaticParam(&mParams.mThirdStepDist_s, "ThirdStepDist");
    getStaticParam(&mParams.mFourthStepDist_s, "FourthStepDist");
    getStaticParam(&mParams.mGravity_s, "Gravity");
    getStaticParam(&mParams.mFirstStepHeight_s, "FirstStepHeight");
    getStaticParam(&mParams.mSecondStepHeight_s, "SecondStepHeight");
    getStaticParam(&mParams.mThirdStepHeight_s, "ThirdStepHeight");
    getStaticParam(&mParams.mFourthStepHeight_s, "FourthStepHeight");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mStopRotSpeedRatio_s, "StopRotSpeedRatio");
}

void SideStepWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

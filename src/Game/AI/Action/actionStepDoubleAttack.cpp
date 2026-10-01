#include "Game/AI/Action/actionStepDoubleAttack.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
StepDoubleAttack::StepDoubleAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StepDoubleAttack::~StepDoubleAttack() = default;

void StepDoubleAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StepDoubleAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void StepDoubleAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void StepDoubleAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

bool StepDoubleAttack::isChangeable() const {
    return false;
}

int StepDoubleAttack::m32() {
    return 1;
}

}  // namespace uking::action

#include "Game/AI/Action/actionLinearFlyAttackBase.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
LinearFlyAttackBase::LinearFlyAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LinearFlyAttackBase::~LinearFlyAttackBase() = default;

bool LinearFlyAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LinearFlyAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LinearFlyAttackBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void LinearFlyAttackBase::loadParams_() {
    getStaticParam(&mParams.mTime_s, "Time");
    getStaticParam(&mParams.mAttackSpeed_s, "AttackSpeed");
    getStaticParam(&mParams.mAttackSlowDownRatio_s, "AttackSlowDownRatio");
    getStaticParam(&mParams.mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mParams.mThroughDist_s, "ThroughDist");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void LinearFlyAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

int LinearFlyAttackBase::m32() {
    return 8192;
}

f32 LinearFlyAttackBase::m34() {
    return 30.0f;
}

void LinearFlyAttackBase::m33(sead::Vector3f* dir) {
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, mActor);
    sead::Vector3f up = -gravity;
    if (up.normalize() < sead::Mathf::epsilon())
        up.set(sead::Vector3f::ey);
    dir->set(up);
}

}  // namespace uking::action

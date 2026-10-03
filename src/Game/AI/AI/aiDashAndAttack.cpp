#include "Game/AI/AI/aiDashAndAttack.h"

namespace uking::ai {

DashAndAttack::DashAndAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DashAndAttack::~DashAndAttack() = default;

bool DashAndAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DashAndAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DashAndAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DashAndAttack::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mAttackFrame_s, "AttackFrame");
    getStaticParam(&mParams.mOffsetLR_s, "OffsetLR");
    getStaticParam(&mParams.mAttackRange_s, "AttackRange");
    getStaticParam(&mParams.mTiredAngle_s, "TiredAngle");
    getStaticParam(&mParams.mTargetSpeedClampMax_s, "TargetSpeedClampMax");
    getStaticParam(&mParams.mIsAbleSkipNear_s, "IsAbleSkipNear");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getDynamicParam(&mParams.mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai

#include "Game/AI/Action/actionAttackJumpToTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
AttackJumpToTarget::AttackJumpToTarget(const InitArg& arg) : JumpToTarget(arg) {}

AttackJumpToTarget::~AttackJumpToTarget() = default;

void AttackJumpToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpToTarget::enter_(params);
    if (*mIsIgnoreSmallHit_s)
        setDamageCallbackTiming(mActor, 4, &_108);
    sead::Vector3f dir = *mTargetPos_d;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    dir -= pos;
    dir.y = 0.0f;
    const f32 dist = dir.normalize();
    _130 = -dir * sead::Mathf::clampMax(*mPosOffsetDist_s, dist);
}

void AttackJumpToTarget::leave_() {
    JumpToTarget::leave_();
}

void AttackJumpToTarget::loadParams_() {
    JumpToTarget::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getStaticParam(&mPosOffsetDist_s, "PosOffsetDist");
    getStaticParam(&mIsCheckNoChangeAS_s, "IsCheckNoChangeAS");
}

void AttackJumpToTarget::calc_() {
    JumpToTarget::calc_();
}

const sead::Vector3f& AttackJumpToTarget::m44() {
    return _130;
}

}  // namespace uking::action

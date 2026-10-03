#include "Game/AI/Action/actionAttackJumpToTarget.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
AttackJumpToTarget::AttackJumpToTarget(const InitArg& arg) : JumpToTarget(arg) {}

AttackJumpToTarget::~AttackJumpToTarget() = default;

void AttackJumpToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpToTarget::enter_(params);
    if (*mParams.mIsIgnoreSmallHit_s)
        setDamageCallbackTiming(mActor, 4, &_108);
    sead::Vector3f dir = *mTargetPos_d;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    dir -= pos;
    dir.y = 0.0f;
    const f32 dist = dir.normalize();
    _130 = -dir * sead::Mathf::clampMax(*mParams.mPosOffsetDist_s, dist);
}

void AttackJumpToTarget::leave_() {
    JumpToTarget::leave_();
    sub_71005DA114(mActor, &_108);
    sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
}

void AttackJumpToTarget::loadParams_() {
    JumpToTarget::loadParams_();
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mParams.mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mParams.mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mParams.mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getStaticParam(&mParams.mPosOffsetDist_s, "PosOffsetDist");
    getStaticParam(&mParams.mIsCheckNoChangeAS_s, "IsCheckNoChangeAS");
}

void AttackJumpToTarget::calc_() {
    JumpToTarget::calc_();
}

const sead::Vector3f& AttackJumpToTarget::m44() {
    return _130;
}

}  // namespace uking::action

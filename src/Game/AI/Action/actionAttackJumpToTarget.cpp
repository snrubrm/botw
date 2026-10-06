#include "Game/AI/Action/actionAttackJumpToTarget.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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
    sead::Vector3f dir = *JumpTo::mParams.mTargetPos_d;
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

// NON_MATCHING: stack layout only (the original keeps the Unk_71002edaec temporary above the ASList query, as in
// HorseRideAttack::calc_ / AnmDrivenMoveAttack::calc_)
void AttackJumpToTarget::calc_() {
    JumpToTarget::calc_();
    if (*mParams.mIsCheckNoChangeAS_s) {
        if (sub_71005DD798(mActor, 0x16, nullptr, 0, 0))
            mFlags.reset(Flag::Changeable);
        else
            mFlags.set(Flag::Changeable);
    }
    const f32 base = sub_71007322E8(mActor, *mParams.mWeaponIdx_s);
    sub_71005DAB2C(mActor, base + *mParams.mJustAvoidSideDist_s, base + *mParams.mJustAvoidBackDist_s,
                   *mParams.mJustAvoidAngle_s, 0);
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0)) {
        sub_71005D7ADC(mActor, *mParams.mWeaponIdx_s, 2, &query.name, nullptr, 1, 1, 0, 1, 1.0f,
                       1.0f);
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
    }
}

const sead::Vector3f& AttackJumpToTarget::m44() {
    return _130;
}

}  // namespace uking::action

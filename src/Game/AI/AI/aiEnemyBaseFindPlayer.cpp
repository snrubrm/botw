#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"

namespace uking::ai {

EnemyBaseFindPlayer::EnemyBaseFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyBaseFindPlayer::~EnemyBaseFindPlayer() = default;



bool EnemyBaseFindPlayer::init_(sead::Heap* heap) {
    const s32 lost_timer = *mLostTimer_s;
    const s32 lost_timer2 = lost_timer * 1.1f;
    _118 = sead::Mathi::min(lost_timer, lost_timer2);
    _11c = sead::Mathi::max(lost_timer, lost_timer2);
    _110 = _118 == _11c ? _118 : sead::GlobalRandom::instance()->getS32Range(_118, _11c);
    sub_71005E2C58(mActor);
    return true;
}

void EnemyBaseFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyBaseFindPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyBaseFindPlayer::loadParams_() {
    getStaticParam(&mSurpriseAttackPer_s, "SurpriseAttackPer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mSurpriseAttackTime_s, "SurpriseAttackTime");
    getStaticParam(&mSurpriseAttackTimeRand_s, "SurpriseAttackTimeRand");
    getStaticParam(&mRerouteTimeMin_s, "RerouteTimeMin");
    getStaticParam(&mRerouteTimeMax_s, "RerouteTimeMax");
    getStaticParam(&mRestreintTime_s, "RestreintTime");
    getStaticParam(&mRetTiredFromTime_s, "RetTiredFromTime");
    getStaticParam(&mSurpriseAttackRange_s, "SurpriseAttackRange");
    getStaticParam(&mAttackRange_s, "AttackRange");
    getStaticParam(&mAttackVMin_s, "AttackVMin");
    getStaticParam(&mAttackVMax_s, "AttackVMax");
    getStaticParam(&mSwiftAttackVMin_s, "SwiftAttackVMin");
    getStaticParam(&mSwiftAttackVMax_s, "SwiftAttackVMax");
    getStaticParam(&mRestreintTiredDist_s, "RestreintTiredDist");
    getStaticParam(&mForceFirstAttackDist_s, "ForceFirstAttackDist");
    getStaticParam(&mRetForceFirstAttackDist_s, "RetForceFirstAttackDist");
    getStaticParam(&mPathTooLongDist_s, "PathTooLongDist");
    getStaticParam(&mNoSearchFromTiredDist_s, "NoSearchFromTiredDist");
    getAITreeVariable(&mIsTryingReturnRestreint_a, "IsTryingReturnRestreint");
}

f32 EnemyBaseFindPlayer::m34() {
    return *mAttackRange_s + sub_71007320F0(mActor, *mWeaponIdx_s);
}

bool EnemyBaseFindPlayer::m36(bool b) {
    return m39(sub_71005D9330(mActor), b);
}

bool EnemyBaseFindPlayer::m37() {
    return m39(sub_71005D98D8(mActor), false);
}

bool EnemyBaseFindPlayer::m42(s32 x) {
    return x != 2 && x != 3 && x != 5;
}

void EnemyBaseFindPlayer::m47() {
    sub_71005DB248(mActor);
}

bool EnemyBaseFindPlayer::m43() {
    if (sub_710072E1B4(mActor, true))
        return false;
    return sub_71005D9744(mActor) != 4;
}

}  // namespace uking::ai

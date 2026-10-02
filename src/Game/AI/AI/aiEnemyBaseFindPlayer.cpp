#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"

namespace uking::ai {

EnemyBaseFindPlayer::EnemyBaseFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyBaseFindPlayer::init_(sead::Heap* heap) {
    sub_710037E9A4();
    sub_71005E2C58(mActor);
    return true;
}

void EnemyBaseFindPlayer::sub_710037E9A4() {
    const s32 lost_timer = *mLostTimer_s;
    const s32 lost_timer2 = lost_timer * 1.1f;
    _118 = sead::Mathi::min(lost_timer, lost_timer2);
    _11c = sead::Mathi::max(lost_timer, lost_timer2);
    _108.mValue = _118 == _11c ? _118 : sead::GlobalRandom::instance()->getS32Range(_118, _11c);
}

void EnemyBaseFindPlayer::sub_710037ECD0() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("ナビメッシュ無し", &params);
}

void EnemyBaseFindPlayer::sub_710037EDA4() {
    _108.mValue = _118 == _11c ? _118 : sead::GlobalRandom::instance()->getS32Range(_118, _11c);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D98D8(mActor), "TargetPos", -1);
    changeChild("気づき", &params);
}

bool EnemyBaseFindPlayer::sub_710037EEAC() {
    auto* actor = mActor;
    if (*mLostTimer_s < 0)
        return !sub_71005D8F28(actor);
    const s32 state = sub_71005D9744(actor);
    if (!sub_71005D8F28(actor))
        return true;
    return m42(state);
}

// NON_MATCHING: the original loads the GlobalRandom GOT entry after the _e8 store and the
// SurpriseAttackTime value before the instance
void EnemyBaseFindPlayer::sub_71003803E8() {
    _e8.set(2);
    _e0 = sead::GlobalRandom::instance()->getS32Range(
        *mSurpriseAttackTime_s, *mSurpriseAttackTime_s + *mSurpriseAttackTimeRand_s);
    if (sub_710037EEAC())
        sub_710037E9A4();
    sub_710037EDA4();
}

void EnemyBaseFindPlayer::sub_710038054C() {
    if (_f0)
        _f0->sub_7100710F04();
    _f8 = _fc == _100 ? _fc : sead::GlobalRandom::instance()->getS32Range(_fc, _100);
    _120 = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    _e8.reset(4);
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    params.addVec3(home_pos, "CentralPos", -1);
    changeChild("威嚇帰還", &params);
}

bool EnemyBaseFindPlayer::sub_7100380B50() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    const f32 dy = sub_71005D9330(enemy).y - enemy->getMtx()(1, 3);
    if (dy < *mSwiftAttackVMin_s || dy > *mSwiftAttackVMax_s)
        return false;

    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&enemy->_c48._8, &player);
    if (player.x_13())
        return false;
    const auto* level = mActor->getParam()->getRes().mGParamList->getEnemyLevel();
    return level && level->mIsSwiftAttack.ref();
}

void EnemyBaseFindPlayer::sub_7100380E90() {
    _e8.reset(4);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("不意討ち", &params);
}

bool EnemyBaseFindPlayer::sub_71003804F4() {
    const s32 lost_timer = *mLostTimer_s;
    if (lost_timer >= 0) {
        if (_108.mValue <= 0)
            return true;
        if (lost_timer > 0)
            return false;
    }
    return !sub_71005D8F28(mActor);
}

void EnemyBaseFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyBaseFindPlayer::leave_() {
    sub_71005DB3EC(mActor);
    _e8.reset(4);
    if (_f0 && _f0->_0)
        _f0->_0->inlineReset();
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

// NON_MATCHING: the original evaluates the params before copying the translation (element-wise) and
// the forward axis, as if through an inline helper taking the matrix (lane1 log, session 18)
bool EnemyBaseFindPlayer::m35() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const auto& target = sub_71005D9330(actor);
    const f32 max_dist = m34();
    if (!sub_710072DEF0(target, max_dist, *mAttackVMin_s, *mAttackVMax_s,
                        actor->getMtx().getTranslation(), actor->getMtx().getBase(2),
                        sead::Mathf::pi(), sead::Mathf::maxNumber(), 0.8f)) {
        return false;
    }
    return m36(true);
}

bool EnemyBaseFindPlayer::m38() {
    return !sub_710072E368(mActor);
}

bool EnemyBaseFindPlayer::m39(const sead::Vector3f& pos, bool b) {
    f32 dist;
    if (auto* nav = mActor->m45())
        dist = nav->_2a8 * nav->_2ac;
    else
        dist = 0;
    if (b)
        dist += sub_71007320F0(mActor, *mWeaponIdx_s);
    sead::Vector3f out;
    return sub_710072F944(mActor, pos, &out, dist, 3.0f);
}

void EnemyBaseFindPlayer::m40() {
    _108.mValue = _118 == _11c ? _118 : sead::GlobalRandom::instance()->getS32Range(_118, _11c);
    _e8.reset(4);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘", &params);
}

void EnemyBaseFindPlayer::m41() {
    _e8.reset(4);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    params.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
    changeChild("速攻", &params);
}

void EnemyBaseFindPlayer::m44() {
    auto* child = getCurrentChild();
    if (isCurrentChild("戦闘") || isCurrentChild("不意討ち") || isCurrentChild("速攻")) {
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
        return;
    }

    const bool noticing = isCurrentChild("気づき");
    if (m43()) {
        _108.sub_7100D3BC4C(-1.0f);
    } else {
        _108.mValue =
            _118 == _11c ? _118 : sead::GlobalRandom::instance()->getS32Range(_118, _11c);
    }
    child->setDynamicParam(noticing ? sub_71005D98D8(mActor) : sub_71005D9330(mActor),
                           "TargetPos");
}

}  // namespace uking::ai

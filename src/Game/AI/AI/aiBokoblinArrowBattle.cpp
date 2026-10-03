#include "Game/AI/AI/aiBokoblinArrowBattle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

// NON_MATCHING: the callback's zero stores are scheduled before the param memset
BokoblinArrowBattle::BokoblinArrowBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BokoblinArrowBattle::~BokoblinArrowBattle() = default;

void BokoblinArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsUpdateNoticeState_s) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    }
    _114 = 0;
    const s32 min_num = *mBlindlyAttackMinNum_s;
    const s32 max_num = *mBlindlyAttackMaxNum_s;
    _118 = sead::GlobalRandom::instance()->getS32Range(min_num, max_num + 1);
    _11c = *mTargetPos_d;
    _11c.y += sub_71005D960C(mActor).y - sub_71005D9330(mActor).y;
    sub_7100331088();
}

// NON_MATCHING: load/scheduling order only; the original loads *mHoldIntervalRand_s and the selected
// hold interval before calling getF32 (the float math, timers and pack match)
void BokoblinArrowBattle::sub_7100331088() {
    sub_71005DA114(mActor, &_c8);
    const s32* hold_interval = _114 == _118 - 1 ? mHoldIntervalLast_s : mHoldInterval_s;
    _f0.reset(s32(*hold_interval +
                  *mHoldIntervalRand_s * sead::GlobalRandom::instance()->getF32() * -0.5f) +
              *mHoldIntervalRand_s);
    _108.reset(*mLeaveWaitTime_s);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

void BokoblinArrowBattle::sub_71003318A8() {
    sub_71005DA114(mActor, &_c8);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_11c, "TargetPos", -1);
    changeChild("弓構え", &pack);
}

void BokoblinArrowBattle::sub_7100331980() {
    setDamageCallbackTiming(mActor, 4, &_c8);
    _fc.reset(*mLeaveTime_s);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("離脱", &pack);
}

bool BokoblinArrowBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void BokoblinArrowBattle::leave_() {
    sub_71005DA114(mActor, &_c8);
}

void BokoblinArrowBattle::loadParams_() {
    getStaticParam(&mHoldInterval_s, "HoldInterval");
    getStaticParam(&mHoldIntervalLast_s, "HoldIntervalLast");
    getStaticParam(&mHoldIntervalRand_s, "HoldIntervalRand");
    getStaticParam(&mLeaveStartDist_s, "LeaveStartDist");
    getStaticParam(&mLeaveEndDist_s, "LeaveEndDist");
    getStaticParam(&mLeaveWaitTime_s, "LeaveWaitTime");
    getStaticParam(&mLeaveTime_s, "LeaveTime");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mOutDistVMin_s, "OutDistVMin");
    getStaticParam(&mOutDistVMax_s, "OutDistVMax");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLeaveTime_s, "LeaveTime");
    getStaticParam(&mBlindlyAttackMinNum_s, "BlindlyAttackMinNum");
    getStaticParam(&mBlindlyAttackMaxNum_s, "BlindlyAttackMaxNum");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mShootDistRatio_s, "ShootDistRatio");
    getStaticParam(&mIsEndAfterAttack_s, "IsEndAfterAttack");
    getStaticParam(&mIsUpdateNoticeState_s, "IsUpdateNoticeState");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiBokoblinArrowBattle.h"
#include "KingSystem/ActorSystem/actActor.h"
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

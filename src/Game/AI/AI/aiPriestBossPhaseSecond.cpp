#include "Game/AI/AI/aiPriestBossPhaseSecond.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

PriestBossPhaseSecond::PriestBossPhaseSecond(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseSecond::~PriestBossPhaseSecond() {
    mRecords.freeBuffer();
}

bool PriestBossPhaseSecond::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseSecond::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
}

void PriestBossPhaseSecond::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseSecond::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mModeChangeLife_s, "ModeChangeLife");
    getStaticParam(&mSimAtkMax_s, "SimAtkMax");
    getStaticParam(&mBowEquipMax_s, "BowEquipMax");
    getStaticParam(&mSyncAtkMax_s, "SyncAtkMax");
    getStaticParam(&mModeChangeBlockTime_s, "ModeChangeBlockTime");
    getStaticParam(&mRespawnSpan_s, "RespawnSpan");
    getStaticParam(&mRespawnBaseSpace_s, "RespawnBaseSpace");
    getStaticParam(&mRespawnBaseMoveTime_s, "RespawnBaseMoveTime");
    getStaticParam(&mRespawnBaseInterval_s, "RespawnBaseInterval");
    getStaticParam(&mCircleFormRange_s, "CircleFormRange");
    getStaticParam(&mCircleFormRushWait_s, "CircleFormRushWait");
    getStaticParam(&mCircleFormRushInterval_s, "CircleFormRushInterval");
    getStaticParam(&mCircleFormShootWait_s, "CircleFormShootWait");
    getStaticParam(&mCircleFormShootInterval_s, "CircleFormShootInterval");
    getStaticParam(&mLineFormDistFromPlayer_s, "LineFormDistFromPlayer");
    getStaticParam(&mLineFormSpace_s, "LineFormSpace");
    getStaticParam(&mLineFormRushWait_s, "LineFormRushWait");
    getStaticParam(&mLineFormRushInterval_s, "LineFormRushInterval");
    getStaticParam(&mLineFormFallWait_s, "LineFormFallWait");
    getStaticParam(&mLineFormFallInterval_s, "LineFormFallInterval");
    getMapUnitParam(&mPriestBossStartPhase_m, "PriestBossStartPhase");
}

void PriestBossPhaseSecond::m39() {
    ksys::act::ActorConstDataAccess accessor;
    for (int i = 2; i <= 10; ++i) {
        if (sub_7100525B18(i, &accessor))
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void PriestBossPhaseSecond::m40() {
    if (sub_7100525A88()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_0)))
        return;
    PriestBossPhase::m40();
}

bool PriestBossPhaseSecond::m37(f32* ratio) {
    ksys::act::BaseProcLink link;
    if (!sub_7100525BC0(2, &link))
        return false;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
    if (!actor || !actor->isAwakeMaybe())
        return false;

    auto* life = actor->getLife();
    const f32 life_value = life ? f32(*life) : 1.0f;
    *ratio = life_value / f32(actor->getMaxLife());
    return true;
}

}  // namespace uking::ai

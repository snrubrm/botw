#include "Game/AI/AI/aiPriestBossActorNormalMode.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossActorNormalMode::PriestBossActorNormalMode(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossActorNormalMode::~PriestBossActorNormalMode() = default;

bool PriestBossActorNormalMode::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossActorNormalMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

// NON_MATCHING: the compiler combines the phase range checks into one comparison.
void PriestBossActorNormalMode::leave_() {
    if (sub_7100505BE4()) {
        sub_7100505BE4();
        if (_e4 >= 3 && _e4 <= 10)
            dmg::DamageInfoMgr::instance()->get4f8().sub_7100671F78(mActor);
    }
    if (auto* unit = sub_7100505BE4())
        unit->sub_7100719D5C(mActor);
    PriestBossMode::leave_();
}

void PriestBossActorNormalMode::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mApproachWarpRate_s, "ApproachWarpRate");
    getStaticParam(&mApproachStartDistance_s, "ApproachStartDistance");
    getStaticParam(&mLeaveStartDistance_s, "LeaveStartDistance");
    getStaticParam(&mLeaveStartTime_s, "LeaveStartTime");
    getStaticParam(&mWaitMinTime_s, "WaitMinTime");
    getStaticParam(&mWaitMaxTime_s, "WaitMaxTime");
    getStaticParam(&mSecondHalfLifePercent_s, "SecondHalfLifePercent");
    getStaticParam(&mFramesRestrictEarthRelease_s, "FramesRestrictEarthRelease");
    getStaticParam(&mWarpPosDistFromPlayer_s, "WarpPosDistFromPlayer");
    getStaticParam(&mStageMarginRateForEarthRelease_s, "StageMarginRateForEarthRelease");
    getStaticParam(&mIsManagedBtlMgr_s, "IsManagedBtlMgr");
    getDynamicParam(&mFromSyncMode_d, "FromSyncMode");
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

f32 PriestBossActorNormalMode::m35() {
    return 0.0f;
}

f32 PriestBossActorNormalMode::m36() {
    if (!sub_7100505BE4())
        return 1.0f;
    return sub_7100505BE4()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_11)) ? 1.0f :
                                                                                         0.01f;
}

f32 PriestBossActorNormalMode::m37() {
    return 0.0f;
}

f32 PriestBossActorNormalMode::m38() {
    return 0.0f;
}

f32 PriestBossActorNormalMode::m42() {
    f32 weight = 0.0f;
    if (sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0 &&
        sub_7100505BE4()->_40 <= *mSecondHalfLifePercent_s) {
        weight = 0.5f;
    }
    return weight;
}

f32 PriestBossActorNormalMode::m44() {
    f32 weight = 0.0f;
    if (!(sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0) && _12c != 9 &&
        sub_7100505BE4() && _e4 == 2) {
        if (sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_3))
            weight = 1.0f;
    }
    return weight;
}

f32 PriestBossActorNormalMode::m45() {
    return 0.0f;
}

f32 PriestBossActorNormalMode::m46() {
    return 0.0f;
}

}  // namespace uking::ai

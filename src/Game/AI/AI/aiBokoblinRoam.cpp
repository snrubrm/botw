#include "Game/AI/AI/aiBokoblinRoam.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

BokoblinRoam::BokoblinRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BokoblinRoam::~BokoblinRoam() = default;

void BokoblinRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    _dc = false;
    _dd = false;
    const s32 free_min = *mFreeIntervalMin_s;
    const s32 free_max = *mFreeIntervalMax_s;
    const s32 free_time = sead::GlobalRandom::instance()->getS32Range(free_min, free_max);
    _d0 = ksys::Timer(free_time, free_time);
    const s32 move_min = *mMoveIntervalMin_s;
    const s32 move_max = *mMoveIntervalMax_s;
    const s32 move_time = sead::GlobalRandom::instance()->getS32Range(move_min, move_max);
    _c4 = ksys::Timer(move_time, move_time);
    _bc = _c0 = *mSpAttackServiceTime_s;
    _b8 = _bc;
    changeChild("待機");
}

void BokoblinRoam::loadParams_() {
    getStaticParam(&mFreeIntervalMin_s, "FreeIntervalMin");
    getStaticParam(&mFreeIntervalMax_s, "FreeIntervalMax");
    getStaticParam(&mFreePer_s, "FreePer");
    getStaticParam(&mMoveIntervalMin_s, "MoveIntervalMin");
    getStaticParam(&mMoveIntervalMax_s, "MoveIntervalMax");
    getStaticParam(&mNoMoveTime_s, "NoMoveTime");
    getStaticParam(&mSpAttackServiceTime_s, "SpAttackServiceTime");
    getStaticParam(&mNoSpAttackMoveTime_s, "NoSpAttackMoveTime");
    getStaticParam(&mTerritory_s, "Territory");
    getStaticParam(&mTargetDistMin_s, "TargetDistMin");
    getStaticParam(&mTargetDistMax_s, "TargetDistMax");
    getStaticParam(&mSpAttackServiceDist_s, "SpAttackServiceDist");
    getStaticParam(&mSpAttackServiceAngle_s, "SpAttackServiceAngle");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getStaticParam(&mTurnCheckDist_s, "TurnCheckDist");
    getStaticParam(&mTurnCheckHeight_s, "TurnCheckHeight");
}

bool BokoblinRoam::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() || isCurrentChild("索敵") || isCurrentChild("暇つぶし");
}

}  // namespace uking::ai

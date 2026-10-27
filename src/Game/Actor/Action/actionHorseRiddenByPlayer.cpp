#include "Game/Actor/Action/actionHorseRiddenByPlayer.h"
#include "Game/Actor/actRideable.h"

namespace uking::action {

HorseRiddenByPlayer::HorseRiddenByPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseRiddenByPlayer::~HorseRiddenByPlayer() {
    ksys::gdt::Manager::instance()->removeReinitCallback(_338);
}

void HorseRiddenByPlayer::sub_71001A388C() {
    _324 = ksys::gdt::Manager::instance()->getS32Handle("Horse_CurrentChargeNum");
    _328 = ksys::gdt::Manager::instance()->getS32Handle("Horse_CurrentExtraChargeNum");
    _32c = ksys::gdt::Manager::instance()->getBoolHandle("Horse_IsOnChargePenalty");
    _330 = ksys::gdt::Manager::instance()->getBoolHandle("MiniGame_HorseRace_CreateObstacle");
}

void HorseRiddenByPlayer::onGdtReinit(ksys::gdt::Manager::ReinitEvent* event) {
    sub_71001A388C();
}

bool HorseRiddenByPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseRiddenByPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseRiddenByPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseRiddenByPlayer::loadParams_() {
    getStaticParam(&mMaxAcceleration_s, "MaxAcceleration");
    getStaticParam(&mSlideToCurveRatio_s, "SlideToCurveRatio");
    getStaticParam(&mTiredFramesAfterGearTop_s, "TiredFramesAfterGearTop");
    getStaticParam(&mCheckFramesSootheAtFirstRun_s, "CheckFramesSootheAtFirstRun");
    getStaticParam(&mCheckFramesSootheAfterRun_s, "CheckFramesSootheAfterRun");
    getStaticParam(&mCheckFramesSootheAfterGearTop_s, "CheckFramesSootheAfterGearTop");
    getStaticParam(&mCheckFramesSootheAfterJump_s, "CheckFramesSootheAfterJump");
    getStaticParam(&mCheckFramesSootheAfterResist_s, "CheckFramesSootheAfterResist");
    getStaticParam(&mCheckFramesAccInputAfterResist_s, "CheckFramesAccInputAfterResist");
    getStaticParam(&mMinFramesForRunSoothe_s, "MinFramesForRunSoothe");
    getStaticParam(&mFamiliarityEffectDelayFrames_s, "FamiliarityEffectDelayFrames");
    getStaticParam(&mChargeRecoveryFrames_s, "ChargeRecoveryFrames");
    getStaticParam(&mChargeRecoveryFramesSecondly_s, "ChargeRecoveryFramesSecondly");
    getStaticParam(&mChargePenaltyFrames_s, "ChargePenaltyFrames");
    getStaticParam(&mSwitchFramesByTemperature_s, "SwitchFramesByTemperature");
    getStaticParam(&mForwardBentFramesAtGearTop_s, "ForwardBentFramesAtGearTop");
    getStaticParam(&mFallHeightForPlayingAS_s, "FallHeightForPlayingAS");
    getStaticParam(&mFallHeightForPlayingASInRunning_s, "FallHeightForPlayingASInRunning");
    getStaticParam(&mFallRayCastLength_s, "FallRayCastLength");
    getStaticParam(&mFamiliarityThresholdOfRailTrace_s, "FamiliarityThresholdOfRailTrace");
    getStaticParam(&mFamiliarityThresholdOfResist_s, "FamiliarityThresholdOfResist");
    getStaticParam(&mFamiliarityThresholdOfWaitAngry_s, "FamiliarityThresholdOfWaitAngry");
    getStaticParam(&mResistGearDownProbability_s, "ResistGearDownProbability");
    getStaticParam(&mResistChangeSteeringProbability_s, "ResistChangeSteeringProbability");
    getStaticParam(&mResistChangeSteeringMinFrames_s, "ResistChangeSteeringMinFrames");
    getStaticParam(&mResistChangeSteeringMaxFrames_s, "ResistChangeSteeringMaxFrames");
    getStaticParam(&mResistChangeSteeringInputRange_s, "ResistChangeSteeringInputRange");
    getStaticParam(&mFramesPlayAngryWhileResist_s, "FramesPlayAngryWhileResist");
    getStaticParam(&mDelayFramesResistGearDown_s, "DelayFramesResistGearDown");
    getStaticParam(&mDelayFramesResistChangeSteering_s, "DelayFramesResistChangeSteering");
    getStaticParam(&mStressDecBySoothe_s, "StressDecBySoothe");
    getStaticParam(&mStressIncByImpossibleAcc_s, "StressIncByImpossibleAcc");
    getStaticParam(&mStressIncByEnemy_s, "StressIncByEnemy");
    getStaticParam(&mStressIncByDamage_s, "StressIncByDamage");
}

void HorseRiddenByPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

// 0x71001abf60: plays the AS names `name` expands to on the rideable's S1 controller.
void sub_71001ABF60(uking::act::Rideable* rideable, const char* name, ...) {
    std::va_list args;
    va_start(args, name);
    rideable->_18.sub_7100E787B0(name, args);
    va_end(args);
}


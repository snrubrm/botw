#include "Game/AI/Action/actionPlayerRideHorse.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <limits>

namespace uking::action {

PlayerRideHorse::PlayerRideHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerRideHorse::~PlayerRideHorse() = default;

bool PlayerRideHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerRideHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: the original stores _d4/_dc as unaligned 64-bit pairs and _d0/_e4 separately; ours merges
    // _d0 with _d4 (and _d8 with _dc) into 32-bit pairs
    mFlags.reset(Flag::Changeable);
    _b0 = 0.0f;
    _b4 = -std::numeric_limits<f32>::infinity();
    _d4.set(15.0f, 0.0f);
    _dc.set(std::numeric_limits<f32>::infinity(), 0.0f);
    _b8 = 0.0f;
    _c4 = 0.0f;
    _104 = 0;
    _d0 = 0.0f;
    _e4 = 0.0f;
    _e8 = mActor->getVelocity();
    _f4 = mActor->getVelocity();
    _100 = mActor->getVelocity().y;
}

void PlayerRideHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerRideHorse::loadParams_() {
    getStaticParam(&mAccelerateInputDelayGear0_s, "AccelerateInputDelayGear0");
    getStaticParam(&mAccelerateInputDelayGear1_s, "AccelerateInputDelayGear1");
    getStaticParam(&mAccelerateInputDelayGear2_s, "AccelerateInputDelayGear2");
    getStaticParam(&mAccelerateInputDelayGear3_s, "AccelerateInputDelayGear3");
    getStaticParam(&mAccelerateInputDelayGearTop_s, "AccelerateInputDelayGearTop");
    getStaticParam(&mAccInputIgnoreFramesGear0_s, "AccInputIgnoreFramesGear0");
    getStaticParam(&mAccInputIgnoreFramesGear1_s, "AccInputIgnoreFramesGear1");
    getStaticParam(&mAccInputIgnoreFramesGear2_s, "AccInputIgnoreFramesGear2");
    getStaticParam(&mAccInputIgnoreFramesGear3_s, "AccInputIgnoreFramesGear3");
    getStaticParam(&mAccInputIgnoreFramesGearTop_s, "AccInputIgnoreFramesGearTop");
    getStaticParam(&mDecelerateInputThreshold_s, "DecelerateInputThreshold");
    getStaticParam(&mStopInputFrames_s, "StopInputFrames");
    getStaticParam(&mAccelerateInputThreshold_s, "AccelerateInputThreshold");
    getStaticParam(&mMoveBackInputThreshold_s, "MoveBackInputThreshold");
    getStaticParam(&mStickXClampAtGear0_s, "StickXClampAtGear0");
    getStaticParam(&mTurnStickXInputThreshold_s, "TurnStickXInputThreshold");
    getStaticParam(&mConstraintBreakThreshold_s, "ConstraintBreakThreshold");
    getDynamicParam(&mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
}

void PlayerRideHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

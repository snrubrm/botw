#include "Game/AI/Action/actionBirdEscape.h"

namespace uking::action {

BirdEscape::BirdEscape(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BirdEscape::~BirdEscape() = default;

bool BirdEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BirdEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BirdEscape::leave_() {
    _88.resetMotionType(_88.sub_710072ACF8(mActor));
}

void BirdEscape::loadParams_() {
    getStaticParam(&mParams.mMoveSpeedMax_s, "MoveSpeedMax");
    getStaticParam(&mParams.mMoveSpeedMin_s, "MoveSpeedMin");
    getStaticParam(&mParams.mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mParams.mInterpolateFrameForMaxSpeed_s, "InterpolateFrameForMaxSpeed");
    getStaticParam(&mParams.mTargetEscapeWidthMax_s, "TargetEscapeWidthMax");
    getStaticParam(&mParams.mTargetEscapeWidthMin_s, "TargetEscapeWidthMin");
    getStaticParam(&mParams.mTargetHeightMax_s, "TargetHeightMax");
    getStaticParam(&mParams.mTargetHeightMin_s, "TargetHeightMin");
    getStaticParam(&mParams.mTargetTurnAngle_s, "TargetTurnAngle");
    getStaticParam(&mParams.mContinueEscapeDistanceXZ_s, "ContinueEscapeDistanceXZ");
    getStaticParam(&mParams.mAdditionalWidth_s, "AdditionalWidth");
    getStaticParam(&mParams.mTargetUpperAngle_s, "TargetUpperAngle");
    getStaticParam(&mParams.mStartReduceHeightRate_s, "StartReduceHeightRate");
}

void BirdEscape::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

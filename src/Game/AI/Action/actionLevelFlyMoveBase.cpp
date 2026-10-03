#include "Game/AI/Action/actionLevelFlyMoveBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LevelFlyMoveBase::LevelFlyMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LevelFlyMoveBase::~LevelFlyMoveBase() {
    _108.release();
}

bool LevelFlyMoveBase::init_(sead::Heap* heap) {
    return _108.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateChecker_a));
}

void LevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LevelFlyMoveBase::leave_() {
    auto* actor = mActor;
    _110.resetRigidBodyMotion(actor);
    _110.resetMotionType(_110.sub_710072ACF8(actor));
    _118.sub_71006F3DF4();
}

void LevelFlyMoveBase::loadParams_() {
    getStaticParam(&mXZSpeed_s, "XZSpeed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mHorizontalFinRadius_s, "HorizontalFinRadius");
    getStaticParam(&mVerticalFinLength_s, "VerticalFinLength");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mDownSpeed_s, "DownSpeed");
    getStaticParam(&mCheckStopSpeed_s, "CheckStopSpeed");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mIsOverRise_s, "IsOverRise");
    getStaticParam(&mIsSlowDownNearGoal_s, "IsSlowDownNearGoal");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    _118.sub_71006F3DF8();
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void LevelFlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

void LevelFlyMoveBase::m34(sead::Vector3f* pos) {
    if (!pos)
        return;
    pos->set(*mTargetPos_d);
    pos->y += *mTargetHeightOffset_s;
}

}  // namespace uking::action

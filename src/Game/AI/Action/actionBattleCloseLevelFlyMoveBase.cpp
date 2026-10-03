#include "Game/AI/Action/actionBattleCloseLevelFlyMoveBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: ours keeps `this + 0x70` (first VFRValue) in a callee-saved register across the memset call; the
// original recomputes it after the call (regalloc only).
BattleCloseLevelFlyMoveBase::BattleCloseLevelFlyMoveBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

BattleCloseLevelFlyMoveBase::~BattleCloseLevelFlyMoveBase() = default;

bool BattleCloseLevelFlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleCloseLevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BattleCloseLevelFlyMoveBase::leave_() {
    auto* actor = mActor;
    _c4.resetRigidBodyMotion(actor);
    _c4.resetMotionType(_c4.sub_710072ACF8(actor));
    _d0.sub_71006F3DF4();
}

void BattleCloseLevelFlyMoveBase::loadParams_() {
    getStaticParam(&mXZSpeed_s, "XZSpeed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mHorizontalFinRadius_s, "HorizontalFinRadius");
    getStaticParam(&mVerticalFinLength_s, "VerticalFinLength");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mDownSpeed_s, "DownSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    _d0.sub_71006F3DF8();
}

void BattleCloseLevelFlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

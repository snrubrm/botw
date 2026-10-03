#include "Game/AI/Action/actionBattleLevelFlyMoveBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: scheduling only (the vtable address add and the VFRVec3f address are ordered differently)
BattleLevelFlyMoveBase::BattleLevelFlyMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BattleLevelFlyMoveBase::~BattleLevelFlyMoveBase() = default;

bool BattleLevelFlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleLevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BattleLevelFlyMoveBase::leave_() {
    auto* actor = mActor;
    _cc.resetRigidBodyMotion(actor);
    _cc.resetMotionType(_cc.sub_710072ACF8(actor));
}

void BattleLevelFlyMoveBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mCheckStopSpeed_s, "CheckStopSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void BattleLevelFlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

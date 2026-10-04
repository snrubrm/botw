#include "Game/AI/Action/actionRemainsWaterExplodeBulletMove.h"

namespace uking::action {

RemainsWaterExplodeBulletMove::RemainsWaterExplodeBulletMove(const InitArg& arg)
    : RemainsWaterBulletAction(arg) {}

RemainsWaterExplodeBulletMove::~RemainsWaterExplodeBulletMove() = default;

bool RemainsWaterExplodeBulletMove::init_(sead::Heap* heap) {
    return RemainsWaterBulletAction::init_(heap);
}

void RemainsWaterExplodeBulletMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _c0 = false;
    _e8 = 1.0f;
    _ec = 1.0f;
    RemainsWaterBulletAction::enter_(params);
}

void RemainsWaterExplodeBulletMove::leave_() {
    RemainsWaterBulletAction::leave_();
    if (_c8.sub_7101241B6C())
        _c8.fadeXLink();
}

void RemainsWaterExplodeBulletMove::loadParams_() {
    RemainsWaterBulletAction::loadParams_();
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mCloseRadius_s, "CloseRadius");
    getStaticParam(&mChaseAngleMulRate_s, "ChaseAngleMulRate");
    getStaticParam(&mFarRadius_s, "FarRadius");
    getStaticParam(&mChaseRotSpdRate_s, "ChaseRotSpdRate");
    getStaticParam(&mChaseSpdRate_s, "ChaseSpdRate");
    getMapUnitParam(&mRemainsWaterBulletAngle_m, "RemainsWaterBulletAngle");
    getMapUnitParam(&mRemainsWaterBulletOffset_m, "RemainsWaterBulletOffset");
}

void RemainsWaterExplodeBulletMove::calc_() {
    sub_7100233FD0();
    RemainsWaterBulletAction::calc_();
}

}  // namespace uking::action

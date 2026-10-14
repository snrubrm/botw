#include "Game/Actor/Action/actionRemainsWaterExplodeBulletMove.h"
#include "KingSystem/System/VFR.h"

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

void RemainsWaterExplodeBulletMove::sub_7100233FD0() {
    switch (sub_7100230688()) {
    case 0:
        ksys::VFR::lerp(&_e8, 2.8f, 0.2f, 0.005f, 0.001f);
        ksys::VFR::lerp(&_ec, 1.2f, 0.2f, 0.005f, 0.001f);
        break;
    case 1:
        ksys::VFR::lerp(&_e8, 1.0f, 0.2f, 0.1f, 0.01f);
        ksys::VFR::lerp(&_ec, 1.0f, 0.2f, 0.1f, 0.01f);
        break;
    case 2:
        ksys::VFR::lerp(&_e8, 2.0f, 0.2f, 0.005f, 0.001f);
        ksys::VFR::lerp(&_ec, 0.6f, 0.2f, 0.005f, 0.001f);
        break;
    case 3:
        ksys::VFR::lerp(&_e8, 2.0f, 0.2f, 0.005f, 0.001f);
        ksys::VFR::lerp(&_ec, 0.8f, 0.2f, 0.005f, 0.001f);
        break;
    }
}

}  // namespace uking::action

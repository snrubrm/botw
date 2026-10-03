#include "Game/AI/Action/actionDragonFixPlacement.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actDragon.h"

namespace uking::action {

DragonFixPlacement::DragonFixPlacement(const InitArg& arg) : NullASPlay(arg) {}

DragonFixPlacement::~DragonFixPlacement() = default;

bool DragonFixPlacement::init_(sead::Heap* heap) {
    return NullASPlay::init_(heap);
}

void DragonFixPlacement::enter_(ksys::act::ai::InlineParamPack* params) {
    NullASPlay::enter_(params);
}

void DragonFixPlacement::leave_() {
    NullASPlay::leave_();
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        dragon->_14c8._8b8 = 1.0f;
        dragon->_14c8._930 &= ~0x40;
    }
}

void DragonFixPlacement::loadParams_() {
    NullASPlay::loadParams_();
    getStaticParam(&mBlendStartFrame_s, "BlendStartFrame");
    getStaticParam(&mHeadFixedModeTime_s, "HeadFixedModeTime");
    getStaticParam(&mRailAdjustModeTime_s, "RailAdjustModeTime");
    getStaticParam(&mCameraVibStartFrame_s, "CameraVibStartFrame");
    getStaticParam(&mCameraVibLoop_s, "CameraVibLoop");
    getStaticParam(&mBlendStartRate_s, "BlendStartRate");
    getStaticParam(&mBlendTime_s, "BlendTime");
    getStaticParam(&mCameraVibPower_s, "CameraVibPower");
    getStaticParam(&mCameraVibRange_s, "CameraVibRange");
    getStaticParam(&mRotate_s, "Rotate");
    getStaticParam(&mPosition_s, "Position");
}

void DragonFixPlacement::calc_() {
    NullASPlay::calc_();
}

}  // namespace uking::action

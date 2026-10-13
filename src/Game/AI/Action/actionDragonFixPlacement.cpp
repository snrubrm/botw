#include "Game/AI/Action/actionDragonFixPlacement.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actDragon.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

DragonFixPlacement::DragonFixPlacement(const InitArg& arg) : NullASPlay(arg) {}

DragonFixPlacement::~DragonFixPlacement() = default;

bool DragonFixPlacement::init_(sead::Heap* heap) {
    return NullASPlay::init_(heap);
}

// NON_MATCHING: the mode-flag selection uses the inverse select condition.
void DragonFixPlacement::enter_(ksys::act::ai::InlineParamPack* params) {
    NullASPlay::enter_(params);
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        _a0 = 0.0f;
        _a4 = 0.0f;
        _a8[0] = 0;
        _a9 = false;
        dragon->_14c8._8b8 = 0.0f;
        if (dragon->_1f70.isOnBit(28))
            dragon->_14c8._930 &= ~0x40;
        else
            dragon->_14c8._930 |= 0x40;
        sead::Matrix34f matrix = sead::Matrix34f::ident;
        ksys::util::sub_71011EFCA8(&matrix, *mRotate_s);
        matrix.setTranslation(*mPosition_s);
        dragon->x(matrix);
        dragon->mMtx.setTranslation(*mPosition_s);
        dragon->setMtx(dragon->mMtx, true, true);
        dragon->nullsub_4648();
    }
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

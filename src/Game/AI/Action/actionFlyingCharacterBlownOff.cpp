#include "Game/AI/Action/actionFlyingCharacterBlownOff.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

FlyingCharacterBlownOff::FlyingCharacterBlownOff(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

FlyingCharacterBlownOff::~FlyingCharacterBlownOff() = default;

bool FlyingCharacterBlownOff::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
}

void FlyingCharacterBlownOff::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterBlownOff::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterBlownOff::calc_() {
    FlyingCharacterReaction::calc_();
}

void FlyingCharacterBlownOff::m32() {
    if (!mFallAS_s.isEmpty())
        playAS(mFallAS_s.cstr(), true, 0, 0, -1.0f);
}

void FlyingCharacterBlownOff::m34(ksys::phys::CharacterController* controller) {
    FlyingCharacterReaction::m34(controller);
}

void FlyingCharacterBlownOff::m35() {
    if (!mOnGroundAS_s.isEmpty())
        playAS(mOnGroundAS_s.cstr(), true, 0, 0, -1.0f);
}

void FlyingCharacterBlownOff::m37(ksys::phys::CharacterController* controller) {
    if (isFinishedAS(0, 0)) {
        setFinished();
        return;
    }

    if (*mIsControlRotation_s) {
        sub_710073FA94(&_40, mActor);
        sead::Vector3f normal;
        if (controller->sub_7100F5F234(&normal)) {
            sub_7100740118(&_40, normal, 0.8f, 2 * sead::Mathf::pi(), 0.0f);
        } else {
            const sead::Vector3f dir = -controller->get7c();
            sub_7100740118(&_40, dir, 0.8f, 2 * sead::Mathf::pi(), 0.0f);
        }
        sub_7100740E04(_40, controller);
    } else {
        sub_7100738660(controller, *mRotReduceRatioOnGround_s);
    }
    sub_7100737C0C(controller, *mPosReduceRatioOnGround_s, -sead::Vector3f::ey);
}

}  // namespace uking::action

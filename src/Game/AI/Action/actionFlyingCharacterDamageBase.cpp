#include "Game/AI/Action/actionFlyingCharacterDamageBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

FlyingCharacterDamageBase::FlyingCharacterDamageBase(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

FlyingCharacterDamageBase::~FlyingCharacterDamageBase() = default;

bool FlyingCharacterDamageBase::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterDamageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
}

void FlyingCharacterDamageBase::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterDamageBase::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mLastSpeedRatio_s, "LastSpeedRatio");
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mIsCheckFallASFinished_s, "IsCheckFallASFinished");
    getStaticParam(&mIsIgnoreSameAS4Fall_s, "IsIgnoreSameAS4Fall");
    getStaticParam(&mIsIgnoreSameAS4OnGround_s, "IsIgnoreSameAS4OnGround");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterDamageBase::calc_() {
    FlyingCharacterReaction::calc_();
}

void FlyingCharacterDamageBase::m33() {
    if (!mFallAS_s.isEmpty())
        playAS(mFallAS_s.cstr(), *mIsIgnoreSameAS4Fall_s, 0, 0, -1.0f);
}

void FlyingCharacterDamageBase::m34(ksys::phys::CharacterController* controller) {
    if (*mIsCheckFallASFinished_s && isFinishedAS(0, 0)) {
        setFinished();
        return;
    }
    FlyingCharacterReaction::m34(controller);
}

void FlyingCharacterDamageBase::m36() {
    if (!mOnGroundAS_s.isEmpty())
        playAS(mOnGroundAS_s.cstr(), *mIsIgnoreSameAS4OnGround_s, 0, 0, -1.0f);
}

void FlyingCharacterDamageBase::m37(ksys::phys::CharacterController* controller) {
    if (isFinishedAS(0, 0))
        setFinished();

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
    FlyingCharacterReaction::m37(controller);
}

}  // namespace uking::action

#include "Game/AI/Action/actionFlyingCharacterFreeFallDie.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

FlyingCharacterFreeFallDie::FlyingCharacterFreeFallDie(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

FlyingCharacterFreeFallDie::~FlyingCharacterFreeFallDie() = default;

bool FlyingCharacterFreeFallDie::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterFreeFallDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
    sub_710072BB28(mActor);
}

void FlyingCharacterFreeFallDie::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterFreeFallDie::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterFreeFallDie::calc_() {
    FlyingCharacterReaction::calc_();
}

void FlyingCharacterFreeFallDie::m32() {
    if (!mFallAS_s.isEmpty())
        playAS(mFallAS_s.cstr(), true, 0, 0, -1.0f);
}

void FlyingCharacterFreeFallDie::m34(ksys::phys::CharacterController* controller) {
    FlyingCharacterReaction::m34(controller);
}

void FlyingCharacterFreeFallDie::m35() {
    if (!mOnGroundAS_s.isEmpty())
        playAS(mOnGroundAS_s.cstr(), true, 0, 0, -1.0f);
}

void FlyingCharacterFreeFallDie::m37(ksys::phys::CharacterController* controller) {
    sub_7100737C0C(controller, *mPosReduceRatioOnGround_s, controller->get70());
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
    if (isFinishedAS(0, 0))
        setFinished();
    else
        FlyingCharacterReaction::m37(controller);
}

}  // namespace uking::action

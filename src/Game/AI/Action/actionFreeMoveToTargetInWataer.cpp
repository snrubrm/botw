#include "Game/AI/Action/actionFreeMoveToTargetInWataer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FreeMoveToTargetInWataer::FreeMoveToTargetInWataer(const InitArg& arg) : FreeMoveToTarget(arg) {}

FreeMoveToTargetInWataer::~FreeMoveToTargetInWataer() = default;

bool FreeMoveToTargetInWataer::init_(sead::Heap* heap) {
    return FreeMoveToTarget::init_(heap);
}

void FreeMoveToTargetInWataer::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMoveToTarget::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (*mForceUseFrontDir_s) {
        const sead::Vector3f front = mActor->getMtx().getBase(2);
        controller->sub_7100F5EDBC(front);
    }
    mActor->getMtx().getBase(_f8, 2);
}

void FreeMoveToTargetInWataer::leave_() {
    FreeMoveToTarget::leave_();
}

void FreeMoveToTargetInWataer::loadParams_() {
    FreeMoveToTarget::loadParams_();
    getStaticParam(&mAllowMoveWaterDepth_s, "AllowMoveWaterDepth");
    getStaticParam(&mForceTurnLimitSpeedStream_s, "ForceTurnLimitSpeedStream");
    getStaticParam(&mIsForceTurnAgainstStream_s, "IsForceTurnAgainstStream");
    getStaticParam(&mForceUseFrontDir_s, "ForceUseFrontDir");
}

void FreeMoveToTargetInWataer::calc_() {
    FreeMoveToTarget::calc_();
}

bool FreeMoveToTargetInWataer::m34() {
    const sead::Vector3f diff = _cc - mActor->getMtx().getTranslation();
    return diff.squaredLength() < *mFinishRadius_s * *mFinishRadius_s;
}

void FreeMoveToTargetInWataer::m38() {
    _cc = *mTargetPos_d;
}

}  // namespace uking::action

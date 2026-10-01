#include "Game/AI/Action/actionFreeMoveToTarget.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FreeMoveToTarget::FreeMoveToTarget(const InitArg& arg) : FreeMove(arg) {}

FreeMoveToTarget::~FreeMoveToTarget() = default;

bool FreeMoveToTarget::init_(sead::Heap* heap) {
    return FreeMove::init_(heap);
}

void FreeMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMove::enter_(params);
    const f32 interval = *mTargetUpdateInterval_s + 0.5f;
    _c0 = ksys::Timer(interval, interval);
}

void FreeMoveToTarget::leave_() {
    FreeMove::leave_();
}

void FreeMoveToTarget::loadParams_() {
    FreeMove::loadParams_();
    getStaticParam(&mTargetUpdateInterval_s, "TargetUpdateInterval");
    getStaticParam(&mFinishRadius_s, "FinishRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void FreeMoveToTarget::calc_() {
    _c0.update();
    if (_c0.hasEnded(0.0f)) {
        if (auto* controller = mActor->getCharacterController())
            m32(controller);
        const f32 interval = *mTargetUpdateInterval_s + 0.5f;
        _c0 = ksys::Timer(interval, interval);
    }
    FreeMove::calc_();
}

bool FreeMoveToTarget::m34() {
    const sead::Vector3f diff = mActor->getMtx().getTranslation() - *mTargetPos_d;
    return diff.squaredLength() <= *mFinishRadius_s * *mFinishRadius_s;
}

}  // namespace uking::action

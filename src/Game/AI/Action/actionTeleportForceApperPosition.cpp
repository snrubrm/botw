#include "Game/AI/Action/actionTeleportForceApperPosition.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

TeleportForceApperPosition::TeleportForceApperPosition(const InitArg& arg) : TeleportBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
TeleportForceApperPosition::~TeleportForceApperPosition() {
    ;
}

bool TeleportForceApperPosition::init_(sead::Heap* heap) {
    return TeleportBase::init_(heap);
}

void TeleportForceApperPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mHideEffectName_s.isEmpty() &&
        !mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20)) {
        xlinkSearchAndEmit(mActor, mHideEffectName_s.cstr(), 2, nullptr);
    }
    TeleportBase::enter_(params);
    const f32 time = *mArriveAtTargetTimeOut_s;
    _a8 = ksys::Timer(time, time);
    _b4 = false;
}

void TeleportForceApperPosition::leave_() {
    TeleportBase::leave_();
}

void TeleportForceApperPosition::loadParams_() {
    TeleportBase::loadParams_();
    getStaticParam(&mArriveAtTargetTimeOut_s, "ArriveAtTargetTimeOut");
    getStaticParam(&mArriveAtTargetRange_s, "ArriveAtTargetRange");
    getStaticParam(&mIsArriveAtTarget_s, "IsArriveAtTarget");
    getStaticParam(&mHideEffectName_s, "HideEffectName");
    getDynamicParam(&mAppearPosition_d, "AppearPosition");
}

void TeleportForceApperPosition::calc_() {
    TeleportBase::calc_();
}

bool TeleportForceApperPosition::isFinished() const {
    if (!ActionBase::isFinished())
        return false;
    return !_b4;
}

}  // namespace uking::action

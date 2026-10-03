#include "Game/AI/Action/actionTeleportForceApperPosition.h"
#include <math/seadMathCalcCommon.h>
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
    if (!_b4)
        TeleportBase::calc_();
    if (*mIsArriveAtTarget_s && mFlags.isOn(Flag::Finished)) {
        const sead::Vector3f& target = m33();
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const f32 dx = target.x - pos.x;
        const f32 dz = target.z - pos.z;
        const f32 distance = sead::Mathf::sqrt(dx * dx + dz * dz);
        _a8.update();
        if (_a8.value <= sead::Mathf::epsilon() || !(distance >= *mArriveAtTargetRange_s)) {
            m37();
            _b4 = false;
        } else {
            sub_7100294F68(m33(), m34());
            _b4 = true;
        }
    }
}

bool TeleportForceApperPosition::isFinished() const {
    if (!ActionBase::isFinished())
        return false;
    return !_b4;
}

}  // namespace uking::action

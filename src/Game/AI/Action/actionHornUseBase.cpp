#include "Game/AI/Action/actionHornUseBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HornUseBase::HornUseBase(const InitArg& arg) : TimeredASPlay(arg) {}

HornUseBase::~HornUseBase() = default;

bool HornUseBase::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap);
}

void HornUseBase::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
}

void HornUseBase::leave_() {
    TimeredASPlay::leave_();
}

void HornUseBase::loadParams_() {
    TimeredASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSignalOnTime_s, "SignalOnTime");
}

void HornUseBase::calc_() {
    TimeredASPlay::calc_();
}

bool HornUseBase::hasPreDeleteCb() {
    return true;
}

void HornUseBase::onPreDelete() {
    mActor->emitBasicSigOff();
}

}  // namespace uking::action

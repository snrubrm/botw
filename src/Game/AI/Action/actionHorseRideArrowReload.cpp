#include "Game/AI/Action/actionHorseRideArrowReload.h"

namespace uking::action {

HorseRideArrowReload::HorseRideArrowReload(const InitArg& arg) : HorseRide(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
HorseRideArrowReload::~HorseRideArrowReload() {
    ;
}

bool HorseRideArrowReload::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideArrowReload::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideArrowReload::leave_() {
    HorseRide::leave_();
}

void HorseRideArrowReload::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideArrowReload::calc_() {
    HorseRide::calc_();
}

}  // namespace uking::action

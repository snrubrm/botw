#include "Game/AI/Action/actionHorseRideViewWait.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

HorseRideViewWait::HorseRideViewWait(const InitArg& arg) : HorseRide(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
HorseRideViewWait::~HorseRideViewWait() {
    ;
}

bool HorseRideViewWait::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideViewWait::leave_() {
    HorseRide::leave_();
    sub_71005DB3EC(mActor);
}

void HorseRideViewWait::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideViewWait::calc_() {
    HorseRide::calc_();
    sub_71005DB1D8(mActor, *mTargetPos_d);
}

}  // namespace uking::action

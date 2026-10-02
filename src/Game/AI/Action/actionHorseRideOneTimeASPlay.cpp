#include "Game/AI/Action/actionHorseRideOneTimeASPlay.h"

namespace uking::action {

HorseRideOneTimeASPlay::HorseRideOneTimeASPlay(const InitArg& arg) : HorseRide(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
HorseRideOneTimeASPlay::~HorseRideOneTimeASPlay() {
    ;
}

bool HorseRideOneTimeASPlay::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideOneTimeASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideOneTimeASPlay::leave_() {
    HorseRide::leave_();
}

void HorseRideOneTimeASPlay::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mIgnoreSameAS_s, "IgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

void HorseRideOneTimeASPlay::calc_() {
    HorseRide::calc_();
}

}  // namespace uking::action

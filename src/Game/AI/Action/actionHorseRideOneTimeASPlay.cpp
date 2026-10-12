#include "Game/AI/Action/actionHorseRideOneTimeASPlay.h"

namespace uking::action {

HorseRideOneTimeASPlay::HorseRideOneTimeASPlay(const InitArg& arg) : HorseRideBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
HorseRideOneTimeASPlay::~HorseRideOneTimeASPlay() {
    ;
}

bool HorseRideOneTimeASPlay::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideOneTimeASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
    sub_71001AD8A0(mASName_s.cstr(), *mIgnoreSameAS_s);
}

void HorseRideOneTimeASPlay::leave_() {
    HorseRideBase::leave_();
}

void HorseRideOneTimeASPlay::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mIgnoreSameAS_s, "IgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

void HorseRideOneTimeASPlay::calc_() {
    HorseRideBase::calc_();
    if (sub_71001ADA78())
        setFinished();
}

}  // namespace uking::action

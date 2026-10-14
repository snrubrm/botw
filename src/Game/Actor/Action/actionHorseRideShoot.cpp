#include "Game/Actor/Action/actionHorseRideShoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideShoot::HorseRideShoot(const InitArg& arg) : HorseRideBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
HorseRideShoot::~HorseRideShoot() {
    ;
}

bool HorseRideShoot::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
    sub_71001AD8A0(mASName_s.cstr(), true);
    sub_71001ADAA0(*mTargetPos_d);
    _78 = false;
}

void HorseRideShoot::leave_() {
    sub_71005DB3B8(mActor);
    sub_71001ADAA8();
    HorseRideBase::leave_();
}

void HorseRideShoot::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mOffsetRangeMin_s, "OffsetRangeMin");
    getStaticParam(&mOffsetRangeMax_s, "OffsetRangeMax");
    getStaticParam(&mOffsetRateByDist_s, "OffsetRateByDist");
    getStaticParam(&mOffsetRangeMinOutOfScreen_s, "OffsetRangeMinOutOfScreen");
    getStaticParam(&mOffsetRangeMaxOutOfScreen_s, "OffsetRangeMaxOutOfScreen");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideShoot::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action

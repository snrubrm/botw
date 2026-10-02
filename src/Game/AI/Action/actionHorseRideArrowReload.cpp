#include "Game/AI/Action/actionHorseRideArrowReload.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

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
    sub_71001AD8A0(mASName_s.cstr(), true);
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
}

void HorseRideArrowReload::leave_() {
    HorseRide::leave_();
    sub_71001ADAA8();
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(5));
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
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
    sub_71001ADAA0(*mTargetPos_d);
    if (sub_71001ADA78())
        setFinished();
}

}  // namespace uking::action

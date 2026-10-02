#include "Game/AI/Action/actionWeaponHold.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WeaponHold::WeaponHold(const InitArg& arg) : OnetimeStopASPlay(arg) {}

WeaponHold::~WeaponHold() = default;

bool WeaponHold::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void WeaponHold::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void WeaponHold::leave_() {
    OnetimeStopASPlay::leave_();
}

void WeaponHold::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void WeaponHold::calc_() {
    OnetimeStopASPlay::calc_();
    if (mActor->getASList()->x(0x54, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        sub_71005DB6D0(mActor, *mWeaponIdx_s);
}

}  // namespace uking::action

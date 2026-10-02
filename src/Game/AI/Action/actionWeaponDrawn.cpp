#include "Game/AI/Action/actionWeaponDrawn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WeaponDrawn::WeaponDrawn(const InitArg& arg) : OnetimeStopASPlay(arg) {}

WeaponDrawn::~WeaponDrawn() = default;

bool WeaponDrawn::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void WeaponDrawn::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void WeaponDrawn::leave_() {
    OnetimeStopASPlay::leave_();
}

void WeaponDrawn::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void WeaponDrawn::calc_() {
    OnetimeStopASPlay::calc_();
    if (mActor->getASList()->x(0x53, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        sub_71005DB5C0(mActor, *mWeaponIdx_s);
}

}  // namespace uking::action

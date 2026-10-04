#include "Game/AI/Action/actionDropWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

DropWeapon::DropWeapon(const InitArg& arg) : OnetimeStopASPlay(arg) {}

DropWeapon::~DropWeapon() = default;

bool DropWeapon::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void DropWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void DropWeapon::leave_() {
    OnetimeStopASPlay::leave_();
}

void DropWeapon::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mAngleOffsetY_s, "AngleOffsetY");
    getStaticParam(&mChemReset_s, "ChemReset");
}

void DropWeapon::calc_() {
    OnetimeStopASPlay::calc_();
    if (sub_71005DD780(mActor, 70, nullptr, 0, 0))
        sub_71000F8798();
}

}  // namespace uking::action

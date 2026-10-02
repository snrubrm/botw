#include "Game/AI/Action/actionHorseRideAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

HorseRideAttack::HorseRideAttack(const InitArg& arg) : HorseRideLookWait(arg) {}

HorseRideAttack::~HorseRideAttack() = default;

bool HorseRideAttack::init_(sead::Heap* heap) {
    return HorseRideLookWait::init_(heap);
}

void HorseRideAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideLookWait::enter_(params);
    mFlags.reset(Flag::Changeable);
    _70 = false;
}

void HorseRideAttack::leave_() {
    sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
    HorseRideLookWait::leave_();
}

void HorseRideAttack::loadParams_() {
    HorseRideLookWait::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
}

void HorseRideAttack::calc_() {
    HorseRideLookWait::calc_();
}

}  // namespace uking::action

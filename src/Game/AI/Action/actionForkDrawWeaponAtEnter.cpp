#include "Game/AI/Action/actionForkDrawWeaponAtEnter.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkDrawWeaponAtEnter::ForkDrawWeaponAtEnter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDrawWeaponAtEnter::~ForkDrawWeaponAtEnter() = default;

bool ForkDrawWeaponAtEnter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDrawWeaponAtEnter::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    sub_71005DB5C0(mActor, *mWeaponIdx_s);
}

void ForkDrawWeaponAtEnter::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDrawWeaponAtEnter::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void ForkDrawWeaponAtEnter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

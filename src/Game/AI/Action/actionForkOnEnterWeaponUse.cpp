#include "Game/AI/Action/actionForkOnEnterWeaponUse.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

ForkOnEnterWeaponUse::ForkOnEnterWeaponUse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkOnEnterWeaponUse::~ForkOnEnterWeaponUse() = default;

bool ForkOnEnterWeaponUse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnEnterWeaponUse::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(1));
    mFlags.set(Flag::Changeable);
}

void ForkOnEnterWeaponUse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOnEnterWeaponUse::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void ForkOnEnterWeaponUse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

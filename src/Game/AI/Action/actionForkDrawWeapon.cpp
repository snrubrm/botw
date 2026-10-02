#include "Game/AI/Action/actionForkDrawWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkDrawWeapon::ForkDrawWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDrawWeapon::~ForkDrawWeapon() = default;

bool ForkDrawWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDrawWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkDrawWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDrawWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkDrawWeapon::calc_() {
    if (sub_71005DD780(mActor, 0x53, nullptr, *mTargetBone_s, *mSeqBank_s))
        sub_71005DB5C0(mActor, *mWeaponIdx_s);
}

}  // namespace uking::action

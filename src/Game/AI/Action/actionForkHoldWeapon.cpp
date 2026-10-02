#include "Game/AI/Action/actionForkHoldWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkHoldWeapon::ForkHoldWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkHoldWeapon::~ForkHoldWeapon() = default;

bool ForkHoldWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkHoldWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkHoldWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkHoldWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkHoldWeapon::calc_() {
    if (sub_71005DD780(mActor, 0x54, nullptr, *mTargetBone_s, *mSeqBank_s))
        sub_71005DB6D0(mActor, *mWeaponIdx_s);
}

}  // namespace uking::action

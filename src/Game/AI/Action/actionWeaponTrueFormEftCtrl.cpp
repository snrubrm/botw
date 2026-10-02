#include "Game/AI/Action/actionWeaponTrueFormEftCtrl.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

WeaponTrueFormEftCtrl::WeaponTrueFormEftCtrl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WeaponTrueFormEftCtrl::~WeaponTrueFormEftCtrl() = default;

bool WeaponTrueFormEftCtrl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WeaponTrueFormEftCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon || !weapon->m153()) {
        if (!isRootAiParamINot5())
            xlinkSearchAndEmit(mActor, mTransformKey_s.cstr(), 2, nullptr);
        xlinkSearchAndEmit(mActor, mTrueFormKey_s.cstr(), 2, &_40);
    }
    xlinkEventOn(mActor, 0x1c, 1, false);
    mFlags.set(Flag::Changeable);
}

void WeaponTrueFormEftCtrl::leave_() {
    _40.fadeXLink();
    xlinkEventOn(mActor, 0x1c, 0, false);
}

void WeaponTrueFormEftCtrl::loadParams_() {
    getStaticParam(&mTransformKey_s, "TransformKey");
    getStaticParam(&mTrueFormKey_s, "TrueFormKey");
}

void WeaponTrueFormEftCtrl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

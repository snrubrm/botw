#include "Game/AI/AI/aiWeaponThrowerSelector.h"
#include "Game/Actor/actWeapon.h"

namespace uking::ai {

WeaponThrowerSelector::WeaponThrowerSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponThrowerSelector::~WeaponThrowerSelector() = default;

bool WeaponThrowerSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponThrowerSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (weapon && (weapon->_e50 & 2) && weapon->_d68 == weapon->_d70)
        changeChild("プレイヤが投げた", params);
    else
        changeChild("その他が投げた", params);
}

void WeaponThrowerSelector::calc_() {}

void WeaponThrowerSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponThrowerSelector::loadParams_() {}

}  // namespace uking::ai

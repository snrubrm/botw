#include "Game/AI/Action/actionEquipedChemicalWeapon.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

EquipedChemicalWeapon::EquipedChemicalWeapon(const InitArg& arg) : EquipedAction(arg) {}

EquipedChemicalWeapon::~EquipedChemicalWeapon() = default;

void EquipedChemicalWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

bool EquipedChemicalWeapon::sub_710010E614() {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (weapon && (!weapon->_d38 || !(weapon->_d38->_18 & 1))) {
        weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
        if (weapon && weapon->isParentPlayer() && !weapon->m214() && weapon->_c4c)
            return weapon->_c20._0 == 0 || weapon->_c20._0 == 2;
    }
    return false;
}

void EquipedChemicalWeapon::calc_() {
    EquipedAction::calc_();
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (weapon && weapon->isParentPlayer() && weapon->m214() && weapon->_c4c &&
        (weapon->_c20._0 == 0 || weapon->_c20._0 == 2)) {
        weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
        if (!weapon || !weapon->_d38)
            return;
        weapon->_d38->sub_71002EF75C();
        if (auto* charge = weapon->_d38)
            charge->_18 |= 4;
        return;
    }
    const bool decrease = sub_710010E614();
    weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (decrease) {
        if (weapon && weapon->_d38)
            weapon->_d38->sub_71002EF850();
        return;
    }
    if (weapon && weapon->isParentPlayer()) {
        if (auto* charge = weapon->_d38) {
            if ((charge->_18 & 1) && weapon->_c4c &&
                (weapon->_c20._0 == 0 || weapon->_c20._0 == 2))
                charge->_18 |= 4;
        }
    }
}

}  // namespace uking::action

#include "Game/AI/Action/actionSetChemicalWeaponPower.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

SetChemicalWeaponPower::SetChemicalWeaponPower(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetChemicalWeaponPower::~SetChemicalWeaponPower() = default;

bool SetChemicalWeaponPower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetChemicalWeaponPower::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = -1;
    mFlags.set(Flag::Changeable);
}

void SetChemicalWeaponPower::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetChemicalWeaponPower::loadParams_() {}

void SetChemicalWeaponPower::calc_() {
    ksys::act::ai::Action::calc_();
}

void SetChemicalWeaponPower::sub_7100069F90(bool on, f32 ratio) {
    sub_71012412E4(mActor, 0x1b, ratio, false);
    xlinkEventOn(mActor, 0x1c, on, false);
}

void SetChemicalWeaponPower::sub_7100069FD0(bool flag) {
    if (flag)
        flyingObjectEmitXlink(mActor, "ChemSwordChargeLoop", 1, nullptr);
}

}  // namespace uking::action

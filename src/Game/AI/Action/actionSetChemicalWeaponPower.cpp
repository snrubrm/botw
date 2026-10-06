#include "Game/AI/Action/actionSetChemicalWeaponPower.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
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

void SetChemicalWeaponPower::sub_7100069E08(f32 ratio) {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    auto* as_list = weapon->getASList();
    if (!as_list)
        return;

    if (!(ratio >= 1.0f)) {
        if (_1c != 0) {
            if (as_list->sub_710115AA68("ChemCharge"))
                as_list->startAnimationMaybe(-1.0f, -1.0f, "ChemCharge", 0, 1, true);
            _1c = 0;
        }
        as_list->sub_710115F1D8(0, 1, ratio);
    } else if (_1c != 1) {
        if (as_list->sub_710115AA68("ChemFull")) {
            as_list->startAnimationMaybe(-1.0f, -1.0f, "ChemFull", 0, 1, true);
            setFinished();
        }
        _1c = 1;
    }
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

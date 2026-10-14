#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetChemicalWeaponPower : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetChemicalWeaponPower, ksys::act::ai::Action)
public:
    explicit SetChemicalWeaponPower(const InitArg& arg);
    ~SetChemicalWeaponPower() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // Declared only (the Charge / StopCharge actions call them with the weapon's charge ratio).
    // 0x7100069e08 (392 B)
    void sub_7100069E08(f32 ratio);
    // 0x7100069f90: sets xlink event 0x1b (`ratio`) and switches event 0x1c to `on`.
    void sub_7100069F90(bool on, f32 ratio);
    // 0x7100069fd0 (32 B)
    void sub_7100069FD0(bool flag);

    int _1c = -1;
};

}  // namespace uking::action

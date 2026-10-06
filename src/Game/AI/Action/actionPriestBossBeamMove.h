#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossBeamMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PriestBossBeamMove, ksys::act::ai::Action)
public:
    explicit PriestBossBeamMove(const InitArg& arg);
    ~PriestBossBeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const int* mShieldDamage_s{};
    // static_param at offset 0x30
    const int* mContactWaitFrame_s{};
    // static_param at offset 0x38
    const float* mReflectDeccel_s{};
    // map_unit_param at offset 0x40
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x48
    const int* mAttackPowerForPlayer_m{};
    // map_unit_param at offset 0x50
    const sead::Vector3f* mPosOffset_m{};
    // The members below are only known from the constructor (layout guess: sizes of the zeroed / initialised runs).
    u8 _58[0xc];
    sead::Vector3f _64 = sead::Vector3f::ez;
    u8 _70[0x30];
    sead::Vector3f _a0 = sead::Vector3f::zero;
    f32 _ac = 0.5f;
    u8 _b0[0x10]{};
    u8 _c0[0x15]{};
    u8 _d5[0x3];
};

}  // namespace uking::action

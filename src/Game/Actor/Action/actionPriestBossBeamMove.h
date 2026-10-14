#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class RigidBody;
}

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
    bool isFinished() const override;

protected:
    void calc_() override;

    // 0x710006566c (placeholder name): moves the beam bodies to `pos` (the transform of `_b8`, if `pos` is not zero) and
    // stops them.
    void sub_710006566C(const sead::Vector3f& pos);

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
    u64 _b0{};
    ksys::phys::RigidBody* _b8{};  // the beam body (its transform is copied to _c8)
    ksys::phys::RigidBody* _c0{};
    ksys::phys::RigidBody* _c8{};
    bool _d0{};
    bool _d1{};
    bool _d2{};
    bool _d3{};
    mutable bool _d4{};
    u8 _d5[0x3];
};

}  // namespace uking::action

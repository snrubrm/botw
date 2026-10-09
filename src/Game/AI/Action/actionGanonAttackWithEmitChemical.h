#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionGanonWeaponNearAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonAttackWithEmitChemical : public GanonWeaponNearAttack {
    SEAD_RTTI_OVERRIDE(GanonAttackWithEmitChemical, GanonWeaponNearAttack)
public:
    explicit GanonAttackWithEmitChemical(const InitArg& arg);
    ~GanonAttackWithEmitChemical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Complete native helper sleeps emitted actor parts and fades this action's sound effect.
    void sub_7100172FA8();
    virtual void m32(sead::Vector3f* pos);
    virtual float m33();
    virtual int m34();

    // static_param at offset 0xa8
    const int* mEmitNum_s{};
    // static_param at offset 0xb0
    const int* mEmitInterval_s{};
    // static_param at offset 0xb8
    const int* mEmitAttackPower_s{};
    // static_param at offset 0xc0
    const int* mEmitMinDamage_s{};
    // static_param at offset 0xc8
    const int* mChildCreateLimit_s{};
    // static_param at offset 0xd0
    const float* mEmitOffsetFromParent_s{};
    // static_param at offset 0xd8
    const float* mEmitIntervalDist_s{};
    // static_param at offset 0xe0
    const float* mEmitIntervalRotate_s{};
    // static_param at offset 0xe8
    const float* mEmitScale_s{};
    // static_param at offset 0xf0
    const float* mEmitMaxScale_s{};
    // static_param at offset 0xf8
    const float* mScaleTime_s{};
    // static_param at offset 0x100
    const float* mEmitStartFrame_s{};
    // static_param at offset 0x108
    const float* mEmitAngleFromParent_s{};
    // static_param at offset 0x110
    const float* mEmitActorSpeedRotate_s{};
    // static_param at offset 0x118
    sead::SafeString mEmitActorName_s{};
    // static_param at offset 0x128
    sead::SafeString mEmitBaseBoneName_s{};
    // static_param at offset 0x138
    sead::SafeString mEmitPartsName_s{};
    // static_param at offset 0x148
    sead::SafeString mCallSEKeyAtAtOn_s{};
    // static_param at offset 0x158
    const sead::Vector3f* mEmitActorSpeed_s{};
    // static_param at offset 0x160
    const sead::Vector3f* mEmitBoneRotateOffset_s{};
    f32 _168 = 0.0f;
    f32 _16c = 0.0f;
    f32 _170 = 0.0f;
    f32 _174 = 0.0f;
    bool _178 = false;
    bool _179 = false;
    bool _17a = false;
    u8 _17b;
    sead::Matrix34f _17c;
    u8 _1ac[4];
    u64 _1b0 = 0;
    u64 _1b8 = 0;
    u64 _1c0 = 0;
    u64 _1c8 = 0;
};
KSYS_CHECK_SIZE_NX150(GanonAttackWithEmitChemical, 0x1d0);

}  // namespace uking::action

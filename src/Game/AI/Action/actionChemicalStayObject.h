#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class ChemicalStayObject : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChemicalStayObject, ksys::act::ai::Action)
public:
    explicit ChemicalStayObject(const InitArg& arg);
    ~ChemicalStayObject() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void sub_71000DD774();

    // static_param at offset 0x20
    const int* mAtAttr_s{};
    // static_param at offset 0x28
    const float* mDeleteTime_s{};
    // static_param at offset 0x30
    const float* mCurveAng_s{};
    // static_param at offset 0x38
    const float* mReduceVelRate_s{};
    // static_param at offset 0x40
    const float* mCurveAngRandomRange_s{};
    // static_param at offset 0x48
    const float* mReduceVelRandomRange_s{};
    // static_param at offset 0x50
    const float* mSideAmplitude_s{};
    // static_param at offset 0x58
    const bool* mIsBindToGeneratedActor_s{};
    // static_param at offset 0x60
    const bool* mIsChemicalAttack_s{};
    // static_param at offset 0x68
    sead::SafeString mBindNodeName_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mBindOffset_s{};
    // map_unit_param at offset 0x80
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x88
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x90
    const int* mCreateLimit_m{};
    // map_unit_param at offset 0x98
    const float* mScaleTime_m{};
    s32 _a0 = 0;
    f32 _a4 = 1.0f;
    bool _a8 = false;
    f32 _ac = 0;
    f32 _b0 = 0;
    f32 _b4 = 0;
    s32 _b8 = 0;
    s32 _bc = 0;
    bool _c0 = false;
    u8 _c1[3];
    sead::Vector3f _c4;
    ksys::Timer _d0;
    ksys::Timer _dc;
    ksys::Timer _e8;
    ksys::act::ModelBindInfo _f8;
    ksys::act::BaseProcLink _198;
    sead::Buffer<ksys::act::BaseProcLink> _1a8;
};

}  // namespace uking::action

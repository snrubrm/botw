#pragma once

#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include "Game/AI/Action/actionChemicalAttackBall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LyzalfosFlame : public ChemicalAttackBall {
    SEAD_RTTI_OVERRIDE(LyzalfosFlame, ChemicalAttackBall)
public:
    explicit LyzalfosFlame(const InitArg& arg);
    ~LyzalfosFlame() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m33() override;

    struct Params {
        // static_param at offset 0x90
        const int* mLengthFrame_s{};
        // static_param at offset 0x98
        const int* mAtResetTime_s{};
        // static_param at offset 0xa0
        const int* mAtChaseFrame_s{};
        // static_param at offset 0xa8
        const int* mBindGrabNodeIdx_s{};
        // static_param at offset 0xb0
        const float* mChaseMax_s{};
        // static_param at offset 0xb8
        const float* mChaseRate_s{};
        // static_param at offset 0xc0
        const sead::Vector3f* mOffsetRot_s{};
    };
    Params mParams;
    ksys::act::ModelBindInfo _c8;
    s32 _168 = 0;
    s32 _16c = 0;
    s32 _170 = 0;
    f32 _174 = 0.0f;
    u64 _178 = 0;
    s32 _180 = 0;
    f32 _184 = 0.0f;
    f32 _188 = 0.0f;
    f32 _18c = 0.0f;
    f32 _190 = 0.0f;
    f32 _194 = 0.0f;
    u8 _198[0xc]{};
    f32 _1a4 = 0.0f;
    s32 _1a8 = 0;
    f32 _1ac = -1.0f;
    u64 _1b0 = 0;
    f32 _1b8 = -1.0f;
    f32 _1bc = 0.0f;
    f32 _1c0 = 0.0f;
    f32 _1c4 = -1.0f;
    xlink2::HandleSLink _1c8;
    bool _1d8 = false;
    u8 _1d9[0x7];
};
KSYS_CHECK_SIZE_NX150(LyzalfosFlame, 0x1e0);

}  // namespace uking::action

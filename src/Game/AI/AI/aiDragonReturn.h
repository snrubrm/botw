#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonReturn : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DragonReturn, ksys::act::ai::Ai)
public:
    explicit DragonReturn(const InitArg& arg);
    ~DragonReturn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_710036D5BC();

protected:
    // static_param at offset 0x38
    const float* mSpeed_s{};
    // static_param at offset 0x40
    const float* mRotateRate_s{};
    // static_param at offset 0x48
    const float* mChangeMoveHeight_s{};
    // static_param at offset 0x50
    const float* mFinishHeight_s{};
    // static_param at offset 0x58
    const float* mAngle_s{};
    // static_param at offset 0x60
    const float* mAvoidStartDistance_s{};
    // static_param at offset 0x68
    const float* mReturnStartFrame_s{};
    bool _70 = false;
    sead::Vector3f _74 = sead::Vector3f::ez;
    u64 _80 = 0;
    sead::Vector3f _88 = sead::Vector3f::ex;
    f32 _94 = 0;
    f32 _98 = -1.0f;
    bool _9c = false;
    // eft::Effect (undeclared; CSV eft::Effect::fadeXLink is called on &_a0 by leave_)
    u64 _a0 = 0;
    u32 _a8 = 0;
    u64 _b0 = 0;
    u32 _b8 = 0;
};
KSYS_CHECK_SIZE_NX150(DragonReturn, 0xc0);

}  // namespace uking::ai

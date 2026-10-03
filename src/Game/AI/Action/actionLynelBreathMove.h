#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelBreathMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LynelBreathMove, ksys::act::ai::Action)
public:
    explicit LynelBreathMove(const InitArg& arg);
    ~LynelBreathMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    u8 _1c[0x84];
    f32 _a0 = 10.0f;
    s32 _a4 = 0;
    s32 _a8 = 0;
    f32 _ac = 1.0f;
    f32 _b0 = 10.0f;
    bool _b4 = false;
    u8 _b5[0x3];
    s32 _b8 = 2139095039;
    s32 _bc = 2139095039;
    s32 _c0 = 2139095039;
    s32 _c4 = -8388609;
    s32 _c8 = -8388609;
    s32 _cc = -8388609;
    bool _d0 = true;
    u8 _d1[0x7];

};
KSYS_CHECK_SIZE_NX150(LynelBreathMove, 0xd8);

}  // namespace uking::action

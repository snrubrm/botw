#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockWaterWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OctarockWaterWait, ksys::act::ai::Ai)
public:
    explicit OctarockWaterWait(const InitArg& arg);
    ~OctarockWaterWait() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71004f10ec: changes to the "浮遊" child with the base height
    void sub_71004F10EC();
    // static_param at offset 0x38
    const int* mNoRiseTime_s{};
    // static_param at offset 0x40
    const int* mRiseDelayTimeMin_s{};
    // static_param at offset 0x48
    const int* mRiseDelayTimeMax_s{};
    // static_param at offset 0x50
    const int* mFinishFloatDelayTimeMin_s{};
    // static_param at offset 0x58
    const int* mFinishFloatDelayTimeMax_s{};
    // static_param at offset 0x60
    const float* mMinHeightFromWater_s{};
    // aitree_variable at offset 0x68
    void* mOctarockFormChangeUnit_a{};
    f32 _70 = 0;
    f32 _74 = 0;
    u32 _78 = 0;
    u32 _7c = 0;
    f32 _80 = 0;
    u32 _84 = 0;
    u32 _88 = 0;
    f32 _8c = -1.0f;
};
KSYS_CHECK_SIZE_NX150(OctarockWaterWait, 0x90);

}  // namespace uking::ai

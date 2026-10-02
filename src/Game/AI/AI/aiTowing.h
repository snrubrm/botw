#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class Towing : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Towing, ksys::act::ai::Ai)
public:
    explicit Towing(const InitArg& arg);
    ~Towing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();

protected:
    s32 _38 = 0;  // speed state (1: accelerating, 2: keeping the max speed, 3: slowing down)
    f32 _3c = 0;  // speed
    f32 _40 = 0;
    f32 _44 = 0;
    sead::Vector2f _48 = sead::Vector2f::zero;
    ksys::Timer _50;
    ksys::Timer _5c;
    ksys::Timer _68;
    bool _74 = false;
    bool _75 = false;
    // static_param at offset 0x78
    const int* mKeepMaxTime_s{};
    // static_param at offset 0x80
    const int* mStopTowingDef_s{};
    // static_param at offset 0x88
    const float* mMaxSpeed_s{};
    // static_param at offset 0x90
    const float* mInitSpeed_s{};
    // static_param at offset 0x98
    const float* mAddSpeed_s{};
    // static_param at offset 0xa0
    const float* mStandardSpeed_s{};
    // static_param at offset 0xa8
    const float* mBrakeDecSpeed_s{};
    // static_param at offset 0xb0
    const float* mAttFrontRate_s{};
    // static_param at offset 0xb8
    const float* mSandCheckLength_s{};
    // static_param at offset 0xc0
    const float* mSandCheckAngle_s{};
};

}  // namespace uking::ai

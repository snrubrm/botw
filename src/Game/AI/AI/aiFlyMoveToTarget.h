#pragma once

#include <container/seadRingBuffer.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyMoveToTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FlyMoveToTarget, ksys::act::ai::Ai)
public:
    explicit FlyMoveToTarget(const InitArg& arg);
    ~FlyMoveToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71003D4414();

protected:
    // static_param at offset 0x38
    const int* mMoveFailCount_s{};
    // static_param at offset 0x40
    const float* mFarDist_s{};
    // static_param at offset 0x48
    const float* mOutDist_s{};
    // static_param at offset 0x50
    const float* mOffsetHeight_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    sead::FixedRingBuffer<sead::Vector3f, 3> _60;
    sead::Vector3f _98;
    bool _a4{};
    f32 _a8{};
    f32 _ac{};
    f32 _b0{};
    u32 _b4{};
};

}  // namespace uking::ai

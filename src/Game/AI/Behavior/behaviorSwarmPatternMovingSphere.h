#pragma once

#include <math/seadVector.h>
#include "Game/AI/Behavior/behaviorSwarmPatternBase.h"

namespace uking::behavior {

class SwarmPatternMovingSphere : public SwarmPatternBase {
    SEAD_RTTI_OVERRIDE(SwarmPatternMovingSphere, SwarmPatternBase)
public:
    explicit SwarmPatternMovingSphere(const InitArg& arg);
    ~SwarmPatternMovingSphere() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;  // TODO 0x7100645118
    void m8() override;  // TODO 0x710064500c
    void m9() override;  // TODO 0x7100645470
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x48 */ const int* mUseSubActorNum_s{};
    /* 0x50 */ const float* mRadius_s{};
    /* 0x58 */ const float* mCycleSpeed_s{};
    /* 0x60 */ sead::Vector3f _60{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(SwarmPatternMovingSphere, 0x70);

}  // namespace uking::behavior

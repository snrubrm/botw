#pragma once

#include "Game/AI/Behavior/behaviorSwarmPattern.h"

namespace uking::behavior {

class SwarmPatternDoubleRing : public SwarmPattern {
    SEAD_RTTI_OVERRIDE(SwarmPatternDoubleRing, SwarmPattern)
public:
    explicit SwarmPatternDoubleRing(const InitArg& arg);
    ~SwarmPatternDoubleRing() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x50 */ const float* mRadius_s{};
    /* 0x58 */ const float* mCenterOffsetHalf_s{};
};
KSYS_CHECK_SIZE_NX150(SwarmPatternDoubleRing, 0x60);

}  // namespace uking::behavior

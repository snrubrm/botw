#pragma once

#include "Game/AI/Behavior/behaviorSwarmPattern.h"

namespace uking::behavior {

class SwarmPatternDisc : public SwarmPattern {
    SEAD_RTTI_OVERRIDE(SwarmPatternDisc, SwarmPattern)
public:
    explicit SwarmPatternDisc(const InitArg& arg);
    ~SwarmPatternDisc() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;  // TODO 0x7100644430
    void m9() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x50 */ const float* mRadius_s{};
};
KSYS_CHECK_SIZE_NX150(SwarmPatternDisc, 0x58);

}  // namespace uking::behavior

#pragma once

#include "Game/AI/Behavior/behaviorSwarmPattern.h"

namespace uking::behavior {

class SwarmPatternCross : public SwarmPattern {
    SEAD_RTTI_OVERRIDE(SwarmPatternCross, SwarmPattern)
public:
    explicit SwarmPatternCross(const InitArg& arg);
    ~SwarmPatternCross() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;  // TODO 0x7100643ff4
    void m9() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x50 */ const float* mWidth_s{};
};
KSYS_CHECK_SIZE_NX150(SwarmPatternCross, 0x58);

}  // namespace uking::behavior

#pragma once

#include "Game/AI/Behavior/behaviorSwarmPatternBase.h"

namespace uking::behavior {

class SwarmPattern : public SwarmPatternBase {
    SEAD_RTTI_OVERRIDE(SwarmPattern, SwarmPatternBase)
public:
    explicit SwarmPattern(const InitArg& arg);
    ~SwarmPattern() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x48 */ const float* mNoiseMax_s{};
};

}  // namespace uking::behavior

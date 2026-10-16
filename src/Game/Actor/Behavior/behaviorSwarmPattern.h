#pragma once

#include "Game/Actor/Behavior/behaviorSwarmPatternBase.h"

namespace uking::behavior {

class SwarmPattern : public SwarmPatternBase {
    SEAD_RTTI_OVERRIDE(SwarmPattern, SwarmPatternBase)
public:
    explicit SwarmPattern(const InitArg& arg);
    ~SwarmPattern() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x48 */ const float* mNoiseMax_s{};
};

}  // namespace uking::behavior

#pragma once

#include "Game/Actor/Behavior/behaviorSwarmPattern.h"

namespace uking::behavior {

class SwarmPatternCross : public SwarmPattern {
    SEAD_RTTI_OVERRIDE(SwarmPatternCross, SwarmPattern)
public:
    explicit SwarmPatternCross(const InitArg& arg);
    ~SwarmPatternCross() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x50 */ const float* mWidth_s{};
};
KSYS_CHECK_SIZE_NX150(SwarmPatternCross, 0x58);

}  // namespace uking::behavior

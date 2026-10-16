#pragma once

#include "Game/Actor/Behavior/behaviorSwarmPattern.h"

namespace uking::behavior {

class SwarmPatternDisc : public SwarmPattern {
    SEAD_RTTI_OVERRIDE(SwarmPatternDisc, SwarmPattern)
public:
    explicit SwarmPatternDisc(const InitArg& arg);
    ~SwarmPatternDisc() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x50 */ const float* mRadius_s{};
};
KSYS_CHECK_SIZE_NX150(SwarmPatternDisc, 0x58);

}  // namespace uking::behavior

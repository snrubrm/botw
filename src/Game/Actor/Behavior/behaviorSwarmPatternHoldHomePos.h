#pragma once

#include "Game/Actor/Behavior/behaviorSwarmPatternBase.h"

namespace uking::behavior {

class SwarmPatternHoldHomePos : public SwarmPatternBase {
    SEAD_RTTI_OVERRIDE(SwarmPatternHoldHomePos, SwarmPatternBase)
public:
    explicit SwarmPatternHoldHomePos(const InitArg& arg);
    ~SwarmPatternHoldHomePos() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x48 */ const int* mRotateType_s{};
};
KSYS_CHECK_SIZE_NX150(SwarmPatternHoldHomePos, 0x50);

}  // namespace uking::behavior

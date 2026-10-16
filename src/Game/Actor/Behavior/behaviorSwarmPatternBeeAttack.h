#pragma once

#include "Game/Actor/Behavior/behaviorSwarmPattern.h"

namespace uking::behavior {

class SwarmPatternBeeAttack : public SwarmPattern {
    SEAD_RTTI_OVERRIDE(SwarmPatternBeeAttack, SwarmPattern)
public:
    explicit SwarmPatternBeeAttack(const InitArg& arg);
    ~SwarmPatternBeeAttack() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x50 */ const float* mDepth_s{};
    /* 0x58 */ const float* mWidth_s{};
};
KSYS_CHECK_SIZE_NX150(SwarmPatternBeeAttack, 0x60);

}  // namespace uking::behavior

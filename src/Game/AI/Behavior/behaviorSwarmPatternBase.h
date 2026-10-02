#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::act {
class Swarm;
}

namespace uking::behavior {

// CSV name: SwarmPattern_.
class SwarmPatternBase : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SwarmPatternBase, ksys::act::ai::Behavior)
public:
    explicit SwarmPatternBase(const InitArg& arg);
    ~SwarmPatternBase() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual void m14(f32 value, act::Swarm* swarm);

    /* 0x28 */ const float* mSpeed_s{};
    /* 0x30 */ const float* mAccRateMin_s{};
    /* 0x38 */ const float* mAccRateMax_s{};
    /* 0x40 */ const bool* mIsAutoMove_s{};
};

}  // namespace uking::behavior

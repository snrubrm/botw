#pragma once

#include <math/seadVector.h>
#include "Game/Actor/Behavior/behaviorSwarmPatternBase.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

class SwarmPatternMovingSphere : public SwarmPatternBase {
    SEAD_RTTI_OVERRIDE(SwarmPatternMovingSphere, SwarmPatternBase)
public:
    explicit SwarmPatternMovingSphere(const InitArg& arg);
    ~SwarmPatternMovingSphere() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14(f32 value, act::Swarm* swarm) override;

    /* 0x48 */ const int* mUseSubActorNum_s{};
    /* 0x50 */ const float* mRadius_s{};
    /* 0x58 */ const float* mCycleSpeed_s{};
    /* 0x60 */ ksys::Timer _60;
};
KSYS_CHECK_SIZE_NX150(SwarmPatternMovingSphere, 0x70);

}  // namespace uking::behavior

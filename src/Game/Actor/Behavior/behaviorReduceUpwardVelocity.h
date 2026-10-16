#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ReduceUpwardVelocity : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ReduceUpwardVelocity, ksys::act::ai::Behavior)
public:
    explicit ReduceUpwardVelocity(const InitArg& arg);
    ~ReduceUpwardVelocity() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const float* mImpulseScale_s{};
    /* 0x30 */ const float* mMinDownImpulse_s{};
};
KSYS_CHECK_SIZE_NX150(ReduceUpwardVelocity, 0x38);

}  // namespace uking::behavior

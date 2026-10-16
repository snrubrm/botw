#pragma once

#include "Game/Actor/Behavior/behaviorGuardFrontBarrier.h"

namespace uking::behavior {

class GuardToTargetBarrier : public GuardFrontBarrier {
    SEAD_RTTI_OVERRIDE(GuardToTargetBarrier, GuardFrontBarrier)
public:
    explicit GuardToTargetBarrier(const InitArg& arg);
    ~GuardToTargetBarrier() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m15(sead::Matrix34f* out) override;

};
KSYS_CHECK_SIZE_NX150(GuardToTargetBarrier, 0x88);

}  // namespace uking::behavior

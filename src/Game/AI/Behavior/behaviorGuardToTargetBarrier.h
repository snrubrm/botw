#pragma once

#include "Game/AI/Behavior/behaviorGuardFrontBarrier.h"

namespace uking::behavior {

class GuardToTargetBarrier : public GuardFrontBarrier {
    SEAD_RTTI_OVERRIDE(GuardToTargetBarrier, GuardFrontBarrier)
public:
    explicit GuardToTargetBarrier(const InitArg& arg);
    ~GuardToTargetBarrier() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m15(sead::Matrix34f* out) override;

};
KSYS_CHECK_SIZE_NX150(GuardToTargetBarrier, 0x88);

}  // namespace uking::behavior

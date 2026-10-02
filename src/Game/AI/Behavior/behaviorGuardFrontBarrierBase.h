#pragma once

#include "Game/AI/Behavior/behaviorOnStateXLinkCreate.h"

namespace uking::behavior {

// CSV name: GuardFrontBarrier (the base of the GuardFrontBarrier behavior).
class GuardFrontBarrierBase : public OnStateXLinkCreate {
    SEAD_RTTI_OVERRIDE(GuardFrontBarrierBase, OnStateXLinkCreate)
public:
    explicit GuardFrontBarrierBase(const InitArg& arg);
    ~GuardFrontBarrierBase() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m14() override;

};

}  // namespace uking::behavior

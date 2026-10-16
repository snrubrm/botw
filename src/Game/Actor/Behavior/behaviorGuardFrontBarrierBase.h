#pragma once

#include "Game/Actor/Behavior/behaviorOnStateXLinkCreate.h"

namespace uking::behavior {

// CSV name: GuardFrontBarrier (the base of the GuardFrontBarrier behavior).
class GuardFrontBarrierBase : public OnStateXLinkCreate {
    SEAD_RTTI_OVERRIDE(GuardFrontBarrierBase, OnStateXLinkCreate)
public:
    explicit GuardFrontBarrierBase(const InitArg& arg);
    ~GuardFrontBarrierBase() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    bool m14() override;

};

}  // namespace uking::behavior

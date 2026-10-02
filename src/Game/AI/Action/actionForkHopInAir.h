#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkHopInAir : public Fork {
    SEAD_RTTI_OVERRIDE(ForkHopInAir, Fork)
public:
    explicit ForkHopInAir(const InitArg& arg);
    ~ForkHopInAir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;
    bool isFailed() const override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mHopHeight_s{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PlayerBarrierBlow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerBarrierBlow, ksys::act::ai::Ai)
public:
    explicit PlayerBarrierBlow(const InitArg& arg);
    ~PlayerBarrierBlow() override;

    bool isChangeable() const override { return false; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mBlowRagdollTime_s{};
    ksys::Timer _40{0.0f, 0.0f};
};
KSYS_CHECK_SIZE_NX150(PlayerBarrierBlow, 0x50);

}  // namespace uking::ai

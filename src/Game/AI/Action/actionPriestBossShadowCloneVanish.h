#pragma once

#include "Game/AI/Action/actionPriestBossWarpOrVanish.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossShadowCloneVanish : public PriestBossWarpOrVanish {
    SEAD_RTTI_OVERRIDE(PriestBossShadowCloneVanish, PriestBossWarpOrVanish)
public:
    explicit PriestBossShadowCloneVanish(const InitArg& arg);
    ~PriestBossShadowCloneVanish() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mDelayFrames_s{};
    ksys::Timer _30{0, 0};
};

KSYS_CHECK_SIZE_NX150(PriestBossShadowCloneVanish, 0x40);

}  // namespace uking::action

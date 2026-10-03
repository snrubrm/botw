#pragma once

#include "Game/AI/AI/aiPriestBossFormation.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PriestBossCircleFormationShoot : public PriestBossFormation {
    SEAD_RTTI_OVERRIDE(PriestBossCircleFormationShoot, PriestBossFormation)
public:
    explicit PriestBossCircleFormationShoot(const InitArg& arg);
    ~PriestBossCircleFormationShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m36() override;
    void m39() override;
    void m43() override;

protected:
    // static_param at offset 0x80
    const float* mHomingAttackTime_s{};
    ksys::Timer _88{};
};
KSYS_CHECK_SIZE_NX150(PriestBossCircleFormationShoot, 0x98);

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiSiteBossSwordApproachRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossFastWarpAttack : public SiteBossSwordApproachRoot {
    SEAD_RTTI_OVERRIDE(PriestBossFastWarpAttack, SiteBossSwordApproachRoot)
public:
    explicit PriestBossFastWarpAttack(const InitArg& arg);
    ~PriestBossFastWarpAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m35() override;
    void m36() override;
    void m38() override;
    bool m39() override;

protected:
    // Copies of the base's _90 / _9c / _a8 / _b4 vectors, taken once by m35 (guarded by _f0).
    sead::Vector3f _c0;
    sead::Vector3f _cc;
    sead::Vector3f _d8;
    sead::Vector3f _e4;
    bool _f0 = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossFastWarpAttack, 0xf8);

}  // namespace uking::ai

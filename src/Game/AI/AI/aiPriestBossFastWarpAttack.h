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

    bool m39() override;

protected:
    void* _c0;
    u32 _c8;
    u8 _cc[0xd4 - 0xcc];
    u32 _d4;
    void* _d8;
    u32 _e0;
    u8 _e4[0xec - 0xe4];
    u32 _ec;
    bool _f0 = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossFastWarpAttack, 0xf8);

}  // namespace uking::ai

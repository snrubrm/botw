#pragma once

#include "Game/AI/AI/aiSiteBossSwordApproachRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordRailApproach : public SiteBossSwordApproachRoot {
    SEAD_RTTI_OVERRIDE(SiteBossSwordRailApproach, SiteBossSwordApproachRoot)
public:
    explicit SiteBossSwordRailApproach(const InitArg& arg);
    ~SiteBossSwordRailApproach() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m34(sead::Vector3f* out) override;

protected:
    // dynamic_param at offset 0xc0
    bool* mIsResetOldMoveIdx_d{};
    s32 _c8 = -1;
    bool _cc = false;
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordRailApproach, 0xd0);

}  // namespace uking::ai

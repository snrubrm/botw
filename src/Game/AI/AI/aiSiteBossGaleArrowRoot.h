#pragma once

#include "Game/AI/AI/aiWithoutWeaponArrow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossGaleArrowRoot : public WithoutWeaponArrow {
    SEAD_RTTI_OVERRIDE(SiteBossGaleArrowRoot, WithoutWeaponArrow)
public:
    explicit SiteBossGaleArrowRoot(const InitArg& arg);
    ~SiteBossGaleArrowRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool m37(bool* broke_ice_block, bool* hit_player) override;

protected:
};

}  // namespace uking::ai

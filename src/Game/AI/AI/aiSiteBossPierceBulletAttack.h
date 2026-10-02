#pragma once

#include "Game/AI/AI/aiSiteBossShootNormalArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossPierceBulletAttack : public SiteBossShootNormalArrowRoot {
    SEAD_RTTI_OVERRIDE(SiteBossPierceBulletAttack, SiteBossShootNormalArrowRoot)
public:
    explicit SiteBossPierceBulletAttack(const InitArg& arg);
    ~SiteBossPierceBulletAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;

    bool m34() override;
    s32 m44() override;

protected:
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/Action/actionSiteBossSpearAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

class SiteBossSpearAttackVertical : public SiteBossSpearAttackBase {
    SEAD_RTTI_OVERRIDE(SiteBossSpearAttackVertical, SiteBossSpearAttackBase)
public:
    explicit SiteBossSpearAttackVertical(const InitArg& arg);
    ~SiteBossSpearAttackVertical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    ksys::act::BaseProcHandle _f0;
    // static_param at offset 0x100
    const int* mShockWaveAttackPower_s{};
};
KSYS_CHECK_SIZE_NX150(SiteBossSpearAttackVertical, 0x108);

}  // namespace uking::action

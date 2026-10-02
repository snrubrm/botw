#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class SiteBossSwordIronPileRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSwordIronPileRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSwordIronPileRoot(const InitArg& arg);
    ~SiteBossSwordIronPileRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFallWaitCount_s{};
    // static_param at offset 0x40
    const float* mFallSpeed_s{};
    // static_param at offset 0x48
    const float* mSlopeRate_s{};
    // map_unit_param at offset 0x50
    const int* mAddAtkPower_m{};
    // map_unit_param at offset 0x58
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x60
    const int* mAttackPowerForPlayer_m{};
    // map_unit_param at offset 0x68
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x70
    sead::SafeString mActorName_m{};
    bool _80 = false;
    bool _81 = false;
    bool _82 = false;
    u32 _84 = 0;
    f32 _88 = 0;
    ksys::Timer _8c{};
    u32 _98 = 0;
    u32 _9c = 0;
    u32 _a0 = 0;
    sead::Vector3f _a4 = {0, 0, 0};
    ksys::act::BaseProcLink _b0;
    Unk_71012419b4 _c0;
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordIronPileRoot, 0xe0);

}  // namespace uking::ai

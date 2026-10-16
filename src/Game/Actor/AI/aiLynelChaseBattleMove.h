#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LynelChaseBattleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelChaseBattleMove, ksys::act::ai::Ai)
public:
    explicit LynelChaseBattleMove(const InitArg& arg);
    ~LynelChaseBattleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    // 0x710048f5a0 (placeholder name): 3 without a target, else 0 / 1 / 2 when the target is beyond the speed-up
    // distance / in between / closer than the slow-down distance along the actor's front axis.
    s32 sub_710048F5A0();

protected:
    // static_param at offset 0x38
    const float* mSlowDownDist_s{};
    // static_param at offset 0x40
    const float* mSpeedUpDist_s{};
    // static_param at offset 0x48
    const float* mBaseDist_s{};
    // static_param at offset 0x50
    const float* mOutDist_s{};
    // static_param at offset 0x58
    const float* mCloseStartDist_s{};
    ksys::act::Unk_7100d3bce4 _60{mActor};
};

}  // namespace uking::ai

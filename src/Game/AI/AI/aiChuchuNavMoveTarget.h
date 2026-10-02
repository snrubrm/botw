#pragma once

#include "Game/AI/AI/aiNavMoveTarget.h"
#include "Game/AI/aiUnk_71023698d0.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChuchuNavMoveTarget : public NavMoveTarget {
    SEAD_RTTI_OVERRIDE(ChuchuNavMoveTarget, NavMoveTarget)
public:
    explicit ChuchuNavMoveTarget(const InitArg& arg);
    ~ChuchuNavMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x380
    const int* mWallHitTime_s{};
    /* 0x388 */ Unk_71025b0588_Data _388;
};
KSYS_CHECK_SIZE_NX150(ChuchuNavMoveTarget, 0x430);

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class BreathEnemyRangeKeepMove : public EnemyRangeKeepMove {
    SEAD_RTTI_OVERRIDE(BreathEnemyRangeKeepMove, EnemyRangeKeepMove)
public:
    explicit BreathEnemyRangeKeepMove(const InitArg& arg);
    ~BreathEnemyRangeKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_7100340570();
    // 0x710034076c: whether the breath part actor (by BreathName) is in the calc state.
    bool sub_710034076C();

    bool sub_710033FB98(sead::Heap* heap);
protected:
    void sub_71003401FC();
    // static_param at offset 0x110
    const int* mEnlargeTime_s{};
    // static_param at offset 0x118
    const float* mAttackRatio_s{};
    // static_param at offset 0x120
    const float* mBreathSize_s{};
    // static_param at offset 0x128
    sead::SafeString mBreathName_s{};
    // static_param at offset 0x138
    sead::SafeString mBaseNode_s{};
    // static_param at offset 0x148
    const int* mLoopTime_s{};
    // static_param at offset 0x150
    const float* mBreathEndDist_s{};
    // static_param at offset 0x158
    const int* mBreathMinTime_s{};
    ksys::Timer _160{0, 0};
    bool _16c = false;
};

}  // namespace uking::ai

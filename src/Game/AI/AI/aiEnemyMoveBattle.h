#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyMoveBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(EnemyMoveBattle, EnemyBattle)
public:
    explicit EnemyMoveBattle(const InitArg& arg);
    ~EnemyMoveBattle() override;
    bool isFinished() const override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x90
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x98
    const int* mLimitMoveTime_s{};
    // static_param at offset 0xa0
    const float* mMoveDist_s{};
    ksys::Timer _a8{0, 0};
    ksys::Timer _b4{0, 0};
};

}  // namespace uking::ai

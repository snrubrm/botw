#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyPursuingBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(EnemyPursuingBattle, EnemyBattle)
public:
    explicit EnemyPursuingBattle(const InitArg& arg);
    ~EnemyPursuingBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;
    // 0x71003a9ae8 (placeholder name; declared only)
    bool sub_71003A9AE8();
    // 0x71003a9d24 (placeholder name)
    void changeToFollowUpAttack();

protected:
    // static_param at offset 0x90
    const int* mPursuingAttackInterval_s{};
    // static_param at offset 0x98
    const int* mPursuingAttackIntervalRand_s{};
    // static_param at offset 0xa0
    const float* mPursuingAttackStartAng_s{};
    ksys::Timer _a8{0, 0};
};

}  // namespace uking::ai

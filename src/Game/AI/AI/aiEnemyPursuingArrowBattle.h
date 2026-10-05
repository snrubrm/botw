#pragma once

#include "Game/AI/AI/aiBokoblinArrowBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyPursuingArrowBattle : public BokoblinArrowBattle {
    SEAD_RTTI_OVERRIDE(EnemyPursuingArrowBattle, BokoblinArrowBattle)
public:
    explicit EnemyPursuingArrowBattle(const InitArg& arg);
    ~EnemyPursuingArrowBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;
    // 0x71003a8a44 (placeholder name)
    void changeToFollowUp();

protected:
    // static_param at offset 0x128
    const int* mPursuingAttackInterval_s{};
    // static_param at offset 0x130
    const int* mPursuingAttackIntervalRand_s{};
    // static_param at offset 0x138
    const float* mPursuingAttackStartDist_s{};
    // static_param at offset 0x140
    const float* mPursuingAttackStartAng_s{};
    ksys::Timer _148{0, 0};
};

}  // namespace uking::ai

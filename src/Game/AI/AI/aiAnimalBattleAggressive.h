#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalBattleAggressive : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(AnimalBattleAggressive, EnemyBattle)
public:
    explicit AnimalBattleAggressive(const InitArg& arg);
    ~AnimalBattleAggressive() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m37() override;
    bool m40() override;
    virtual void m44();
    virtual void m45();

protected:
    // static_param at offset 0x90
    const int* mForceAttackTimer_s{};
    // static_param at offset 0x98
    const int* mCounterAttackTimer_s{};
    // static_param at offset 0xa0
    const float* mForceAttackRange_s{};
    // static_param at offset 0xa8
    const float* mCounterAttackRange_s{};
    // aitree_variable at offset 0xb0
    bool* mAnimalEnableCounterFlag_a{};
    ksys::Timer _b8;
    ksys::Timer _c4;
};

}  // namespace uking::ai

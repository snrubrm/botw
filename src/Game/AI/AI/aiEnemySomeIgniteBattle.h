#pragma once

#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"
#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::ai {

class EnemySomeIgniteBattle : public BreathAttackEnemyBattle {
    SEAD_RTTI_OVERRIDE(EnemySomeIgniteBattle, BreathAttackEnemyBattle)
public:
    explicit EnemySomeIgniteBattle(const InitArg& arg);
    ~EnemySomeIgniteBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m39() override;
    void m37() override;
    void m42() override;
    void m43() override;
    bool m44() override;

protected:
    // static_param at offset 0xb0
    const int* mIgniteNum_s{};
    sead::SafeArray<ksys::act::BaseProcHandle, 5> _b8;
};

}  // namespace uking::ai

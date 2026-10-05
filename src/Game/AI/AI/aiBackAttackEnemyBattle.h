#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BackAttackEnemyBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(BackAttackEnemyBattle, EnemyBattle)
public:
    explicit BackAttackEnemyBattle(const InitArg& arg);
    ~BackAttackEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    // 0x710032611c (placeholder name)
    void changeToBackAttack();

protected:
    bool sub_7100325F84();

    // static_param at offset 0x90
    const float* mBackAttackAngle_s{};
    Unk_7102451ba0 _98;
};

}  // namespace uking::ai

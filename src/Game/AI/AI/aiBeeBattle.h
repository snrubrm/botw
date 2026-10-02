#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeeBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(BeeBattle, EnemyBattle)
public:
    explicit BeeBattle(const InitArg& arg);
    ~BeeBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m36(sead::Vector3f* pos) override;

protected:
};

}  // namespace uking::ai

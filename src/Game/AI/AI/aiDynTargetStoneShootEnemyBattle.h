#pragma once

#include "Game/AI/AI/aiStoneShootEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DynTargetStoneShootEnemyBattle : public StoneShootEnemyBattle {
    SEAD_RTTI_OVERRIDE(DynTargetStoneShootEnemyBattle, StoneShootEnemyBattle)
public:
    explicit DynTargetStoneShootEnemyBattle(const InitArg& arg);
    ~DynTargetStoneShootEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    ksys::act::BaseProcLink& m35() override;

protected:
    // dynamic_param at offset 0xb0
    ksys::act::BaseProcLink* mTargetActor_d{};
};
KSYS_CHECK_SIZE_NX150(DynTargetStoneShootEnemyBattle, 0xb8);

}  // namespace uking::ai

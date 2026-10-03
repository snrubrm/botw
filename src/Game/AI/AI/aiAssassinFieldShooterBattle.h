#pragma once

#include "Game/AI/AI/aiAssassinFieldShooterBattleBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinFieldShooterBattle : public AssassinFieldShooterBattleBase {
    SEAD_RTTI_OVERRIDE(AssassinFieldShooterBattle, AssassinFieldShooterBattleBase)
public:
    explicit AssassinFieldShooterBattle(const InitArg& arg);
    ~AssassinFieldShooterBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34() override;

protected:
};

}  // namespace uking::ai

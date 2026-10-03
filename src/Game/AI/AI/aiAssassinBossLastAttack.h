#pragma once

#include "Game/AI/AI/aiAssassinBossIronBallAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossLastAttack : public AssassinBossIronBallAttack {
    SEAD_RTTI_OVERRIDE(AssassinBossLastAttack, AssassinBossIronBallAttack)
public:
    explicit AssassinBossLastAttack(const InitArg& arg);
    ~AssassinBossLastAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100318f5c: whether any of the iron ball part actors satisfies
    // ActorConstDataAccess::sub_7100D13BB8.
    bool sub_7100318F5C();

protected:
};

}  // namespace uking::ai

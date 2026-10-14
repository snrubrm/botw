#pragma once

#include "Game/Actor/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GiantEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(GiantEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit GiantEnemyFindPlayer(const InitArg& arg);
    ~GiantEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool m35() override;
    bool m36(bool b) override;
    bool m37() override;

protected:
};

}  // namespace uking::ai

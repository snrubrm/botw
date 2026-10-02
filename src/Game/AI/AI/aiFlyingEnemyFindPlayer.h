#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(FlyingEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit FlyingEnemyFindPlayer(const InitArg& arg);
    ~FlyingEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m38() override { return false; }

    bool sub_71003D2E30(const sead::Vector3f& pos);
    bool m36(bool b) override;
    bool m37() override;
protected:
};

}  // namespace uking::ai

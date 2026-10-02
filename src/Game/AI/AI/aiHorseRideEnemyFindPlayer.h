#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(HorseRideEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit HorseRideEnemyFindPlayer(const InitArg& arg);
    ~HorseRideEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    bool m38() override;
    bool m39(const sead::Vector3f& pos, bool b) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

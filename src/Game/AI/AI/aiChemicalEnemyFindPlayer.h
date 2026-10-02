#pragma once

#include "Game/AI/AI/aiLandHumEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChemicalEnemyFindPlayer : public LandHumEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(ChemicalEnemyFindPlayer, LandHumEnemyFindPlayer)
public:
    explicit ChemicalEnemyFindPlayer(const InitArg& arg);
    ~ChemicalEnemyFindPlayer() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // In the tail padding of LandHumEnemyFindPlayer.
    bool _1e2 = true;
};
KSYS_CHECK_SIZE_NX150(ChemicalEnemyFindPlayer, 0x1e8);

}  // namespace uking::ai

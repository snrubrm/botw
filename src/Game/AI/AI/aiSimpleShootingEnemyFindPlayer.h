#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SimpleShootingEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(SimpleShootingEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit SimpleShootingEnemyFindPlayer(const InitArg& arg);
    ~SimpleShootingEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    f32 m34() override;
    bool m42(s32 x) override;
    bool m43() override;

protected:
    // static_param at offset 0x140
    const float* mShootBaseDist_s{};
    // static_param at offset 0x148
    const float* mShootDistRatio_s{};
};

}  // namespace uking::ai

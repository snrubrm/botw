#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(MimicEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit MimicEnemyFindPlayer(const InitArg& arg);
    ~MimicEnemyFindPlayer() override;
    bool isFinished() const override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;
    bool m35() override;

protected:
    void sub_71004A70B4();

    // static_param at offset 0x140
    const float* mPlayerForceFindDist_s{};
    // aitree_variable at offset 0x148
    int* mMimicryMaterial_a{};
    // aitree_variable at offset 0x150
    bool* mIsStartResetMimicry_a{};
};

}  // namespace uking::ai

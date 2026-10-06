#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwimEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(SwimEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit SwimEnemyFindPlayer(const InitArg& arg);
    ~SwimEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m35() override;
    bool m36(bool b) override;
    bool m37() override;
    bool m38() override;

protected:
    // 0x71005b4054: sets _170 to 15, then changes to the "対象壁つかまり" child
    void sub_71005B4054();
    // static_param at offset 0x140
    const bool* mIsAbleToLand_s{};
    u64 _148;
    // static_param at offset 0x150
    const float* mNearScaffoldDist_s{};
    // static_param at offset 0x158
    const float* mClimbVmin_s{};
    // static_param at offset 0x160
    const float* mClimbVmax_s{};
    // static_param at offset 0x168
    const float* mClimbHmax_s{};
    f32 _170 = 0;
};
KSYS_CHECK_SIZE_NX150(SwimEnemyFindPlayer, 0x178);

}  // namespace uking::ai

#pragma once

#include <container/seadBuffer.h>
#include "Game/AI/AI/aiEnemyBattle.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossFirstBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(AssassinBossFirstBattle, EnemyBattle)
public:
    explicit AssassinBossFirstBattle(const InitArg& arg);
    ~AssassinBossFirstBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    bool m40() override;
    bool m41() override;

    void sub_710031657C(s32 a1, s32 a2);

protected:
    // static_param at offset 0x90
    const int* mIronBallNum_s{};
    // static_param at offset 0x98
    const float* mGuardAngle_s{};
    // static_param at offset 0xa0
    const float* mAttackInterseptDist_s{};
    // static_param at offset 0xa8
    sead::SafeString mIronBallKeyName_s{};
    // One message sender per iron ball (allocated in init_).
    sead::Buffer<Unk_7102368740> _b8;
    u32 _c8 = 0;
    u32 _cc = 0;
    u32 _d0 = 0;
};

}  // namespace uking::ai

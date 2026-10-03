#pragma once

#include "Game/AI/AI/aiShootingEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class HorseRideShootingEnemyBattle : public ShootingEnemyBattle {
    SEAD_RTTI_OVERRIDE(HorseRideShootingEnemyBattle, ShootingEnemyBattle)
public:
    explicit HorseRideShootingEnemyBattle(const InitArg& arg);
    ~HorseRideShootingEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x7100443a58 (placeholder name)
    void sub_7100443A58();
    // 0x7100443b28 (placeholder name)
    void sub_7100443B28();
    // 0x7100443c04 (placeholder name)
    void sub_7100443C04();

protected:
    // static_param at offset 0xc8
    const int* mTrackTime_s{};
    // static_param at offset 0xd0
    const int* mTrackTimeRand_s{};
    // static_param at offset 0xd8
    const int* mSlowTime_s{};
    // static_param at offset 0xe0
    const int* mSlowTimeRand_s{};
    ksys::Timer _e8;
    int _f4{};
    int _f8{};
    int _fc{};
    int _100{};
};

}  // namespace uking::ai

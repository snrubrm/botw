#pragma once

#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

#include "Game/AI/AI/aiSimpleShootingEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ShootingEnemyFindPlayer : public SimpleShootingEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(ShootingEnemyFindPlayer, SimpleShootingEnemyFindPlayer)
public:
    explicit ShootingEnemyFindPlayer(const InitArg& arg);
    ~ShootingEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m45() override;
    bool m46() override;

protected:
    // Unnamed in the binary (0x710056aa30 / 0x710056ab10): change to the "隠れる" / "隠れられない" child with the
    // target position (all four are called by calc_).
    void sub_710056AA30();
    void sub_710056AB10();
    // 0x710056abf0
    bool sub_710056ABF0();
    // 0x710056ad84: changes to the "危険回避" child with the position of _180.
    void sub_710056AD84();

    struct Params {
        // static_param at offset 0x150
        const int* mReHideTime_s{};
        // static_param at offset 0x158
        const float* mExplosivesAvoidDist_s{};
        // static_param at offset 0x160
        const float* mExplosivesAvoidSpeed_s{};
        // static_param at offset 0x168
        const float* mExplosivesAvoidAng_s{};
        // static_param at offset 0x170
        const float* mHideStartDistMin_s{};
        // static_param at offset 0x178
        const float* mHideStartDistMax_s{};
    };
    Params mParams;
    ksys::act::BaseProcLink _180;
    ksys::Timer _190{0, 0};
};
KSYS_CHECK_SIZE_NX150(ShootingEnemyFindPlayer, 0x1a0);

}  // namespace uking::ai

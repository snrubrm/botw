#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyRangeKeepSwimMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRangeKeepSwimMove, ksys::act::ai::Ai)
public:
    explicit EnemyRangeKeepSwimMove(const InitArg& arg);
    ~EnemyRangeKeepSwimMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x71003ae3c4 (placeholder name)
    void changeToMoveSideways(s8 dir);

protected:
    // 0x71003adee4 (placeholder name): whether a point 5 units away from the player (XZ) is not on the navmesh
    // or the navmesh query there does not hit the surface type 6.
    bool sub_71003ADEE4();
    // 0x71003aed8c (placeholder name): restarts the timer `_84` (random 4..10) once the player is within range,
    // else counts it down while it is running.
    void sub_71003AED8C();
    // 0x71003aee84 (placeholder name): same for `_78` (random 15..29) with the close distance.
    void sub_71003AEE84();

    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mTime_s{};
    // static_param at offset 0x48
    const float* mCloseDist_s{};
    // static_param at offset 0x50
    const float* mFarDist_s{};
    // static_param at offset 0x58
    const float* mOutDist_s{};
    // static_param at offset 0x60
    const float* mBaseDist_s{};
    // static_param at offset 0x68
    const float* mSpaceDist_s{};
    // static_param at offset 0x70
    const bool* mIsCheckCliff_s{};
    ksys::Timer _78;
    ksys::Timer _84;
    ksys::Timer _90;
};

}  // namespace uking::ai

#pragma once

#include <container/seadObjList.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_71025b0578.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class NavMoveTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NavMoveTarget, ksys::act::ai::Ai)
public:
    explicit NavMoveTarget(const InitArg& arg);
    ~NavMoveTarget() override;

    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // Inline in the original (emitted in ChuchuNavMoveTarget's TU, 0x710034d6a4).
    virtual sead::Vector3f* m34() { return mParams.mTargetPos_d; }
    virtual void m35(sead::Vector3f* out);
    virtual bool m36();
    virtual bool m37();

protected:
    void calc_() override;

    /* 0x38 */ void* _38{};
    // aitree_variable at offset 0x40
    void* mRefPosVibrateCheckerForAI_a{};
    // aitree_variable at offset 0x48
    void* mRefVelRotVibrateCheckerforAI_a{};
    /* 0x50 */ sead::FixedObjList<sead::Vector3f, 20> _50;
    /* 0x300 */ u64 _300 = 0;
    /* 0x308 */ u32 _308 = 0;
    /* 0x310 */ Unk_71000b0800<Unk_71025b0578> _310;
    /* 0x318 */ Unk_71000b0800<Unk_71025b7688> _318;
    struct Params {
        // static_param at offset 0x320
        const int* mWeaponIdx_s{};
        // static_param at offset 0x328
        const float* mReachTargetArea_s{};
        // static_param at offset 0x330
        const float* mRepathTime_s{};
        // static_param at offset 0x338
        const float* mTooFarDist_s{};
        // static_param at offset 0x340
        const bool* mUseCharacterRadius_s{};
        // static_param at offset 0x348
        const int* mVibrateCheckTime_s{};
        // static_param at offset 0x350
        const int* mRotVibrateCheckTime_s{};
        // static_param at offset 0x358
        const bool* mIsLastLineReachCheck_s{};
        // dynamic_param at offset 0x360
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    // Result of sub_71005E2BCC (init_): the enemy's navmesh move state.
    /* 0x368 */ uking::act::Enemy::Unk_12d0* _368{};
    /* 0x370 */ ksys::Timer _370{0, 0};
};
KSYS_CHECK_SIZE_NX150(NavMoveTarget, 0x380);

}  // namespace uking::ai

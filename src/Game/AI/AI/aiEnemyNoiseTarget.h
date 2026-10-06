#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class EnemyNoiseTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoiseTarget, ksys::act::ai::Ai)
public:
    explicit EnemyNoiseTarget(const InitArg& arg);
    ~EnemyNoiseTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x710039b064 (placeholder names): turns to the unreachable state / whether the enemy has no usable weapon.
    void sub_710039B064();
    bool sub_710039B164();
    // 0x710039b400 (placeholder name): picks up the shield (the target weapon `_c8`).
    void sub_710039B400();
    // 0x710039b240 (placeholder name): the weapon of the shield slot can be picked up; stores its link in `out`.
    bool sub_710039B240(ksys::act::BaseProcLink* out);

protected:
    // aitree_variable at offset 0x38
    bool* mIsTrgChangeUnderWaterState_a{};
    // static_param at offset 0x40
    const int* mLostTime_s{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const int* mRerouteTimeMin_s{};
    // static_param at offset 0x58
    const int* mRerouteTimeMax_s{};
    // static_param at offset 0x60
    const float* mNearDist_s{};
    // static_param at offset 0x68
    const float* mFarDist_s{};
    // static_param at offset 0x70
    const int* mShieldIdx_s{};
    // static_param at offset 0x78
    const float* mSearchShieldDist_s{};
    // static_param at offset 0x80
    const int* mNoShieldEquipWpIdx_s{};
    // static_param at offset 0x88
    const float* mNoShieldSearchDist_s{};
    // static_param at offset 0x90
    const float* mUnReachableToRepathDist_s{};
    // static_param at offset 0x98
    const float* mTooFarPathDist_s{};
    f32 _a0{};
    s32 _a4{};
    s32 _a8{};
    sead::Vector3f _ac;
    u32 _b8{};
    sead::Vector3f _bc;
    ksys::act::BaseProcLink _c8;
    bool _d8{};
};

}  // namespace uking::ai

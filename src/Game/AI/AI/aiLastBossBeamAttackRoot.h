#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::ai {

class LastBossBeamAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossBeamAttackRoot, ksys::act::ai::Ai)
public:
    explicit LastBossBeamAttackRoot(const InitArg& arg);
    ~LastBossBeamAttackRoot() override;

    bool isFinished() const override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x710047555c (not decompiled; called by init_).
    void sub_710047555C();
    // 0x7100475b28 (placeholder name): the point the beam aims at: the target's (or the player's) position
    // raised by 1, pulled back by a ray cast from the model's bone / the actor.
    void sub_7100475B28(sead::Vector3f* out);
    // 0x710047679c (placeholder name)
    void changeToFire(const sead::Vector3f& target_pos);

protected:
    // Inline-only in the original (name guess; evidence: the param pack and name temporary sit above enter_'s target).
    void changeToAim(const sead::Vector3f& target_pos);

    // static_param at offset 0x38
    const int* mAttackPowerForPlayer_s{};
    // static_param at offset 0x40
    const int* mAttackPower_s{};
    // static_param at offset 0x48
    const int* mAtMinDamage_s{};
    // static_param at offset 0x50
    const int* mAddAttackPower_s{};
    // static_param at offset 0x58
    const float* mWaitTime_s{};
    // static_param at offset 0x60
    const float* mKeepDistance_s{};
    // static_param at offset 0x68
    const float* mMoveSpeed_s{};
    // static_param at offset 0x70
    const float* mInitSpeed_s{};
    // static_param at offset 0x78
    const float* mAccel_s{};
    // static_param at offset 0x80
    const float* mKeepDistanceRand_s{};
    // static_param at offset 0x88
    const float* mRandKeepFrame_s{};
    // static_param at offset 0x90
    const float* mBrakeStartFrame_s{};
    // static_param at offset 0x98
    const float* mMoveYSpeed_s{};
    // static_param at offset 0xa0
    const bool* mIsMove_s{};
    // static_param at offset 0xa8
    const bool* mIsChangeable_s{};
    // static_param at offset 0xb0
    const bool* mIsCreateGuardEffect_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mReflectOffset_s{};
    ksys::Timer _c0;
    ksys::VFRValue _cc;
    bool _d8 = false;
    sead::Vector3f _dc;
    u64 _e8 = 0;
    ksys::Timer _f0;
    ksys::Timer _fc;
    sead::Matrix33f _108;
    gsys::BoneAccessKeyEx _130;
    ksys::act::BaseProcLink _168;
};
KSYS_CHECK_SIZE_NX150(LastBossBeamAttackRoot, 0x178);

}  // namespace uking::ai

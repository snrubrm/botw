#pragma once

#include "Game/AI/AI/aiPriestBossActorRoot.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "Game/AI/aiPriestBossWeightedPool.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include <container/seadSafeArray.h>
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PriestBossActorGiantRoot : public PriestBossActorRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorGiantRoot, PriestBossActorRoot)
public:
    // Attack indices (names unknown; 11 values: the clamp of the counter array).
    SEAD_ENUM(Attack, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)
    // Movement state (names unknown): 2 = inactive, 7 = no face position update, 8 = also sets the child's
    // TargetPos.
    SEAD_ENUM(State, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)

    explicit PriestBossActorGiantRoot(const InitArg& arg);
    ~PriestBossActorGiantRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual const char* m36();
    virtual f32 m37();
    virtual f32 m38();
    virtual f32 m39();
    virtual f32 m40();
    virtual f32 m41();
    virtual f32 m42();
    virtual f32 m43();
    virtual f32 m44();
    virtual f32 m45();
    // m46: the attack index of the child's last attack (0x710050924c; also counts it in `_b0`, not decompiled);
    // m47 is not decompiled (0x710050941c).
    virtual Attack m46();
    virtual void m47();

protected:
    // inline-only in the original; name is a guess. Evidence: m40 / m41 / m42 / m44 repeat the same sequence
    // for attacks 3 / 4 / 5 / 7 (frequency of the phase's attack, random factor, 0.9^count) and the by-value
    // enum parameter gives the stack round trips seen in the asm.
    f32 getWeight(Attack attack);
    void sub_71005089F4(State state);

    // static_param at offset 0x40
    const float* mFreqIronBallAttack_s{};
    // static_param at offset 0x48
    const float* mFreqBigEarthReleaseAttack_s{};
    // static_param at offset 0x50
    const float* mFreqEyeBeamAttack_s{};
    // static_param at offset 0x58
    const float* mFreqStageRotation_s{};
    // static_param at offset 0x60
    const float* mFloatDistFromPlayer_s{};
    // static_param at offset 0x68
    const bool* mIsFreeMoving_s{};
    // aitree_variable at offset 0x70
    float* mKeepDistFromGround_a{};
    // aitree_variable at offset 0x78
    bool* mIsActive_a{};
    // aitree_variable at offset 0x80
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0x88
    sead::Vector3f* mDestinationPos_a{};
    // aitree_variable at offset 0x90
    sead::Vector3f* mFacePos_a{};
    s32 _98 = 0;
    State _9c = State::_2;
    s32 _a0 = 0;
    Unk_7102451280* _a8 = nullptr;
    // Per-phase counters (indexed by the phase, clamped to 10): the weights of m40-m44 decay as 0.9^count.
    sead::SafeArray<u32, 11> _b0{};
    ksys::Timer _dc{900.0f, 900.0f};
    Unk_7102451120 _e8;
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/Action/actionFollowChallenge.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include <math/seadVector.h>

class Unk_71024f15c0;

namespace uking::action {

class ChallengeChainRing : public FollowChallenge {
    SEAD_RTTI_OVERRIDE(ChallengeChainRing, FollowChallenge)
public:
    explicit ChallengeChainRing(const InitArg& arg);
    ~ChallengeChainRing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m33();
    virtual void m34(const sead::Vector3f& pos, const sead::Vector3f& dir);

    // map_unit_param at offset 0xab0
    const float* mChainRingOrbitSpeed_m{};
    // map_unit_param at offset 0xab8
    const bool* mIsFirstNode_m{};
    u8 _ac0[0xb4c - 0xac0];
    f32 _b4c = 0;
    f32 _b50 = 0;
    f32 _b54 = 0;
    f32 _b58 = 0;
    f32 _b5c = 0;
    u8 _b60[0xb70 - 0xb60];
    bool _b70 = false;
    Unk_71024f15c0* _b78 = nullptr;
    sead::Vector3f _b80{0, 0, 0};
    ksys::Timer _b8c;

    virtual void m35(sead::Vector3f* pos);
};

}  // namespace uking::action

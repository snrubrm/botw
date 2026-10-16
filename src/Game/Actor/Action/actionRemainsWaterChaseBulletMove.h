#pragma once

#include "Game/Actor/Action/actionRemainsWaterBulletAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::action {

class RemainsWaterChaseBulletMove : public RemainsWaterBulletAction {
    SEAD_RTTI_OVERRIDE(RemainsWaterChaseBulletMove, RemainsWaterBulletAction)
public:
    explicit RemainsWaterChaseBulletMove(const InitArg& arg);
    ~RemainsWaterChaseBulletMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710023357c: the bullet velocity chasing the target position (false without a player, body or target).
    bool sub_710023357C(sead::Vector3f* out);
    // 0x71002338d4 (declared only; 1132 B): the chase target position.
    bool sub_71002338D4(sead::Vector3f* target);
    void calc_() override;
    void m32() override;

    // static_param at offset 0x80
    const float* mBaseChaseSpd_s{};
    // static_param at offset 0x88
    const float* mMaxChaseSpd_s{};
    // static_param at offset 0x90
    const float* mChaseSpdRate_s{};
    // static_param at offset 0x98
    const float* mChaseAngleRate_s{};
    // static_param at offset 0xa0
    const float* mDepthOffset_s{};
    // static_param at offset 0xa8
    const float* mMaxPredictFrame_s{};
    // static_param at offset 0xb0
    const float* mMinPredictFrame_s{};
    // static_param at offset 0xb8
    const float* mStartPredictDist_s{};
    // static_param at offset 0xc0
    const float* mEndPredictDist_s{};
    // static_param at offset 0xc8
    const float* mWeakChaseTimer_s{};
    // static_param at offset 0xd0
    const sead::Vector3f* mBaseTargetOffset_s{};
    // static_param at offset 0xd8
    const sead::Vector3f* mBaseTargetRandOffset_s{};
    // map_unit_param at offset 0xe0
    const float* mRemainsWaterBulletAngle_m{};
    // map_unit_param at offset 0xe8
    const sead::Vector3f* mRemainsWaterBulletOffset_m{};
    ksys::act::Unk_7100d3bce4 _f0{mActor};
    sead::Vector3f _108{0, 1, 0};
    bool _114 = false;
};

}  // namespace uking::action

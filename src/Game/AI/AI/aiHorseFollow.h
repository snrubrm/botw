#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseFollow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseFollow, ksys::act::ai::Ai)
public:
    explicit HorseFollow(const InitArg& arg);
    ~HorseFollow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(sead::Vector3f* out, const sead::Vector3f& pos, const sead::Vector3f& target_pos,
                     const sead::Vector3f& target_velocity, const sead::Vector3f& up);
    virtual void m35();
    virtual bool m36() { return true; }
    virtual bool m37() { return true; }
    virtual const sead::Vector3f* m38() { return mSelfPositionOffsetLocal_s; }

protected:
    // static_param at offset 0x38
    const float* mDistanceSuccessEnd_s{};
    // static_param at offset 0x40
    const float* mDistanceMovingToward_s{};
    // static_param at offset 0x48
    const float* mDistanceRequestingPath_s{};
    // static_param at offset 0x50
    const float* mDistanceGivingUp_s{};
    // static_param at offset 0x58
    const float* mDistanceThresholdCry_s{};
    // static_param at offset 0x60
    const float* mDistanceCheckAvoidance_s{};
    // static_param at offset 0x68
    const float* mTargetVelocitySuccessEnd_s{};
    // static_param at offset 0x70
    const float* mUpdateTargetPosFrames_s{};
    // static_param at offset 0x78
    const float* mUpdateTargetPosFramesNear_s{};
    // static_param at offset 0x80
    const float* mSuccessEndDelays_s{};
    // static_param at offset 0x88
    const float* mSideDistance_s{};
    // static_param at offset 0x90
    const float* mTargetVelocityDistanceSec_s{};
    // static_param at offset 0x98
    const bool* mIsAvoidNavMeshActor_s{};
    // static_param at offset 0xa0
    const bool* mIsTargetPosEqualToLeaderPos_s{};
    // static_param at offset 0xa8
    const bool* mCanIgnorePlayer_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mSelfPositionOffsetLocal_s{};
    // dynamic_param at offset 0xb8
    float* mDistanceKept_d{};
    // dynamic_param at offset 0xc0
    ksys::act::BaseProcLink* mTargetActor_d{};
    f32 _c8 = 0;
    f32 _cc = 0;
    f32 _d0 = 0;
    int _d4 = -1;
    u8 _d8 = 0xff;
    s8 _d9 = -1;
    bool _da = false;
};
KSYS_CHECK_SIZE_NX150(HorseFollow, 0xe0);

}  // namespace uking::ai

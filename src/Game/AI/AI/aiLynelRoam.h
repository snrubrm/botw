#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LynelRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelRoam, ksys::act::ai::Ai)
public:
    explicit LynelRoam(const InitArg& arg);
    ~LynelRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x710049859c (placeholder name)
    void changeToMove(const sead::Vector3f& pos);

    // 0x7100498c00 (placeholder name): the player is within SpAttackServiceDist and the angle in front of the Lynel.
    bool sub_7100498C00();
    // 0x7100498e54 (placeholder name): picks a position to roam to (forward, then the other directions) and
    // starts moving there.
    bool sub_7100498E54();
    // 0x7100498d14 / 0x7100498ef8 (placeholder names): turn towards a new position (the first one looks for
    // a position, the other turns around the central position).
    void sub_7100498D14();
    void sub_7100498EF8();

protected:
    bool sub_7100498398(sead::Vector3f* out);
    bool sub_710049951C(sead::Vector3f* out, const sead::Vector3f& direction);

    // static_param at offset 0x38
    const int* mFreeIntervalMin_s{};
    // static_param at offset 0x40
    const int* mFreeIntervalMax_s{};
    // static_param at offset 0x48
    const int* mFreePer_s{};
    // static_param at offset 0x50
    const int* mMoveIntervalMin_s{};
    // static_param at offset 0x58
    const int* mMoveIntervalMax_s{};
    // static_param at offset 0x60
    const int* mNoMoveTime_s{};
    // static_param at offset 0x68
    const int* mNoSpAttackMoveTime_s{};
    // static_param at offset 0x70
    const int* mSpAttackServiceTime_s{};
    // static_param at offset 0x78
    const int* mRepathTime_s{};
    // static_param at offset 0x80
    const float* mTerritory_s{};
    // static_param at offset 0x88
    const float* mTargetDistMin_s{};
    // static_param at offset 0x90
    const float* mTargetDistMax_s{};
    // static_param at offset 0x98
    const float* mSpAttackServiceDist_s{};
    // static_param at offset 0xa0
    const float* mSpAttackServiceAngle_s{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mCentralPos_d{};
    f32 _b0{};
    s32 _b4{};
    s32 _b8{};
    ksys::Timer _bc;
    ksys::Timer _c8;
    ksys::Timer _d4;
    ksys::Timer _e0;
};

}  // namespace uking::ai

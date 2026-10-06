#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class WillBallAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WillBallAction, ksys::act::ai::Action)
public:
    explicit WillBallAction(const InitArg& arg);
    ~WillBallAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x71002bbb84 (parameter names are guesses): the unit direction from the actor towards the target (plus the
    // height offset; flat when the ball is on the ground), the horizontal distance and its ratio to the horizontal
    // distance from the start position.
    virtual void m32(sead::Vector3f* direction, f32* distance, f32* progress);

    struct Params {
        // static_param at offset 0x20
        const float* mMaxSpeed_s{};
        // static_param at offset 0x28
        const float* mRotSpeed_s{};
        // static_param at offset 0x30
        const float* mReachRange_s{};
        // static_param at offset 0x38
        const float* mTiredAngle_s{};
        // static_param at offset 0x40
        const float* mRotBaseRatio_s{};
        // static_param at offset 0x48
        const float* mAccel_s{};
        // static_param at offset 0x50
        const bool* mIsIgnoreLastSpRot_s{};
        // static_param at offset 0x58
        const bool* mIsAddAABBHeight_s{};
        // static_param at offset 0x60
        const bool* mIsGround_s{};
        // dynamic_param at offset 0x68
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    sead::Vector3f _70;
    ksys::VFRValue _7c;
    f32 _88 = 1.0f;
    f32 _8c = 0;
    s8 _90 = 1;  // +1 / -1: the sign of the actor's vertical velocity when entering
    bool _91 = false;
};

KSYS_CHECK_SIZE_NX150(WillBallAction, 0x98);

}  // namespace uking::action

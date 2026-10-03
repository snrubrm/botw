#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelAttackThroughMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelAttackThroughMove, ksys::act::ai::Ai)
public:
    explicit LynelAttackThroughMove(const InitArg& arg);
    ~LynelAttackThroughMove() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710048bf14 (placeholder name): picks the through time in [_94, _98] and starts the child with the target.
    void sub_710048BF14();

    struct Params {
        // static_param at offset 0x38
        const int* mSideOffsetDirType_s{};
        // static_param at offset 0x40
        const int* mCliffFailTime_s{};
        // static_param at offset 0x48
        const int* mWeaponIdx_s{};
        // static_param at offset 0x50
        const float* mSideOffset_s{};
        // static_param at offset 0x58
        const float* mThroughDist_s{};
        // static_param at offset 0x60
        const float* mAcceptableRadius_s{};
        // static_param at offset 0x68
        const float* mFrontAngle_s{};
        // dynamic_param at offset 0x70
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    sead::Vector3f _78;
    sead::Vector3f _84;
    f32 _90 = 0;
    s32 _94 = 0;
    s32 _98 = 0;
};

}  // namespace uking::ai

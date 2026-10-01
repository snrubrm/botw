#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class SwimMoveBase : public WaterFloatBase {
    SEAD_RTTI_OVERRIDE(SwimMoveBase, WaterFloatBase)
public:
    explicit SwimMoveBase(const InitArg& arg);
    ~SwimMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mSpeed_s{};
    // static_param at offset 0x68
    const float* mRotSpeed_s{};
    // static_param at offset 0x70
    const float* mFinRadius_s{};
    // static_param at offset 0x78
    const float* mFinRotate_s{};
    // static_param at offset 0x80
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x88
    const int* mWeaponIdx_s{};
    // dynamic_param at offset 0x90
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _98;
    ksys::Timer _a4;
    sead::Matrix33f _b0;
    sead::Vector3f _d4;
    f32 _e0 = 0;
};

KSYS_CHECK_SIZE_NX150(SwimMoveBase, 0xe8);

}  // namespace uking::action

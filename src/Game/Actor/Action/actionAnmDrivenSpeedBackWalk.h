#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class AnmDrivenSpeedBackWalk : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmDrivenSpeedBackWalk, ksys::act::ai::Action)
public:
    explicit AnmDrivenSpeedBackWalk(const InitArg& arg);
    ~AnmDrivenSpeedBackWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const int* mWeaponIdx_s{};
    // static_param at offset 0x30
    const float* mRotSpd_s{};
    // static_param at offset 0x38
    const float* mRotAddRatio_s{};
    // static_param at offset 0x40
    const float* mFinishDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    f32 _50 = 0;
    sead::Matrix33f _54;
    ksys::Timer _78{0, 0};
    ksys::Timer _84{0, 0};
};
KSYS_CHECK_SIZE_NX150(AnmDrivenSpeedBackWalk, 0x90);

}  // namespace uking::action

#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"

namespace uking::action {

class BackSwim : public WaterFloatBase {
    SEAD_RTTI_OVERRIDE(BackSwim, WaterFloatBase)
public:
    explicit BackSwim(const InitArg& arg);
    ~BackSwim() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const int* mTime_s{};
    // static_param at offset 0x68
    const int* mWeaponIdx_s{};
    // static_param at offset 0x70
    const float* mSpeed_s{};
    // static_param at offset 0x78
    const float* mRotSpd_s{};
    // static_param at offset 0x80
    const float* mRotAddRatio_s{};
    // static_param at offset 0x88
    const float* mFinishDist_s{};
    // static_param at offset 0x90
    const float* mDecelRatio_s{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0xa0
    const bool* mIsCheckCliff_s{};
    ksys::VFRValue _a8;
    ksys::VFRValue _b4;
    sead::Matrix33f _c0;
    sead::Vector2f _e4{0, 0};
    sead::Vector2f _ec{0, 0};
    sead::Vector2f _f4{0, 0};
};
KSYS_CHECK_SIZE_NX150(BackSwim, 0x100);

}  // namespace uking::action

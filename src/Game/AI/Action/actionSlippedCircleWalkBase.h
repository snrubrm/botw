#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SlippedCircleWalkBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SlippedCircleWalkBase, ksys::act::ai::Action)
public:
    explicit SlippedCircleWalkBase(const InitArg& arg);
    ~SlippedCircleWalkBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mRotDist_s{};
    // static_param at offset 0x38
    const float* mAccRatio_s{};
    // dynamic_param at offset 0x40
    int* mRotDir_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    sead::Matrix33f _50;
    s32 _74 = 0;
    f32 _78 = 0;
};

KSYS_CHECK_SIZE_NX150(SlippedCircleWalkBase, 0x80);

}  // namespace uking::action

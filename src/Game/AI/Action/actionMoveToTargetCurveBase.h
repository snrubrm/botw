#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class MoveToTargetCurveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoveToTargetCurveBase, ksys::act::ai::Action)
public:
    explicit MoveToTargetCurveBase(const InitArg& arg);
    ~MoveToTargetCurveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxHeight_s{};
    // static_param at offset 0x28
    const float* mTimeScale_s{};
    // static_param at offset 0x30
    const bool* mIsDebugDrawTargetPos_s{};
    u32 _38 = 0;
    u32 _3c = 0;
    u32 _40 = 0;
    sead::Vector3f _44 = sead::Vector3f::zero;
    f32 _50 = 0;
    sead::Vector3f _54{0, 0, 0};
    f32 _60 = 0;
    f32 _64 = 0;
};

KSYS_CHECK_SIZE_NX150(MoveToTargetCurveBase, 0x68);

}  // namespace uking::action

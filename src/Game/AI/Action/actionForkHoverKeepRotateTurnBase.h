#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class ForkHoverKeepRotateTurnBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkHoverKeepRotateTurnBase, ksys::act::ai::Action)
public:
    explicit ForkHoverKeepRotateTurnBase(const InitArg& arg);
    ~ForkHoverKeepRotateTurnBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMinRotSpd_s{};
    // static_param at offset 0x28
    const float* mEndAngle_s{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mTargetPos_d{};
    /* 0x38 */ sead::Matrix33f _38;
    /* 0x5c */ ksys::VFRValue _5c;
};
KSYS_CHECK_SIZE_NX150(ForkHoverKeepRotateTurnBase, 0x68);

}  // namespace uking::action

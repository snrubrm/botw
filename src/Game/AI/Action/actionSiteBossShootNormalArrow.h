#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossShootNormalArrow : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossShootNormalArrow, ksys::act::ai::Action)
public:
    explicit SiteBossShootNormalArrow(const InitArg& arg);
    ~SiteBossShootNormalArrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isFinished() const override;
    void loadParams_() override;

protected:
    // 0x7100263c64 (declared only): out of line in the original.
    void sub_7100263C64();
    void calc_() override;

    // static_param at offset 0x20
    const float* mInitSpeed_s{};
    // static_param at offset 0x28
    const float* mTargetOffsetY_s{};
    // static_param at offset 0x30
    const bool* mIsConnectChild_s{};
    // static_param at offset 0x38
    const bool* mIsCheckASEvent_s{};
    // static_param at offset 0x40
    const bool* mIsTurnToTarget_s{};
    // static_param at offset 0x48
    sead::SafeString mBaseNode_s{};
    // static_param at offset 0x58
    sead::SafeString mASName_s{};
    // static_param at offset 0x68
    const sead::Vector3f* mIgniteOffset_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mIgniteRotate_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mDirMinAngle_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mDirMaxAngle_s{};
    // dynamic_param at offset 0x88
    int* mIndex_d{};
    // dynamic_param at offset 0x90
    int* mAtAttr_d{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0xa0
    ksys::act::BaseProcLink* mIgniteActor_d{};
    // dynamic_param at offset 0xa8
    ksys::act::BaseProcHandle** mArrowHandle_d{};
    sead::Matrix33f _b0;
    int _d4 = 0;
    int _d8 = 0;
    int _dc = 0;
    int _e0 = 0;
};

}  // namespace uking::action

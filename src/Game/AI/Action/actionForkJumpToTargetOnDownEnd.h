#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkJumpToTargetOnDownEnd : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkJumpToTargetOnDownEnd, ksys::act::ai::Action)
public:
    explicit ForkJumpToTargetOnDownEnd(const InitArg& arg);
    ~ForkJumpToTargetOnDownEnd() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const float* mAngleDir_s{};
        // static_param at offset 0x28
        const float* mJumpDist_s{};
        // static_param at offset 0x30
        const float* mJumpHeight_s{};
        // static_param at offset 0x38
        const float* mLimitSpeed_s{};
        // static_param at offset 0x40
        const float* mEndGrSpeed_s{};
        // static_param at offset 0x48
        const float* mJumpMinDist_s{};
        // static_param at offset 0x50
        const bool* mIsBasisByTarget_s{};
        // static_param at offset 0x58
        const bool* mOnGround_s{};
        // dynamic_param at offset 0x60
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    u8 _68[0xc];
    ksys::VFRValue _74;
    u16 _80 = 1;
    u8 _82[0x6];
};
KSYS_CHECK_SIZE_NX150(ForkJumpToTargetOnDownEnd, 0x88);

}  // namespace uking::action

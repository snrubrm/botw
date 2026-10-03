#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgStepMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgStepMove, ksys::act::ai::Action)
public:
    explicit ForkASTrgStepMove(const InitArg& arg);
    ~ForkASTrgStepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const int* mWeaponIdx_s{};
        // static_param at offset 0x28
        const float* mCloseDist_s{};
        // static_param at offset 0x30
        const float* mSpeed_s{};
        // static_param at offset 0x38
        const float* mRotSpd_s{};
        // static_param at offset 0x40
        const float* mFinishDist_s{};
        // dynamic_param at offset 0x48
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    ksys::VFRValue _50{0.0f};
    f32 _5c = 0.0f;
    sead::Matrix33f _60;
    sead::Vector3f _84{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(ForkASTrgStepMove, 0x90);

}  // namespace uking::action

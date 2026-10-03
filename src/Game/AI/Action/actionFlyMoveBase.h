#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class FlyMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FlyMoveBase, ksys::act::ai::Action)
public:
    explicit FlyMoveBase(const InitArg& arg);
    ~FlyMoveBase() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Writes the target position (TargetPos with TargetHeightOffset added to y).
    virtual void m32(sead::Vector3f* target);
    // Writes the normalised direction to the target position and its distance.
    virtual void m33(sead::Vector3f* dir, f32* dist);
    bool sub_710013443C();

    struct Params {
        // static_param at offset 0x20
        const float* mSpeed_s{};
        // static_param at offset 0x28
        const float* mRotSpd_s{};
        // static_param at offset 0x30
        const float* mFinRotate_s{};
        // static_param at offset 0x38
        const float* mHorizontalFinRadius_s{};
        // static_param at offset 0x40
        const float* mTargetHeightOffset_s{};
        // static_param at offset 0x48
        const float* mRotRatio_s{};
        // static_param at offset 0x50
        const float* mVerticalFinLength_s{};
        // dynamic_param at offset 0x58
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    ksys::VFRValue _60;
    sead::Vector3f _6c{0, 0, 0};
    sead::Vector3f _78{0, 0, 0};
    sead::Matrix33f _84;
    ksys::VFRValue _a8;
    ksys::act::CCAccessor mCCAccessor;
};

KSYS_CHECK_SIZE_NX150(FlyMoveBase, 0xc0);

}  // namespace uking::action

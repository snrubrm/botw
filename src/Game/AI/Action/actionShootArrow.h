#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class ShootArrow : public ActionEx {
    SEAD_RTTI_OVERRIDE(ShootArrow, ActionEx)
public:
    explicit ShootArrow(const InitArg& arg);
    ~ShootArrow() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x20
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x28
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const float* mOffsetRangeMin_s{};
    // static_param at offset 0x40
    const float* mOffsetRangeMax_s{};
    // static_param at offset 0x48
    const float* mOffsetRateByDist_s{};
    // static_param at offset 0x50
    const float* mOffsetRangeMinOutOfScreen_s{};
    // static_param at offset 0x58
    const float* mOffsetRangeMaxOutOfScreen_s{};
    // static_param at offset 0x60
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _78{0.0f};
    ksys::VFRVec3f _84;
    f32 _a8 = 0;
    bool _ac = false;
};

}  // namespace uking::action

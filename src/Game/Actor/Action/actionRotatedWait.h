#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RotatedWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RotatedWait, ksys::act::ai::Action)
public:
    explicit RotatedWait(const InitArg& arg);
    ~RotatedWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mRotAxis_m{};
    // map_unit_param at offset 0x28
    const float* mTiltAngle_m{};
    u64 _30 = 0;
    sead::Vector3f _38 = sead::Vector3f::ey;
    sead::Vector3f _44 = sead::Vector3f::zero;
    sead::Vector3f _50 = sead::Vector3f::zero;
    u8 _5c[0x4];
};
KSYS_CHECK_SIZE_NX150(RotatedWait, 0x60);

}  // namespace uking::action

#pragma once

#include <math/seadMatrix.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchWheel : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwitchWheel, ksys::act::ai::Ai)
public:
    explicit SwitchWheel(const InitArg& arg);
    ~SwitchWheel() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    const float* mRotateStartRad_s{};
    // static_param at offset 0x40
    const float* mRotateEndRad_s{};
    // static_param at offset 0x48
    const float* mReverseEndRad_s{};
    // static_param at offset 0x50
    const float* mReverseStartRad_s{};
    // static_param at offset 0x58
    const bool* mIsAbleToReverse_s{};
    // map_unit_param at offset 0x60
    const int* mRotAxis_m{};
    // Inverse of the actor's home rotation (enter_).
    sead::Matrix33f _68;
    xlink2::HandleSLink* _90 = nullptr;
};
KSYS_CHECK_SIZE_NX150(SwitchWheel, 0x98);

}  // namespace uking::ai

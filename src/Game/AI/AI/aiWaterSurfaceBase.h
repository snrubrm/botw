#pragma once

#include <math/seadVector.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaterSurfaceBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WaterSurfaceBase, ksys::act::ai::Ai)
public:
    explicit WaterSurfaceBase(const InitArg& arg);
    ~WaterSurfaceBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_71005ED41C();
    void sub_71005ED79C();
    void sub_71005ED864();

    // map_unit_param at offset 0x38
    const float* mFlowSpeedFactor_m{};
    // aal::ShapeCube* (created in init_ with aal::ShapeCube::create)
    void* _40{};
    xlink2::HandleSLink _48;
    xlink2::HandleSLink _58;
    sead::Vector3f _68 = sead::Vector3f::zero;
};

}  // namespace uking::ai

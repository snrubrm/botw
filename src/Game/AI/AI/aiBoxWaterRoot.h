#pragma once

#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace aal {
class ShapeCube;
}

namespace ksys::phys {
class RigidBody;
}

namespace uking::ai {

class BoxWaterRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BoxWaterRoot, ksys::act::ai::Ai)
public:
    explicit BoxWaterRoot(const InitArg& arg);
    ~BoxWaterRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710033d4c8 (declared only): applies the params to the water bodies and shapes.
    void sub_710033D4C8();

    // Created in init_: the cylinder water body (waterfall), the box body of the waterfall and the
    // body of the part below it.
    ksys::phys::RigidBody* _38{};
    ksys::phys::RigidBody* _40{};
    ksys::phys::RigidBody* _48{};
    aal::ShapeCube* _50{};
    aal::ShapeCube* _58{};
    xlink2::HandleSLink _60{};
    // map_unit_param at offset 0x70
    const int* mWaterMaterial_m{};
    // map_unit_param at offset 0x78
    const float* mFlowSpeedFactor_m{};
    // map_unit_param at offset 0x80
    const float* mWaterfallRadius_m{};
    // map_unit_param at offset 0x88
    const float* mWaterfallLength_m{};
    // map_unit_param at offset 0x90
    const float* mWaterfallThickness_m{};
    // map_unit_param at offset 0x98
    const float* mWaterfallAngle_m{};
    // map_unit_param at offset 0xa0
    const int* mSoundInDoorType_m{};
};

}  // namespace uking::ai

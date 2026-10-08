#pragma once

#include <gsys/gsysModelAccessKey.h>

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoMotorcyclePutMaterials : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoMotorcyclePutMaterials, ksys::act::ai::Action)
public:
    explicit DemoMotorcyclePutMaterials(const InitArg& arg);
    ~DemoMotorcyclePutMaterials() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mCloseSaddleFramesSincePut_s{};
    // static_param at offset 0x28
    const float* mFinishCookFramesSincePut_s{};
    // static_param at offset 0x30
    const float* mCloseSaddleFramesSincePutFairy_s{};
    // static_param at offset 0x38
    const float* mFinishCookFramesSincePutFairy_s{};

    // All recovered from the ctor's stores (0x54cb8). _40/_44/_48 are gsys bone keys
    // (written by enter_'s searchBone calls); _4c is the 5 cycled Loc/Fairy bone keys (written by
    // enter_ via index). BoneAccessKey (not s32): enter_ stores whole searchBone results (str w0)
    // with no conversion, and reset() gives the observed -1/-1 bits. _60 is compared as a float
    // by calc_; _64/_68 are s32 counters (scvtf, ldrsw) in enter_.
    // NON_MATCHING (ctor): our build merges the adjacent same-value stores (stp), while the
    // original keeps str-x/str-w/stur-x boundaries; the values and offsets are identical.
    gsys::BoneAccessKey _40;
    gsys::BoneAccessKey _44;
    gsys::BoneAccessKey _48;
    gsys::BoneAccessKey _4c[5];
    f32 _60 = 0.0f;
    s32 _64 = 0;
    s32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(DemoMotorcyclePutMaterials, 0x70);

}  // namespace uking::action

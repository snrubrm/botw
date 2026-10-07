#pragma once

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

    // All recovered from the ctor's stores (0x54cb8). _40/_44/_48 are gsys bone indices
    // (written by enter_'s searchBone calls, -1 = not found). _60 is compared as a float by calc_;
    // _64/_68 are s32 counters (scvtf) in enter_. _4c/_50/_54/_58/_5c are only written by the ctor.
    // NON_MATCHING (ctor): our build merges the adjacent same-value stores (stp), while the
    // original keeps str-x/str-w/stur-x boundaries; the values and offsets are identical.
    s32 _40 = -1;
    s32 _44 = -1;
    s32 _48 = -1;
    s32 _4c = -1;
    s32 _50 = -1;
    s32 _54 = -1;
    s32 _58 = -1;
    s32 _5c = -1;
    f32 _60 = 0.0f;
    s32 _64 = 0;
    s32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(DemoMotorcyclePutMaterials, 0x70);

}  // namespace uking::action

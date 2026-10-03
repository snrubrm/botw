#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::action {

class AirOctaFloatBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirOctaFloatBase, ksys::act::ai::Action)
public:
    explicit AirOctaFloatBase(const InitArg& arg);
    ~AirOctaFloatBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x20
    const float* mAmplitude_s{};
    // static_param at offset 0x28
    const float* mGoalDistance_s{};
    // static_param at offset 0x30
    const bool* mGoalInSuccessEnd_s{};
    // aitree_variable at offset 0x38
    void* mAirOctaDataMgr_a{};
    f32 _40 = 0.0f;
    f32 _44 = 0.0f;
    sead::Vector3f _48 = sead::Vector3f::zero;
    sead::Vector3f _54 = sead::Vector3f::zero;
    sead::Vector3f _60 = sead::Vector3f::zero;
    ksys::act::BoneHandle _70;
    ksys::act::BoneHandle _118;
    s32 _1c0 = 0;
    sead::Vector3f _1c4;
};
KSYS_CHECK_SIZE_NX150(AirOctaFloatBase, 0x1d0);

}  // namespace uking::action

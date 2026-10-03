#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class Constraint;
}

namespace uking::ai {

// Besides Ai it has a plain ActorBind subobject at 0x38 (like DgnObj_DLC_SliderBlock): m4 / m5
// override ActorBind's slots (their Ai vtable entries are the CSV's m38 / m39).
class DgnObj_DLC_CogWheel2 : public ksys::act::ai::Ai, public ksys::act::ActorBind {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_CogWheel2, ksys::act::ai::Ai)
public:
    explicit DgnObj_DLC_CogWheel2(const InitArg& arg);
    ~DgnObj_DLC_CogWheel2() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();

    bool m4(ksys::act::BaseProc* proc) override;
    bool m5(ksys::act::BaseProc* proc) override;

protected:
    // static_param at offset 0x60
    const bool* mCorrectConstraint_s{};
    // map_unit_param at offset 0x68
    const float* mGearRatio_m{};
    // map_unit_param at offset 0x70
    const bool* mRegistFromBeginning_m{};
    // map_unit_param at offset 0x78
    const bool* mJoinSystemGroup_m{};
    // aitree_variable at offset 0x80
    float* mRotationOffset_a{};
    ksys::phys::Constraint* _88{};
    sead::SafeArray<f32, 3> _90;
    s32 _9c = 0;
};

}  // namespace uking::ai

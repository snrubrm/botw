#pragma once

#include <math/seadVector.h>
#include <xlink2/xlink2Handle.h>
#include "Game/AI/AI/aiGuardianBeamAttackBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianBeamAttack : public GuardianBeamAttackBase {
    SEAD_RTTI_OVERRIDE(GuardianBeamAttack, GuardianBeamAttackBase)
public:
    explicit GuardianBeamAttack(const InitArg& arg);
    ~GuardianBeamAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    sead::Vector3f _38 = sead::Vector3f::ey;
    xlink2::Handle _48;
    xlink2::Handle _58;
    f32 _68 = 5.0f;
    f32 _6c = 30.0f;
    u32 _70 = 0;
    // heap-allocated object derived from ksys::act::ModelBindInfo (created in init_)
    void* _78{};
    // static_param at offset 0x80
    const float* mLightRadius_s{};
    // static_param at offset 0x88
    const float* mLightLength_s{};
    // static_param at offset 0x90
    const float* mLightLengthOffset_s{};
    // static_param at offset 0x98
    const float* mEarSpeed_s{};
    // static_param at offset 0xa0
    const bool* mAdjustRadius_s{};
};

}  // namespace uking::ai

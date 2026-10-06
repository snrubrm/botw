#pragma once

#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Stun : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Stun, ksys::act::ai::Action)
public:
    explicit Stun(const InitArg& arg);
    ~Stun() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x7100281144 (placeholder name): starts the stun when the actor was hit by an attack of a stunning damage
    // type: launches the actor along the hit direction and copies its angular velocity.
    bool sub_7100281144();

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const float* mHitImpactForceSmallSwordS_s{};
    // static_param at offset 0x30
    const float* mHitImpactForceLargeSwordS_s{};
    // static_param at offset 0x38
    const float* mHitImpactForceSpearS_s{};
    ksys::Timer _40;
    ksys::VFRValue _4c;
    ksys::VFRVec3f _58;
    s32 _7c = 0;
};
KSYS_CHECK_SIZE_NX150(Stun, 0x80);

}  // namespace uking::action

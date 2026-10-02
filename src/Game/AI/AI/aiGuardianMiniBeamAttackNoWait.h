#pragma once

#include "Game/AI/AI/aiGuardianMiniBeamAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBeamAttackNoWait : public GuardianMiniBeamAttack {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamAttackNoWait, GuardianMiniBeamAttack)
public:
    explicit GuardianMiniBeamAttackNoWait(const InitArg& arg);
    ~GuardianMiniBeamAttackNoWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x2d8
    const float* mAttackAngle_s{};
    bool _2e0 = true;
};
KSYS_CHECK_SIZE_NX150(GuardianMiniBeamAttackNoWait, 0x2e8);

}  // namespace uking::ai

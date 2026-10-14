#pragma once

#include "Game/Actor/actGuardian.h"
#include "Game/Actor/actGuardianComponent.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianBeamAttackBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianBeamAttackBase, ksys::act::ai::Ai)
public:
    explicit GuardianBeamAttackBase(const InitArg& arg);
    ~GuardianBeamAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100411de0 / 0x7100411e74 / 0x7100411f00 (placeholder names): the Guardian component the actor is (null
    // for other actors): its Guardian, the component itself and a test on the Guardian.
    uking::act::Guardian* sub_7100411DE0();
    uking::act::GuardianComponent* sub_7100411E74();
    bool sub_7100411F00();
};

}  // namespace uking::ai

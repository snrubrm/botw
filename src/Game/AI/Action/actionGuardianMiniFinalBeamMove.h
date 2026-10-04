#pragma once

#include "Game/AI/Action/actionGuardianBeamFire.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniFinalBeamMove : public GuardianBeamFire {
    SEAD_RTTI_OVERRIDE(GuardianMiniFinalBeamMove, GuardianBeamFire)
public:
    explicit GuardianMiniFinalBeamMove(const InitArg& arg);
    ~GuardianMiniFinalBeamMove() override;
    bool isFinished() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100194a58 (declared only): out of line in the original.
    void sub_7100194A58();
    void calc_() override;
    bool _80 = false;
};

}  // namespace uking::action

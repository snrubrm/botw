#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HoldArrowTurn : public TurnBase {
    SEAD_RTTI_OVERRIDE(HoldArrowTurn, TurnBase)
public:
    explicit HoldArrowTurn(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // static_param at offset 0x90
    const int* mWeaponIdx_s{};
};

}  // namespace uking::action

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
    u8 _60[0x90 - 0x60];
    void* _90{};
};

}  // namespace uking::action

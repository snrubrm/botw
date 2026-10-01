#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerWakeBoardEnd : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerWakeBoardEnd, PlayerAction)
public:
    explicit PlayerWakeBoardEnd(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
};

}  // namespace uking::action

#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerStainCarryWait : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerStainCarryWait, PlayerAction)
public:
    explicit PlayerStainCarryWait(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    bool _1d = false;
};

}  // namespace uking::action

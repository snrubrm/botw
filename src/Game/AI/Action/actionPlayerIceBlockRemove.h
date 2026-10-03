#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

class PlayerIceBlockRemove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerIceBlockRemove, PlayerAction)
public:
    explicit PlayerIceBlockRemove(const InitArg& arg);
    ~PlayerIceBlockRemove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    ksys::act::BaseProcHandle _20;
};

}  // namespace uking::action

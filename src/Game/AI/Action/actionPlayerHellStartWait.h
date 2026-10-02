#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerHellStartWait : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerHellStartWait, PlayerAction)
public:
    explicit PlayerHellStartWait(const InitArg& arg);
    ~PlayerHellStartWait() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    int _20 = 0;
};

}  // namespace uking::action

#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerDestinationTurnStarter : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerDestinationTurnStarter, PlayerAction)
public:
    explicit PlayerDestinationTurnStarter(const InitArg& arg);
    ~PlayerDestinationTurnStarter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m33();
    virtual bool m34();
    virtual bool m35();
};

}  // namespace uking::action

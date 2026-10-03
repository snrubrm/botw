#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/MathUtil.h"

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

    ksys::util::Unk_7101EC6BAC _20{0};
    ksys::act::BaseProcLink _28;
};

}  // namespace uking::action

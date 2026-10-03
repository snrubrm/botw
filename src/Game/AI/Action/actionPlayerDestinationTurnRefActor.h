#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

class PlayerDestinationTurnRefActor : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerDestinationTurnRefActor, PlayerAction)
public:
    explicit PlayerDestinationTurnRefActor(const InitArg& arg);
    ~PlayerDestinationTurnRefActor() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m33();
    virtual bool m34();
    virtual bool m35();

    // dynamic_param at offset 0x20
    sead::SafeString mUniqName_d{};
    ksys::util::Unk_7101EC6BAC _30{0};
    ksys::act::BaseProcLink _38;
    ksys::act::BaseProcLink _48;
    int _58 = 0;
};

}  // namespace uking::action

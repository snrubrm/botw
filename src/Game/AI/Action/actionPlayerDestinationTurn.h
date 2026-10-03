#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

class PlayerDestinationTurn : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerDestinationTurn, PlayerAction)
public:
    explicit PlayerDestinationTurn(const InitArg& arg);

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
    float* mDestPosX_d{};
    // dynamic_param at offset 0x28
    float* mDestPosY_d{};
    // dynamic_param at offset 0x30
    float* mDestPosZ_d{};
    ksys::util::Unk_7101EC6BAC _38{0};
};

}  // namespace uking::action

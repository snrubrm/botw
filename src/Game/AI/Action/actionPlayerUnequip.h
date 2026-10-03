#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::action {

class PlayerUnequip : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerUnequip, PlayerAction)
public:
    explicit PlayerUnequip(const InitArg& arg);
    ~PlayerUnequip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    ksys::act::ModelBindInfo _20;
};

}  // namespace uking::action

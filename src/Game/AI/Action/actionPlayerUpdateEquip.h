#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::action {

class PlayerUpdateEquip : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerUpdateEquip, PlayerAction)
public:
    explicit PlayerUpdateEquip(const InitArg& arg);
    ~PlayerUpdateEquip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    ksys::act::ModelBindInfo _20;
};

}  // namespace uking::action

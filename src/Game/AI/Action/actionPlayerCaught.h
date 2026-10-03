#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/AI/aiUnk_7102450058.h"

namespace uking::action {

class PlayerCaught : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCaught, PlayerAction)
public:
    explicit PlayerCaught(const InitArg& arg);
    ~PlayerCaught() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    Unk_710244ed58 _20;
};

}  // namespace uking::action

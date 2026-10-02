#pragma once

#include "Game/AI/Action/actionPlayerStoleOpenBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerStoleOpenEx : public PlayerStoleOpenBase {
    SEAD_RTTI_OVERRIDE(PlayerStoleOpenEx, PlayerStoleOpenBase)
public:
    explicit PlayerStoleOpenEx(const InitArg& arg);

protected:
    void m32() override;
};

}  // namespace uking::action

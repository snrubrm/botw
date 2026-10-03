#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

class PlayerSetVisibleWeapon : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSetVisibleWeapon, PlayerAction)
public:
    explicit PlayerSetVisibleWeapon(const InitArg& arg);
    ~PlayerSetVisibleWeapon() override;

    bool init_(sead::Heap* heap) override;
    bool oneShot_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mSetVisible_d{};
    ksys::MessageTransceiverTxOnly _28{mActor};
};

}  // namespace uking::action

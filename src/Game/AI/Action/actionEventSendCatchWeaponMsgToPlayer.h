#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSendCatchWeaponMsgToPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSendCatchWeaponMsgToPlayer, ksys::act::ai::Action)
public:
    explicit EventSendCatchWeaponMsgToPlayer(const InitArg& arg);
    ~EventSendCatchWeaponMsgToPlayer() override;

    bool init_(sead::Heap* heap) override;
    bool oneShot_() override;
    void loadParams_() override;

protected:
    Unk_710237ecc0 _20{mActor};
};
KSYS_CHECK_SIZE_NX150(EventSendCatchWeaponMsgToPlayer, 0x50);

}  // namespace uking::action

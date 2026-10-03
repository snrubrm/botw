#pragma once

#include "Game/AI/Action/actionPlayerLookAtObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <prim/seadSafeString.h>

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class PlayerTurnAndLookToObject : public PlayerLookAtObject {
    SEAD_RTTI_OVERRIDE(PlayerTurnAndLookToObject, PlayerLookAtObject)
public:
    explicit PlayerTurnAndLookToObject(const InitArg& arg);
    ~PlayerTurnAndLookToObject() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m40();
    virtual void m41(ksys::phys::CharacterController* controller);

    // dynamic_param at offset 0xc8
    bool* mIsUseSlowTurn_d{};
    // dynamic_param at offset 0xd0
    bool* mIsTurnToLookAtPos_d{};
    bool _d8 = false;
    bool _d9 = false;
    sead::FixedSafeString<64> _e0{""};
};
KSYS_CHECK_SIZE_NX150(PlayerTurnAndLookToObject, 0x138);

}  // namespace uking::action

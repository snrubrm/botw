#pragma once

#include "Game/AI/Action/actionPlayerLookAtObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"

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
};

}  // namespace uking::action

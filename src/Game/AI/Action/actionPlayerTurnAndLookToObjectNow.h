#pragma once

#include "Game/AI/Action/actionPlayerLookAtObjectNow.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <prim/seadSafeString.h>

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class PlayerTurnAndLookToObjectNow : public PlayerLookAtObjectNow {
    SEAD_RTTI_OVERRIDE(PlayerTurnAndLookToObjectNow, PlayerLookAtObjectNow)
public:
    explicit PlayerTurnAndLookToObjectNow(const InitArg& arg);
    ~PlayerTurnAndLookToObjectNow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m40();
    virtual void m41(ksys::phys::CharacterController* controller);

    bool _c8 = false;
    sead::FixedSafeString<64> _d0{""};
};
KSYS_CHECK_SIZE_NX150(PlayerTurnAndLookToObjectNow, 0x128);

}  // namespace uking::action

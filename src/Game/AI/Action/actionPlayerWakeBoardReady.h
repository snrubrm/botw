#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

class PlayerWakeBoardReady : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerWakeBoardReady, PlayerAction)
public:
    explicit PlayerWakeBoardReady(const InitArg& arg);
    ~PlayerWakeBoardReady() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mCreateSelf_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mUniqueName_d{};
    ksys::act::BaseProcHandle _38;

};
KSYS_CHECK_SIZE_NX150(PlayerWakeBoardReady, 0x48);

}  // namespace uking::action

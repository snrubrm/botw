#pragma once

#include "Game/AI/Action/actionTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniGuardTurn : public Turn {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardTurn, Turn)
public:
    explicit GuardianMiniGuardTurn(const InitArg& arg);
    ~GuardianMiniGuardTurn() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // 0x71001966c4 (declared only): out of line in the original.
    void sub_71001966C4();
    // static_param at offset 0x90
    const int* mASSlot_s{};
    // static_param at offset 0x98
    sead::SafeString mASName_s{};
};

}  // namespace uking::action

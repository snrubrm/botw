#pragma once

#include "Game/AI/Action/actionPlayerGuidedMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/AI/aiUnk_71024f15c0.h"

namespace uking::action {

class PlayerRailMove : public PlayerGuidedMove {
    SEAD_RTTI_OVERRIDE(PlayerRailMove, PlayerGuidedMove)
public:
    explicit PlayerRailMove(const InitArg& arg);
    ~PlayerRailMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x58
    sead::SafeString mRailName_d{};
    Unk_71024f15c0 _68;

};
KSYS_CHECK_SIZE_NX150(PlayerRailMove, 0xc8);

}  // namespace uking::action

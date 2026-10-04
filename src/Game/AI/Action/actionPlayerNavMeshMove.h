#pragma once

#include "Game/AI/Action/actionPlayerGuidedMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerNavMeshMove : public PlayerGuidedMove {
    SEAD_RTTI_OVERRIDE(PlayerNavMeshMove, PlayerGuidedMove)
public:
    explicit PlayerNavMeshMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    // 0x71007e8c34 (declared only): out of line in the original.
    void sub_71007E8C34(ksys::act::ai::InlineParamPack* params);
    void calc_() override;
};

}  // namespace uking::action
